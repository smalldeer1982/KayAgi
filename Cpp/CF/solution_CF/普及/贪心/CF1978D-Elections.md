# Elections

## 题目描述

Elections are taking place in Berland. There are $ n $ candidates participating in the elections, numbered from $ 1 $ to $ n $ . The $ i $ -th candidate has $ a_i $ fans who will vote for him. Additionally, there are $ c $ people who are undecided about their favorite candidate, let's call them undecided. Undecided people will vote for the candidate with the lowest number.

The candidate who receives the maximum number of votes wins the elections, and if multiple candidates receive the same maximum number of votes, the candidate with the lowest number among them wins.

You found these elections too boring and predictable, so you decided to exclude some candidates from them. If you do not allow candidate number $ i $ to participate in the elections, all $ a_i $ of his fans will become undecided, and will vote for the candidate with the lowest number.

You are curious to find, for each $ i $ from $ 1 $ to $ n $ , the minimum number of candidates that need to be excluded from the elections for candidate number $ i $ to win the elections.

## 说明/提示

In the first test case:

- If all candidates are allowed, candidate number $ 1 $ will receive $ 3 $ votes ( $ 1 $ undecided person will vote for him), candidate number $ 2 $ will receive $ 0 $ votes, and candidate number $ 3 $ will receive $ 3 $ votes. Therefore, candidate number $ 1 $ wins (he received the same number of votes as candidate $ 3 $ , but his number is lower), so the answer for him is $ 0 $ .
- If candidate number $ 1 $ is not allowed, his $ 2 $ fans will become undecided. Then candidate number $ 2 $ will receive $ 3 $ votes ( $ 3 $ undecided people will vote for him) and candidate number $ 3 $ will receive $ 3 $ votes. Therefore, candidate number $ 2 $ wins (he received the same number of votes as candidate $ 3 $ , but his number is lower), so the answer for him is $ 1 $ .
- If candidates with numbers $ 1 $ and $ 2 $ are not allowed, candidate number $ 3 $ wins, so the answer for him is $ 2 $ .

In the second test case, candidate number $ 1 $ will win if candidate number $ 2 $ is not allowed to participate.

## 样例 #1

### 输入

```
5
3 1
2 0 3
2 3
0 10
5 3
5 4 3 2 1
4 5
3 10 7 1
6 0
2 2 2 3 3 3```

### 输出

```
0 1 2
1 0
0 1 2 3 4
1 0 2 3
1 1 2 0 4 5```

# 题解

## 作者：hh弟中弟 (赞：5)

### [CF1978D Elections](https://www.luogu.com.cn/problem/CF1978D)
有一点比较显然，如果一个人不能直接获胜的话，那么他前面的人都应该被撤下，这样才会改变这个人的票数，才有可能使他获胜。\
接下来有两种情况：
- 撤完前面的人后，他的票数大于等于剩下的人的最多票数的话，那么此时直接获胜。
- 撤完前面的人后，他的票数小于剩下的人的最多票数的话，此时再把票数最多的人撤下，这样他就成了票数最多的人，获胜。

直接做前缀和和后缀最大值就行，时间复杂度 $\mathcal{O}(n)$，注意开 long long。
```cpp
#include<bits/stdc++.h>
#define int long long 
typedef long long ll;
typedef unsigned long long ull;
inline int read(){char ch=getchar();int x=0,f=1;for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')f=-1;for(;ch>='0'&&ch<='9';ch=getchar())x=(x<<3)+(x<<1)+(ch^48);return x*f;}
const int N=2e5+10;
int a[N],sum[N],max[N];
signed main(){
	// freopen("in.in","r",stdin);freopen("out.out","w",stdout);
	std::ios::sync_with_stdio(false);std::cin.tie(0);std::cout.tie(0);
	int T=read();
	while(T--){
		int n=read(),c=read();
		for(int i=1;i<=n;++i)a[i]=read();a[1]+=c;
		for(int i=1;i<=n;++i)sum[i]=sum[i-1]+a[i];
		max[n+1]=0;
		for(int i=n;i;--i)max[i]=std::max(a[i],max[i+1]);
		int st=0;
		for(int i=1;i<=n;++i){
			if(a[i]==max[1]&&st<max[1]){std::cout<<0<<' ';}
			else{
				int ans=i-1;
				if(sum[i]<max[i+1]){ans++;}
				std::cout<<ans<<' ';
			}
			st=std::max(st,a[i]);
		}
		std::cout<<'\n';
	}	
}
```
感觉 C 比 D 难（在正确理解题意的情况下），所以为啥青还能掉分（wtcl）。

---

## 作者：szh_AK_all (赞：4)

这道题很简单，~~但是比赛时没时间做。~~

### 分析
首先，一开始的 $c$ 个投票者肯定会将票投给第 $1$ 个人。如果将第一个人去掉，那么这 $a_1+c$ 张票将会传递给第 $2$ 个人；将前 $i$ 个人去掉，那么第 $i+1$ 个人会获得 $c+\sum_{x=1}^{i+1}a_i$ 张票。

考虑第 $i$ 个人若要成为票数最多的人，至少需要去掉多少竞争对手。

若第 $i$ 个人的票数原本就是最多的，那么答案便为 $0$；否则，前 $i-1$ 个人肯定是要去掉的，因为如果不去掉前 $i-1$ 个人中的任何一个，那么没被去掉的人就会获得更多的票数（因为投票者会将票投给编号小的人），而第 $i$ 个人的票数却没改变。由于第 $i$ 个人的票数本身不是最大的，而其他某些人的票数还变多了，那么第 $i$ 个人的票数便更不可能是最大的。所以，若第 $i$ 个人的票数原本不是最多的，前 $i-1$ 个人一定要去掉。

接下来又分为两种情况。若去掉前 $i-1$ 个人后，$c+\sum_{x=1}^{i}$ 为当前的最大票数，则答案为 $i-1$；否则，因为要求出**至少**需要去掉多少人，所以直接将后 $n-i$ 个人中票数最大者去掉，那么第 $i$ 个人的票数便是最大的了，答案为 $i$。

### Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int a[200005], hou[200005];

signed main() {
	int t;
	cin >> t;
	while (t--) {
		int n, c;
		cin >> n >> c;
		for (int i = 1; i <= n; i++)
			cin >> a[i];
		a[1] += c;
		hou[n + 1] = 0;
		for (int i = n; i >= 1; i--)
			hou[i] = max(hou[i + 1], a[i]);
		int maxn = 0;
		for (int i = 1; i <= n; i++) {
			if (a[i] == hou[1]) {
				maxn = i;
				break;
			}
		}
		int qian = 0;
		for (int i = 1; i <= n; i++) {
			if (i == maxn)
				cout << 0;
			else if (a[i] + qian >= hou[i + 1])
				cout << i - 1;
			else
				cout << i;
			qian += a[i];
			cout << " ";
		}
		cout << endl;
	}
}
```

---

## 作者：NATO (赞：3)

~~不看翻译随便秒的题~~。

### 思路浅析：

强调一下，题目中待定票是全部投给剩下的人中**编号**最小的。

读懂了题，做法就极其简单了。

考虑如果我不是最大值，我必然是要将前面的人 ban 完才可能是最大值的，原因显然（就是如果最大值出自前面，那么我不删完这些票必然也是投给前面的人的，出自后面亦然）。

故对于 $a_i$（$a_1$ 就直接判一下 $a_1+c$ 是否是大于等于最大值的），判一下 $a_1+c$ 是否是小于 $a_i$ 且 $a_i$ 是原序列中最前面的那个最大值的，如果是，那么就一个也不删，否则，删掉前面所有人，若 $c+\sum\limits_{j=1}^{i}a_j$ 小于后面的最大值，那么再删掉后面的最大值即可（某一个最大值的票数都给我了，我就一定是新的最大值），答案为 $i$，否则为 $i-1$。处理一个前缀和和后缀最大值即可，时间复杂度 $O(n)$。

#### 参考代码：

[赛时代码](https://codeforces.com/contest/1978/submission/266007829)

沙包笔者赛时忘了删掉后面的最大值加给自己之后自己必然是最大值了，故请读者自行忽略代码中的二分和线段树，改成与后缀最大值比较即可（~~像笔者一样大脑短路者慎读上面的代码，造成的数据结构综合征笔者概不负责~~）。

---

## 作者：SunsetLake (赞：2)

## 思路

因为有不确定的人，因此对于每个参赛者分两种情况讨论：

- 会获得不确定的票。
- 不会获得不确定的票。

对于第一种，那么当前参赛者 $i$ 一定是序列中的第一个人，这样才能拿到所有不确定的票，答案先加上 $i - 1$。然后 $a_i$ 就变成了 $\sum\limits_{j = 1}^{i}a_j + c$。再去看 $i + 1 \sim n$ 中 $> a_i$ 的人（没有就不管），我们只需要删除一个最大的 $a_j$ 就行了。因为最大的被删了之后会加到 $a_i$ 上，此时 $a_i$ 一定 $\ge$ 序列中所有的数。

对于第二种，因为 $a_i$ 不能再增大，那么所有 $>$ 它的数以及在他前面 $=$ 它的数都要被删掉。但是这些数被删后又会加到下标最小的数上面去，$a_i$ 就不可能最大了。当然，只有一种数需要判这种情况：序列中第一个最大的数，枚举 $1 \sim i$ 谁作为第一个数即可。

实现用前缀和，复杂度 $O(n)$。

## code

```cpp
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
using namespace std;
int t;
const int N = 2e5 + 5;
int n;
ll c,a[N];
ll sum[N],k[N];
void solve(){
	cin >> n >> c;
	for(int i = 1;i <= n;++ i) cin >> a[i],sum[i] = sum[i - 1] + a[i];
	ll mx = -1;
	for(int i = n;i >= 1;-- i){
		if(mx <= sum[i] + c) k[i] = 0;
		else k[i] = 1;
		mx = max(mx,a[i]); 	
	}
	bool fl = 0;
	for(int i = 1;i <= n;++ i){
		int ans = 0;
		if(a[i] == mx && !fl){
			fl = 1;
			ans = i - 1;
			for(int j = 1;j <= i;++ j)
				if(sum[j] + c < a[i]){
					ans = j - 1;
					break;
				}
			cout << ans << " ";
			continue;
		}
		ans = i - 1 + k[i];
		cout << ans << " ";
	}
	puts("");
}
int main(){
	cin >> t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：KSCD_ (赞：2)

## 题意
给出 $n$ 个人的票数 $a_i$，同时有 $c$ 票暂时没有固定对象。可以让若干人不参加，这些人原有的票数以及 $c$ 票都会投给参加者中编号最小的那个，最终赢家是票数最多的人中编号最小的。对于每个 $x\in[1,n]$，求出让 $i$ 成为最终赢家最少需要让多少人不参加。
## 思路
可以把 $c$ 直接加给 $a_1$，显然跟原题意是等价的。之后求出 $a$ 中最靠前的最大值编号 $k$，显然 $k$ 的答案为 $0$。

考虑其他 $x$ 的答案。由于 $a_x$ 本身已经不是最大值，并且即使是去掉目前最大的 $a_k$，这一部分也会加到编号最小的 $a_i$ 上，最大值一定不降。所以至少要将 $x$ 之前的 $x-1$ 个人全部去掉，才能使 $x$ 为编号最小，$a_x$ 增加以变为最大。

所以维护 $a$ 的前缀和 $s$，若 $s_x\ge a_k$，只需要把前面全去掉即可，答案为 $x-1$。否则需要把前面全去掉，并且把 $x$ 后面的最大值 $a_k$ 也去掉，答案为 $x$。
## 代码
```cpp
#include<iostream>
#define int long long 
using namespace std;
const int N=2e5+10;
int n,c,mx,a[N],s[N];
void sol()
{
	cin>>n>>c;
	for(int i=1;i<=n;i++) cin>>a[i];
	a[1]+=c,mx=1;
	for(int i=1;i<=n;i++)
	{
		s[i]=s[i-1]+a[i]; 
		if(a[mx]<a[i]) mx=i;
	}
	for(int i=1;i<=n;i++) cout<<(i==mx?0:(s[i]>=a[mx]?i-1:i))<<' ';
	cout<<'\n';
}
signed main()
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	int T; cin>>T;
	while(T--) sol();
	return 0;
}
```

---

## 作者：int_R (赞：2)

分类讨论 $i$ 是不是存活的最小的编号，即能不能使没投票的人把票投给他。

- 是编号最小的

要求编号小于 $i$ 的全部都被排除了，此时 $i$ 得到的票数是 $c+\sum\limits_{j=1}^i a_i$，同时要不断找出后面最大的值加到 $i$ 的票数上，直到 $i$ 的票数大于等于后面最大的值。

由于前缀和是单调递增的，所以可以反过来从 $n$ 扫到 $1$，这样每个后面被排除掉的之后一定都会被排除。维护后面一个堆，不断模拟，在算完 $i$ 之后把 $a_i$ 也放到堆里。

- 不是编号最小的

要把所有值比他大的人全部排除掉，那么这样没投票的人就已经比他的值大了，而我们又钦定他不会是编号最小的，那么他就不会获胜。

所以这种情况只存在一个人，就是没有排除过任何人，本来值就最大的人，特判这种情况。

```cpp
inline bool cmp(node x,node y)
    {return x.a!=y.a?x.a>y.a:x.pos<y.pos;}
inline void work()
{
    cin>>n>>c;ll tmp=c;
    for(int i=1;i<=n;++i)
        cin>>a[i],p[i]={a[i],i},s[i]=a[i]+s[i-1],vis[i]=0;
    priority_queue <ll> q;int cnt=n-1;
    for(int i=n;i;--i)
    {
        while(!q.empty()&&c+s[i]<q.top())
            ++cnt,c+=q.top(),q.pop();
        ans[i]=cnt,q.push(a[i]),--cnt;
    }
    sort(p+1,p+1+n,cmp);c=tmp;
    if(p[1].pos>1&&c+a[1]<p[1].a) ans[p[1].pos]=0;
    for(int i=1;i<=n;++i) cout<<ans[i]<<' ';
    cout<<'\n';return ;
}
```

---

## 作者：CarroT1212 (赞：1)

纪念一下这道送我 $-87$ 的 Div2D。在最后十分钟才和出题人对上电波，五分钟写完，结果因为求后缀 $\max$ 的时候从前到后遍历寄了。

------------

首先注意不确定的票数是加在第一个没有被删的人上面，而不是票数最少的。这玩意场上耗了我二十分钟，直到 clarifications 出现。（题面用 index 表示出现位置会死吗？）

最开始自带的那个 $c$ 并没有很大的影响，我们直接把它加 $a_1$ 上面再做即可。

设我们现在要求第 $p$ 个人的答案。先考虑第 $p$ 个人在删完之后是第一个的情况。那么我们必定要把 $p$ 之前的所有人删掉，这时所有不确定的票数都加到了 $p$ 上面。如果这时它是序列的最大值就直接完事，否则我们需要把它后面的某一些人也删掉，同时把多出来的票数也加给 $p$。显然我们优先删后面最大的数更优。

场上在最后十分钟发现问题之前我一直在想我到底要不要直接开始线段树上二分。但是需要注意一点：如果你优先删了最大的数，那么这些票数就变成你的了，你还用担心有别的数比你大吗？所以如果还要删，直接删一个最大值就结束了。

第 $p$ 个人删完不是第一个的情况同理，可以发现这种情况只会发生在 $p$ 它自己就是最大值，否则最大值肯定要被删去，删去之后会加在第一个数上面，而第一个数又不是 $p$，完蛋了。

综上：

+ 如果第一个最大值是 $p$，答案为 $0$。
+ 如果 $p$ 与它前面的数的和不小于最大值，答案为 $p-1$。
+ 否则，答案为 $p$。

---

## 作者：Phartial (赞：0)

幽默 2D。

先判掉原先就是冠军的情况，否则就有两种可能：

1. 冠军没被干掉：那么为了超过冠军，我们必须吃到 $c$ 的加成，于是需要干掉 $1\sim i-1$ 中的所有人，如果此时 $i$ 超越冠军的话就只需要干掉 $i-1$ 个人；
2. 冠军被干掉：那么冠军的选票就会到 $c$ 里面，于是 $1$ 肯定成了新的冠军，也需要干掉，以此类推，我们还是需要干掉 $1\sim i-1$ 中的所有人，那么此时 $i$ 就肯定是冠军了，总共需要干掉 $i$ 个人。

然后就做完了。注意这个冠军的计算是需要让 $1$ 吃到 $c$ 的加成的。

```cpp
#include <iostream>

using namespace std;
using LL = long long;

const int kN = 2e5 + 1;

int tt, n;
LL c, a[kN];

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  for (cin >> tt; tt--;) {
    cin >> n >> c;
    int mxi = 0;
    for (int i = 1; i <= n; ++i) {
      cin >> a[i];
      if (i == 1) {
        a[1] += c;
      }
      if (a[i] > a[mxi]) {
        mxi = i;
      }
    }
    a[1] -= c;
    for (int i = 1; i <= n; ++i) {
      if (i == mxi) {
        cout << "0 ";
      } else if (a[i] + c >= a[mxi]) {
        cout << i - 1 << ' ';
      } else {
        cout << i << ' ';
      }
      c += a[i];
    }
    cout << '\n';
  }
  return 0;
}
```

---

## 作者：Lu_xZ (赞：0)

**D		\*1557**

首先，初始排名最大的不需要删人。

如果编号为 $i$ 的人初始不是最大，必需要把 $1\sim i - 1$ 全部删掉，否则分数加不到他头上。

此时 $i$ 的总分为 $\sum_{i = 1}^n a_i$，检查这个数是否大于等于 $i + 1\sim n$ 的最大值。

如果成立，那么 $i$ 此时就是最大的，需要删 $i - 1$ 次。

否则还要把 $i + 1 \sim n$ 里最大的加到自己头上，需要删 $i$ 次。

```cpp
void solve() {
	cin >> n >> c;
	for(int i = 1; i <= n; ++ i) {
		cin >> a[i];
	}
	a[1] += c;
	suf[n + 1] = 0;
	for(int i = n; i >= 1; -- i) {
		suf[i] = max(suf[i + 1], a[i]);
	}
	int p = 0;
	for(int i = 1; i <= n; ++ i) {
		if(suf[1] == a[i]) {
			p = i;
			break;
		}
	}
	ll cur = 0;
	for(int i = 1; i <= n; ++ i) {
		if(i == p) {
			cout << 0 << ' ';
		}
		else if(a[i] + cur >= suf[i + 1]) {
			cout << i - 1 << ' ';
		} 
		else {
			cout << i << ' ';
		}
		cur += a[i];
	}
	cout << '\n';
}
```

---

## 作者：Targanzqq (赞：0)

### 一道清奇贪心
首先这个题有一个性质，用好这个性质是解题的关键。

当一个的数被删除后，最前面的数会加上所有**已删除的数**的值。所以我们考虑到第 $j$ 个数大于等于当前数的时候，假设当前为第 $i$ 个数，我们去掉第 $j$ 个数以后，假设当前序列开头为 $k(k\not =i)$，则有 $a_k=a_k+a_j>a_i$。以此类推，我们需要去除前面所有数，使得被加上这些值的是第 $i$ 个数本身，才能使得这个数**可能**满足条件。

所以我们先扫一遍，如果前面有数**大于等于**当前数，或后面有数**大于**当前数，或第一个数加上 $c$ **大于等于**当前数，就把当前数前面的数都删除（即让答案加上这个数前面的数的个数）。

扫完之后，如果后面有数仍大于这个数，我们如果将这个数去除，那么加上这个数值的一定是当前数。我们可以贪心的去除后面最大的数，那么当前数加上这个数以后，一定比后面的所有数大（因为加上的这个数本身就比后面的数大）。

### 源代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int t,n,c,a[200005],maxn[200005],maxb[200005],pre[200005];

signed main(){
	ios::sync_with_stdio(false);
	cin>>t;
	while(t--){
		cin>>n>>c;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			pre[i]=a[i]+pre[i-1];
		}
		for(int i=n;i>=1;i--){
			maxn[i]=max(maxn[i+1],a[i]);
		}
		for(int i=1;i<=n;i++){
			maxb[i]=max(maxb[i-1],a[i]);
		}
		for(int i=1;i<=n;i++){
			int ans=0;
			int flag=0;
			if(a[1]+c>=a[i]||a[i]<=maxb[i-1]||a[i]<maxn[i+1]){
				ans+=i-1;
				flag=1;
			}
			if(a[i]+flag*(pre[i-1]+c)<maxn[i+1]){
				ans++;
			}
			cout<<ans<<" ";
		}
		for(int i=1;i<=n;i++){
			maxn[i]=0;maxb[i]=0;
		} 
		cout<<endl;
	}
}

```

---

## 作者：Dtw_ (赞：0)

[cf](https://codeforces.com/contest/1978/problem/d)
# 题目大意
有 $N$ 个人，有 $A_i$ 个人给他投票，有 $c$ 个人是自由人会投给当前可投给的编号最小的人，每人一票，可以踢人，如果把第 $i$ 人踢了，那他就不可被投票了，且这 $A_i$ 个人也会变成自由人。票数最多的人获胜，如果有同样多的，编号最小的人获胜，求 $1$ 到 $n$ 中对于每个人来说，他想获胜至少要踢掉几个人。

# 思路
首先容易想到，如果对于我前面的比我大的我一定会把他们全踢掉，因为只要有一个比我大，把他踢掉后，他的那些票会给我之前的剩余的人，只有把我前面的全部踢掉，那些票才能给我，我才能赢。

然后考虑我后面的，如果有人大于我，我一定也会把他踢掉，而他的票又会投到我前面的人去，所以综上，如果我一开始就不行，那无论是我前面的比我大还是我后面的比我大，我都一定会把前面 $i-1$ 个人全踢掉，同时我在看后面的，如果有比我大的，那我的答案只需要在加 $1$ 就行，因为我可以找到我后面最大的那个人，把他踢掉，因为我前面没人了，所以那些票一定会投给我，然后就行了。

再梳理一下：

1. 看我一开始不踢人行不行。
2. 行的话就结束，否则把我前面的人全部踢掉。
3. 看我后面有没有人比我大。
4. 有的话加 $1$，因为我可以找到最大的那个，最大的那个已经比后面剩余的比我大的都要大，比如 $1,0,5,3$ 我是 $1$，我后面比我大的有 $3,5$ 我只需要把 $5$ 踢了，然后我就是最大的了，所以只需要加 $1$。

具体的实现，考虑找比我大的用前缀最大值，然后因为把人给踢了，所以我的值要加上前面被踢的 $i-1$ 个人的值，用前缀和优化一下就行了。

# Code
```cpp
#include<bits/stdc++.h>

using namespace std;

#define endl '\n'

#define TRACE 1
#define tcout TRACE && cout

#define IN(o) insert(o)

#define fi first
#define se second

#define int long long

#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

const int INF = 0x3f3f3f3f3f3f3f3f;

const int P = 998244353;

const int N = 2e5 + 10;

int n, c, a[N], b[N], s[N];

signed main()
{
	fst;
	int t;
	cin >> t;
	while(t--)
	{
		cin >> n >> c;
		for(int i=1; i<=n; i++)
		{
			a[i] = b[i] = s[i] = 0;
		}
		for(int i=1; i<=n; i++)
		{
			cin >> a[i];
			if(i == 1) a[i] += c;
			b[i] = max(b[i-1], a[i]);
			s[i] = s[i-1] + a[i];
		}
		// 前面的只要有比 i 大的那全删, 后面从最大的开始看, 是否大于现在的我
		for(int i=1; i<=n; i++)
		{
			int res = 0, x = a[i];
			if(a[i] > b[i-1] && a[i] >= b[n]) // 我比我前面的都严格大，比我后面的都不小于
			{
				// 一开始我就赢了，啥也不干
			}
			else
			{
				res += i - 1; // 把前面的人都踢了
				x += s[i-1]; // 我的值加上前面的值
				if(b[n] > x) res++; // 还是有比我大的，那就加 1
			}
			cout << res << " ";
		}
		cout << endl;
	}
	return 0;
}




```

---

