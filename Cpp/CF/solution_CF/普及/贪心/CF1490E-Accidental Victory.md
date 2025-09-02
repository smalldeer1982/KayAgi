# Accidental Victory

## 题目描述

A championship is held in Berland, in which $ n $ players participate. The player with the number $ i $ has $ a_i $ ( $ a_i \ge 1 $ ) tokens.

The championship consists of $ n-1 $ games, which are played according to the following rules:

- in each game, two random players with non-zero tokens are selected;
- the player with more tokens is considered the winner of the game (in case of a tie, the winner is chosen randomly);
- the winning player takes all of the loser's tokens;

The last player with non-zero tokens is the winner of the championship.

All random decisions that are made during the championship are made equally probable and independently.

For example, if $ n=4 $ , $ a = [1, 2, 4, 3] $ , then one of the options for the game (there could be other options) is:

- during the first game, the first and fourth players were selected. The fourth player has more tokens, so he takes the first player's tokens. Now $ a = [0, 2, 4, 4] $ ;
- during the second game, the fourth and third players were selected. They have the same number of tokens, but in a random way, the third player is the winner. Now $ a = [0, 2, 8, 0] $ ;
- during the third game, the second and third players were selected. The third player has more tokens, so he takes the second player's tokens. Now $ a = [0, 0, 10, 0] $ ;
- the third player is declared the winner of the championship.

Championship winners will receive personalized prizes. Therefore, the judges want to know in advance which players have a chance of winning, i.e have a non-zero probability of winning the championship. You have been asked to find all such players.

## 样例 #1

### 输入

```
2
4
1 2 4 3
5
1 1 1 1 1```

### 输出

```
3
2 3 4 
5
1 2 3 4 5```

# 题解

## 作者：UperFicial (赞：5)

# 贪心

### 前言

思维题。

个人感觉更偏向贪心。

题目链接：[$\text{Link}$](https://www.luogu.com.cn/problem/CF1490E)

### 题意简述

- 有 $n$ 个队伍，第 $i$ 个队伍有 $a_i$ 个货币。

- 有若干次比赛，每次比赛随机挑选两支存活的队伍，货币数少的队伍淘汰，并将全部货币转交给货币多的队伍。若两支队伍货币一样多，则随机选一支队伍获胜。

- 你需要求出哪些队伍可能获胜。

### 题目分析

单考虑一支队伍 $x$ ，有一个显然的贪心想法：把所有货币数比它少的队伍都消灭掉，再去从小到大地消灭其余的队伍。

这也就可以做一个 $O(n^2\log n)$ 的方法了，将货币数排好序后每个队伍都去贪一下，然后模拟，一旦遇到一个消灭不了的队伍就说明这个队伍已经玩完了。而在消灭比它小的队伍的过程中一波前缀和就可以搞定。

但是这个做法显然 $T$ 飞，需要优化。

假定 $a$ 已从小到大排好序。

设 $s$ 数组保留前缀和即 $s_i=\sum_{k=1}^ia_k$。

那么 $s_i$ 就可以表示为第 $i$ 支队伍消灭掉所有货币数比它小的队伍后的货币数总和。

然后就有一个很一眼的结论：如果第 $i+1$ 支队伍能胜利，$s_i\ge a_{i+1}$，那么第 $i$ 支队伍能胜利。

证明：如果第 $i+1$ 支队伍能胜利，那么说明它一开始在消灭完所有货币数比它小的队伍得到 $s_{i+1}$ 这些货币数量后就能胜利了；而如果 $s_i\ge a_{i+1}$，那么第 $i$ 支队伍能消灭第 $i+1$ 支队伍，则目前货币数总和为 $s_i+a_{i+1}$ 即 $s_{i+1}$，刚刚已经说过 $s_{i+1}$ 这些货币数量能胜利所以命题得证。

~~而大多题解光摆了结论并没有证明。~~

同理，如果 $i+1$ 支队伍能胜利，$s_i<a_{i+1}$，那么 $i$ 号队伍就不会胜利，而 $i$ 号队伍不会胜利的话，$i$ 号队伍以前的队伍都不会胜利。

刚刚的探讨都是在 $a$ 数组排好序的基础上，所以要先排序，在记录排好序后的 $x$ 号位置是排序前的哪支队伍，开个结构体就可以实现。

另外注意：

> 十年 $\text{CF}$ 一场空，不开 $\boxed{?}\ \ \boxed{?}$ 见祖宗。

具体细节见代码吧。

时间复杂度：$O(n\log n)$。

空间复杂度：$O(n)$。

[$code$](https://paste.ubuntu.com/p/Sz48NB4shx/)

[$AC$ 记录](https://www.luogu.com.cn/record/46874577)

$$\texttt{The End.by UF}$$

---

## 作者：Gokix (赞：2)

[CF1490E](https://www.luogu.com.cn/problem/CF1490E)

------

这里提供一个好思考、好理解的做法：

首先我们把序列按能量由小到大排序。排序后的序列记作 $a$ 。

考虑如果一个人想拿第一，他必须与现存能量最小的人比赛，然后吸收他们的能量。接着重复这个过程，直到赢下 $a_n$ ，成为第一。

所以就有一个显然的结论：**如果 $a_i$ 不能取得第一，那么 $a_j(1 \le j <i)$ 也不可能取得第一 。**

证明显然。如果你的初能量小于我的初能量，那我能吸收的人的能量肯定大于等于你能吸收的能量。等于当且仅当你在某场比赛时吸收了我的能量。所以我的能量最终都无法赢下第一，那你就更不可能了。

因此我们就有了一个计算的方向：从 $a_n$ 倒着跑。一旦某个 $a_i$ 被判定为不可能，那就终止循环直接输出答案。

-----

接下来说一下如何判定 $a_i$ 能不能拿第一。

之前说了如果一个人想拿第一的策略，但是如果我们直接按着这个思路这么想不太好做。那么我们就考虑如果一个人最终拿不了第一会怎样？

**如果 $a_i$ 拿不了第一，那一定存在一个 $j>i$，使得 $\sum{a_u}(1 \le u <j) > a_i$。**

解释一下，就是有一个 $a_j$ 在你吸收了 $a_1$ ~ $a_{j-1}$ 所有的能量后也干不过它。那你也干不过之后的人，所以你也拿不了第一。

然后你发现这个东西一个前缀和就秒了。然后这个题就A了。

------------

CODE:

$a.id$ 是序列 $a$ 的编号。

$a.w$ 是序列 $a$ 的能量。

$f$ 是前缀和。

$b$ 是输出数组。

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
long long t,n,f[200010],b[200010],tot;
struct node
{
	long long id,w;
}a[200010];
bool cmp(node u,node v)
{
	return u.w<v.w;
}
int main()
{
	long long i,j,u,v;
	cin>>t;
	while(t--)
	{
		cin>>n;
		memset(a,0,sizeof(a));
		memset(f,0,sizeof(f));
		tot=0;
		for(i=1;i<=n;i++)//输入
		{
			cin>>a[i].w;
			a[i].id=i;
		}
		sort(a+1,a+n+1,cmp);
		for(i=1;i<=n;i++)//前缀和
		{
			f[i]=f[i-1]+a[i].w;
		}
		for(i=n;i>=2;i--)//核心代码
		{
			if(f[i-1]<a[i].w)//判断能否拿第一
			{
				break;//如果你不行那比你小的更不行，直接break
			}
		}
		for(j=i;j<=n;j++)//以下是输出
		{
			tot++;
			b[tot]=a[j].id;
		}
		sort(b+1,b+tot+1);
		cout<<tot<<endl;
		for(i=1;i<=tot;i++)
		{
			cout<<b[i]<<" ";
		}
		cout<<endl;
	}
	return 0;
}
```

完结撒花！

---

## 作者：SegTree (赞：1)

对于一支队伍，当它挑完所有比它值更小的，然后再往后判断是否能继续加入后面的值，如果该操作实现到末尾，那么就是可行的。

上面做法的时间复杂度为 $\mathcal{O}(n^2)$，无法通过本题。考虑优化。

对于一支比它值更大的队伍，它能操作实现到的下标一定不小于那个值更小的队伍的下标，故可以使用双指针优化。

时间复杂度 $\mathcal{O}(n \log n)$，因为需要对于队伍排序所以带一只 $\log$。

[submission.](https://codeforces.com/contest/1490/submission/214628500)

---

## 作者：jiang_cheng (赞：1)

## 解题思路：
看到一道题，先想出暴力解法，再做优化。首先考虑排序一遍，然后枚举每一个人的能不能成为赢家，做着做着，发现一个规律：如果排序之后第$i$个人能成为赢家，且$j$在$i$的后面，则第$j$个人也一定能成为赢家.

于是，我们的思路就进化了：排序一遍（记得记录每个人编号），维护一个指针，从前往后扫，计算代币的前缀和，如果这当前个人的代币大于前面代币和，则将指针更新到当前这个人。有可能成为赢家的人数就是总人数减去当前指针所在位置再加一。有可能成为赢家的人就是指针所在位置及以后的人。(管理员大大最帅啦！！！）
## 附上代码：
```cpp
#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

const int kMaxN = 2e5 + 1;

int t, n, k;  //k为指针
long long m;  //前缀和
struct E {
  long long a;  //代币数
  int i;        //编号
} e[kMaxN];

bool C(E e1, E e2) {
  return e1.a < e2.a;
}  //结构体比较，比较代币数量

bool B(E e1, E e2) {
  return e1.i < e2.i;
}  //比较编号先后

int main() {
  cin >> t;
  while (t--) {
    cin >> n;
    k = 0, m = 0;  //初始化指针和前缀和
    for (int i = 1; i <= n; i++) {
      cin >> e[i].a;
      e[i].i = i;
    }
    sort(e + 1, e + n + 1, C);  //排序
    for (int i = 1; i <= n; i++) {
      if (m < e[i].a) {
        k = i;  //如果当前这个人的代币数大于前面的代币和，就更新指针
      }
      m += e[i].a;  //计算前缀和
    }
    cout << n - k + 1 << endl;  //有可能成为赢家的人数
    sort(e + k, e + n + 1, B);  //编号排序
    for (int i = k; i <= n; i++) {
      cout << e[i].i << " ";  //输出编号
    }
    cout << endl;
  }
  return 0;
}
```


---

## 作者：registerGen (赞：1)

[宣传一下这次 div3 的题解](https://registergen.github.io/post/solution-codeforces-round-702-div-3/)

先将 $a$ 从小到大排序。

如果 $a_1<a_2$，则 $a_1$ 一定 GG。

如果 $a_2+a_1<a_3$，则 $a_2$ 一定 GG。否则，$a_2$ 就可能将 $a_1$ 吞并，然后将 $a_3$ 吞并，然后跟 $a_4$ PK。如果 $a_2+a_1+a_3<a_4$，则 $a_2$ GG，否则就接着吞并 $a_4$……

这样我们就能得到一个结论：

如果 $\exists k\ge t,\text{s.t. }\displaystyle\sum_{i=1}^k a_i<a_{k+1}$，则 $a_t$ 一定 GG。

处理前缀和然后模拟即可。

```cpp
int n,a[N+10];
ll sum[N+10];
int anss[N+10];
 
void solve(){
	std::multimap<int,int> M;
	n=ri();
	rep(i,1,n)a[i]=ri(),M.insert(mp(a[i],i));
	std::sort(a+1,a+n+1);
	rep(i,1,n)sum[i]=sum[i-1]+a[i];
	int pos=-1;
	rep(i,1,n-1)
		if(sum[i]<a[i+1]){
			pos=i; // 现在，a_1 到 a_pos 都一定 GG 了
		}
	if(pos==-1){
		printf("%d\n",n);
		rep(i,1,n)
			printf("%d ",i);
		puts("");
		return;
	}
	int totans=0;
	for(std::multimap<int,int>::iterator it=M.begin();it!=M.end();it++){
		if(it->first>a[pos])anss[++totans]=it->second;
	}
	std::sort(anss+1,anss+totans+1);
	printf("%d\n",totans);
	rep(i,1,totans)
		printf("%d ",anss[i]);
	puts("");
}
```

---

## 作者：云浅知处 (赞：1)

[珂能并不会有更好的阅读体验](https://yunqian-qwq.github.io/post/solution-cf1490e)

------------

### Description

[题目 Link](https://codeforces.com/problem/1490/E)

>- 有 $n$ 个人，第 $i$ 个人的实力为 $a_i$。
>- 要进行 $n-1$ 场比赛，每场比赛淘汰一个人，最后留下的人是赢家。
>- 每场比赛都会从现有的人中间随机选取两个人 $p,q$，如果 $a_p>a_q$，则 $p$ 获胜，$q$ 淘汰，并且 $a_p$ 变成 $a_p+a_q$。
>- 如果 $a_p=a_q$，那么两人都可以赢，此时输赢随机。
>- 若 $a_p<a_q$，与 $a_p>a_q$ 类似。
>- 现在，给定 $n$ 个人的实力，求有多少个人可能会赢，他们分别是谁。
>- 需要先输出可能会赢的人数，再按照升序输出可能赢的人的编号。
>- $t$ 组数据，$1\le t\le 10^4,\sum n\le 2\times10^5,a_i\le10^9$。

------------

先排序，排成升序（排序之前先记录一下每个数的编号）。

然后如果前 $k$ 个加起来都没第 $k+1$ 个大，那前 $k$ 个肯定都没机会赢。

并且注意到这个东西一定是最大的一些数能赢qwq。

毕竟不可能出现 $a_i<a_j$ ，但是 $i$ 可能赢，$j$ 不可能赢这种嘛awa。

就像您比云浅强，不考虑其他因素，那么不可能云浅能1=但是您无论如何都1=不了（

那记录一个指针，指针后面的数都是能赢的，前面都是不可能赢的。

从前往后扫一遍，同时记录前缀和，如果前缀和小于后面的单独一个数自己，说明前面这一堆都不可能赢了，指针后移。

复杂度 $O(n\log n)$。

哦对，还有一个事：

既然记录了前缀和，那么最多会到：

$10^9\times(2\times10^5)=2\times10^{14}>2^{31}-1$

所以，一定要！！！！开 `long long`！！！！！！

```cpp
#include<cstdio>
#include<algorithm>
#include<cctype>

#define int long long

using namespace std;

struct Node{
    int val,id;
};

bool cmp(Node p,Node q){
    return (p.val==q.val)?(p.id<q.id):p.val<q.val;
}

int t,n;
Node a[200005];
int b[200005];

signed main(void){

    scanf("%d",&t);
    while(t--){
        
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i].val);
            a[i].id=i;
        }
        
        sort(a+1,a+n+1,cmp);
        int sum=0,k=1;
        for(int i=1;i<n;i++){
            sum+=a[i].val;
            if(sum<a[i+1].val)k=i+1;
        }
        printf("%d\n",n-k+1);
        
        int cnt=0;
        for(int i=k;i<=n;i++){
            b[++cnt]=a[i].id;
        }
        sort(b+1,b+cnt+1);
        
        for(int i=1;i<=cnt;i++)printf("%d ",b[i]);
        puts("");
    }

    return 0;
}
```

---

## 作者：二gou子 (赞：1)

## 题目大意

将任意两个数作比较，大的数会加上小的数，而小的数则会变为$0$，如果两个数相同，则选择其中一个数加上另一个数，另一个数变为$0$，两个数中的任意一个数都有可能被选中。问哪些数有可能使其它所有的数都变为$0$后使自己不为$0$。

## 思路

我们发现，对于任意一个数，比它小和跟它等大的数都有可能被它累加，从而使自己“存活”的概率更大。此题问的是是否**有可能**，那也就是说一个数如果想让自己笑到最后，那必然是要把比它小的数和和它一样大的数都“吸收”，然后继续跟更大的数比较。

代码实现比较简单，只需要将数列从小到大排个序，预处理出前缀和，然后当两个相邻的数不一样，则看看较小的数之前的前缀和是否大于等于较大的那个数。如果大于则能继续“吸收”，反之小于则不行。但要注意的是：**如果某一处前缀和小于较大的数，那么从这个位置往前的更小的数肯定没有活到最后的希望**。所以我们要倒着循环，当有不可能活到最后的数出现就跳出循环，输出答案。时间复杂度就是排序的复杂度。

## Code
```C++
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<queue>
#include<cstring>
#define ll long long
using namespace std;
int t,n,tot;
ll sum[2000005];
int ans[2000005];
struct Node{
	int num;
	ll val;
}a[2000005];
bool cmp(Node x,Node y){
	return x.val<y.val;
}
int sol(int x){
	int p=x;
	while(a[p].val==a[p-1].val){
		ans[++tot]=a[p].num;
		p--;
	}
	ans[++tot]=a[p].num;
	return p;
}
int main()
{
	scanf("%d",&t);
	while(t--){
		tot=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%lld",&a[i].val);
			a[i].num=i;
		}
		sort(a+1,a+1+n,cmp);
//		for(int i=1;i<=n;i++){
//			printf("%d %lld\n",a[i].num,a[i].val);
//		}
		for(int i=1;i<=n;i++){
			sum[i]=sum[i-1]+a[i].val;
		}
		sol(n);
		for(int i=n;i>=1;i--){
			if(a[i].val!=a[i-1].val){
				if(sum[i-1]>=a[i].val){
					i=sol(i-1)+1;
				}
				else{
					break;
				}
			}
		}
		printf("%d\n",tot);
		sort(ans+1,ans+1+tot);
		for(int i=1;i<=tot;i++){
			printf("%d ",ans[i]);
		}
		printf("\n");
	}
	return 0;
}
```
（由于$Div3$时间较紧，代码比较混乱，但思路才是主要的）

---

## 作者：nb_jzy (赞：0)

# 题意

- 每次选择两支队伍，金币数量大的那一方获胜，并获得败者的所有金币数量。

- 询问有几组队伍可以获胜。

# 思路

很好想，如果一个队伍想要获胜，**他一定会先打比金币自己要少的队伍**。

再进一步想，他肯定从**数量最小**的那只队伍开始打，然后金币数不断累加，最终**累加起来的和**如果大于了 boss（金币数最多的那支队伍），他就一定可以获胜。

# 做法

思路都出来了，敲代码呗。

现将队伍按金币数量排序，然后统计一个前缀和。

$$ sum_i= \sum _{j=1}^ia_j $$

接着我们就看 $sum_i$ 是否可以满足题意即可。

可以用二分实现，及二分在哪个位置可以满足题意，那他后面的位置肯定也行。

时间复杂度 $\mathcal{O}(n\times \log n)$。
# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,ans[200005],cnt;
long long sum[200005];
struct person{
	long long w;
	int id;
}a[200005];
bool cmp(person x,person y){
	return x.w<y.w;
}
bool check(int x){//check 函数，按题意模拟
	long long ans=sum[x];
	for(int i=x+1;i<=n;i++){
		if(ans>=a[i].w){
			ans+=a[i].w;
		}
		else return 0;
	}
	return 1;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i].w,a[i].id=i;
		sort(a+1,a+n+1,cmp);
		for(int i=1;i<=n;i++){
			sum[i]=sum[i-1]+a[i].w;
		}
		int l=1,r=n;
		while(l<=r){//二分
			int mid=(l+r)>>1;
			if(check(mid)) r=mid-1;
			else l=mid+1; 
		}
		cnt=n-l+1;
		cout<<cnt<<endl;
		for(int i=1;i<=cnt;i++){
			ans[i]=a[l+i-1].id;
		}
		sort(ans+1,ans+cnt+1);//按照顺序输出答案
		for(int i=1;i<=cnt;i++){
			cout<<ans[i]<<" "; 
		}
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：__LiChangChao__ (赞：0)

## 思路
由于要求**有可能获胜**，考虑**贪心**。

假设数据已经排序，考虑一个性质：假设一个队伍的代币比它前面所有人的和（即前缀和）都大，那么前面的人无论什么顺序都一定赢不了（无论如何都小于这个队伍）。

于是剩下的人自然就是答案。

注意：输出时还要对编号进行**排序后输出**。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=200005;
long long t,n,m1,m2,sum,s[maxn],d[maxn];
struct node{
	int id,s;
}a[maxn];
inline bool cmp(node a,node b){
	if(a.s==b.s)return a.id<b.id;
	return a.s<b.s;
}
int main() {
	scanf("%lld",&t);
	while(t--) {
		s[0]=0;
		sum=0;
		m1=INT_MAX,m2=-1;
		scanf("%lld",&n);
		for(int i=1; i<=n; i++)scanf("%lld",&a[i].s),a[i].id=i;
		sort(a+1,a+n+1,cmp);
		for(int i=1; i<=n; i++) {
			s[i]=s[i-1]+a[i].s;
		}
		for(int i=n;i>=1;i--){
			d[++sum]=a[i].id;
			if(a[i].s>s[i-1])break;
		}
		printf("%lld\n",sum);
		sort(d+1,d+sum+1);
		for(int i=1;i<=sum;i++)printf("%lld ",d[i]);
		puts("");
	}
}

```

---

## 作者：清烛 (赞：0)

挂一下 [My Blog](https://imyangty.com/oi/1309)
### 题意
一场锦标赛中有 $n$ 个选手，第 $i$ 个选手一开始有 $a_i$ 个 token。进行 $n - 1$ 场比赛。每场比赛随机抽取两个 token 不为 $0$ 的选手，token 大的一方为胜方，（token 相同则胜方随机选一个），胜方会拿走败方的所有 token。最后会产生一位冠军。

很明显，冠军是谁与每场比赛选取的选手有很大关系。**升序**输出**有可能**成为冠军的选手的编号。

### 题解
我们考虑一个选手如何能成为冠军。容易构造出一种方案：

- 首先先跟所有 token 小于等于自己的选手打若干场然后作为胜方拿走他们的 token
- 然后转战 token 大于自己的初始 token 的选手，从小往大打，如果能打得过所有选手他就成冠军

第一步肯定是能够实现的（除非是 token 垫底的那个选手），关键就在于他拿了所有比自己弱的选手的 token 之后能不能打得过那些比自己一开始强的选手。

考虑到这里，我们很自然的会先把所有选手按照 token 从小到大排个序再求一个前缀和。记排序过后的第 $i$ 个选手的 token 为 $b_i$，前缀和为 $s_i$。不难发现如果 $s_i \ge b_{i + 1}$ 的话这个选手就有机会打赢第 $i + 1$ 个选手。然后他现在有的 token 即为 $s_{i + 1}$。看到这里“第 $i$ 个选手能不能赢”的问题就已经被转化成了“第 $i+1$ 个选手能不能赢”的问题了，不难归纳出如下结论：

**如果第 $i$ 个选手能成为冠军，并且 $b_i \le s_{i - 1}$，那么第 $i -1$ 个选手也能成为冠军**。说明如果第 $i$ 个选手没机会成为冠军，那么初始 token 比他低的也**都没有机会了**。

所以直接建结构体排序就可以了。

如果你 WA on test 3，就像我在比赛过程中一样，大概率你没有**开 `long long`**

```cpp
int sum[maxn];

struct node
{
    int val, id;
    node(){}
    node(int v, int i) {val = v, id = i;}
} a[maxn];

bool cmp1(node a, node b)
{
    return a.val < b.val;
}

bool cmp2(node a, node b)
{
    return a.id < b.id;
}

signed main()
{
    int T = read();
    while (T--)
    {
        int n = read();
        FOR(i, 1, n) a[i].val = read(), a[i].id = i;
        std::sort(a + 1, a + 1 + n, cmp1);//按照 token 值排序
        FOR(i, 1, n) sum[i] = sum[i - 1] + a[i].val;//前缀和
        int ans = 0, cnt = 0;
        DEC(i, n, 1)//从最大的往最小的考虑
        {
            ++cnt;
            if (a[i].val > sum[i - 1])//遇到后面的都打不赢了的
            {
                ans = a[i].val;
                break;
            }
        }
        std::sort(a + 1, a + n + 1, cmp2);//按照编号重新排序
        printf("%d\n", cnt);
        FOR(i, 1, n)
            if (a[i].val >= ans)
                printf("%d ", i);//升序输出
        puts("");
    }
    return 0;
}
```

---

## 作者：xh39 (赞：0)

## 翻译
### 描述
$n$ 个人参加比赛,第 $i$ 人有 $a[i]$ 个币。

$(n-1)$ 次比赛,每次随机挑选 $2$ 人比赛,每次比赛币多的人胜利并拿走败者的所有币。败者被淘汰。

最后没被淘汰的人获得最终的胜利。

求可能获得最终胜利的人的编号。

### 输入格式

多组数据。

对于每组数据,第 $1$ 行 $1$ 个正整数 $n$ 表示人数。

第 $2$ 行 $n$ 个正整数表示初始币的个数。

### 输出格式

对于每组数据,第 $1$ 行 $1$ 个正整数表示可能获得最终胜利的人数。

第 $2$ 行从小到大输出可能获得最终胜利人的编号。空格隔开。



## 思路
先从小到大排序。如果小的能胜利,那么大的更能胜利。所以我们只需要找出最小的可以胜利的人即可。设这个数为 $minans$。

一个最简单的办法就是二分查找。这里讲一个更简单的做法。

一个人显然能赢比自己实力弱的所有人。所以用一个计数器统计所有比它小的数的和。

如果所有数的和还比不过下一个数,那么这个数肯定是没机会赢了。把 $minans$ 设为下一个数。

最后如果比 $minans$ 大就有机会赢,输出。

单组数据时间复杂度:$O(n\times \log_{2}(n))$。(排序带 $\log$)。
## 代码
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
long long a[1000005],b[1000005];
void Main(){
	long long n,i,sum=0,minans=0;
	cin>>n;
	for(i=0;i<n;i++){
		scanf("%lld",a+i);
		b[i]=a[i]; //为输出编号,还要用一个数组存储原来是什么样子。
	}
	sort(a,a+n);
	minans=a[0];
	for(i=0;i<n-1;i++){
		sum+=a[i];
		if(sum<a[i+1]){
			minans=a[i+1];
		}
	}
	sum=0;
	for(i=0;i<n;i++){
		if(b[i]>=minans){
			sum++;
		}
	}
	cout<<sum<<endl;
	for(i=0;i<n;i++){
		if(b[i]>=minans){
			cout<<i+1<<" ";
		}
	}
	cout<<endl;
}
int main(){
	long long t,i;
	cin>>t;
	for(i=0;i<t;i++){
		Main();
	}
	return 0;
}
```

---

## 作者：henrytb (赞：0)

首先一个人肯定有机会打败 $a$ 值 $\le$ 他的人（因为 $a$ 值相同的话是随机打败，总之有机会）。

因此我们先将 $a$ 数组排个序。

打败完了这么多人之后，我们设这个人位置为 $x$，他现在的 $a$ 值变成了所有 $a$ 值 $\le a_x$ 的人的 $a$ 值之和。

然后他打败了这么多人后还有机会接着向后打败，也就是说，如果现在这个人的 $a$ 值比后头一个人的 $a$ 值大，那么就可以往下继续滚雪球。但如果遇到当前 $a$ 值比后一个人的 $a$ 值小了，这个人就打败不了，后头的人也打败不了了。

也就是说我们肯定要先做个前缀和。

一个人要赢，肯定就是要打败所有人，意思就是他滚的雪球要滚到底。

所以我们从后往前推，如果说哪里遇到当前的前缀和比后一个人的 $a$ 值小了，那么就 `break` 掉，因为再往前的人都打败不了这个人了，雪球滚不下去。否则就继续循环。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
int _,n;
pair<int,int> a[200005];
int sum[200005];
bool ans[200005];
int b[200005];
map<int,int> summ,nxt;
signed main() {
    for(scanf("%lld",&_);_;--_) {
        summ.clear();nxt.clear();
        scanf("%lld",&n);
        rep(i,1,n) ans[i]=0;
        rep(i,1,n) b[i]=0;
        rep(i,1,n) {
            scanf("%d",&a[i].first);
            a[i].second=i;
        }
        sort(a+1,a+n+1);
        rep(i,1,n) {
            sum[i]=sum[i-1]+a[i].first;
            summ[a[i].first]=sum[i];
            if(a[i].first!=a[i-1].first) nxt[a[i-1].first]=a[i].first;
        }
        ans[a[n].second]=1;
        nxt[a[n].first]=0;
        per(i,n-1,1) {
            if(summ[a[i].first]>=nxt[a[i].first]) ans[a[i].second]=1;
            else break;
        }
        int qwq=0;
        rep(i,1,n) {
            if(ans[i]) ++qwq;
        }
        printf("%lld\n",qwq);
        rep(i,1,n) {
            if(ans[i]) printf("%lld ",i);
        }
        puts("");
    }
    return 0;
}
```

---

## 作者：_masppy_ (赞：0)

### 前言
 [题目传送门](https://www.luogu.com.cn/problem/CF1490E)

第一篇题解 awa

### 题意简述
- 有 $n$ 个人，每人有货币 $a_i$。

- 对这些人两两比较，货币多的人得到另一个人的货币，**若相同则随机分配给一人**。

- 问有哪些人可能获得所有货币。

### 解题思路
对于每个人，肯定优先从除他以外最小的人开始比较，所以一个人在和比他初始货币多的人比较之前肯定已经获得了货币数小于等于他的人的货币。

于是可以用结构体存储每个人的初始位置以及货币数 $a_i$ 并对货币数从小到大排序，之后处理序列的前缀和 $sum$。

对于 $i-1$ 和 $i$，假设他们的初始位置为 $j$ 和 $k$，同时 $i-1$ 能够战胜 $i$，则  $sum_{i-1}\geq a_k$，而对于这个 $i-1$，如果 $i$ 能够战胜 $i+1$，那么 $i-1$ 也可以。

于是，我们可以记录一个 $tag$，遍历序列，当遇到 $sum_{i-1}\geq a_k$ 时，若 $tag$ **为空**，则将 $tag$ 记为 $i-1$。而遇到 $sum_{i-1}<a_k$ 时，则将 $tag$ 清空。

将 $[1,n]$ 遍历过后，输出 $n-tag+1$，也就是可能获得所有货币的人的个数，然后将 $[tag,n]$ 的初始位置都推入数组并排序，然后**从小到大输出**。

时间复杂度约为 $O(n\log n)$。

```cpp
int main(){
   scanf("%d",&t);
	
   while(t--){
    	can=0;//前文的tag
    	scanf("%d",&n);
    	for(int i=1;i<=n;i++){
    		scanf("%lld",&a[i].x);
    		a[i].id=i;//记录初始位置
    	}
    	sort(a+1,a+1+n,cmp);//从小到大排序
    	for(int i=1;i<=n;i++){
    		sum[i]=sum[i-1]+a[i].x;
    		if(i>1&&sum[i-1]>=a[i].x&&!can){//i-1能够战胜i且can为空
    			can=i-1;
			}
			if(i>1&&sum[i-1]<a[i].x){//清空
				can=0;
			}
		}
		if(!can){//当tag为空时代表只有n能够获得全部货币
			printf("1\n");
			printf("%d\n",a[n].id);
			continue;
		}
		
		printf("%d\n",n-can+1);//人数
		cnt=0;
		for(int i=can;i<=n;i++){
			out[++cnt]=a[i].id;//将[tag,n]的初始位置推入数组
		}
		sort(out+1,out+1+cnt);//排序
		for(int i=1;i<=cnt;i++){
			printf("%d ",out[i]);//输出
		}
		printf("\n");
    }
    return 0;
}
```

撒花撒花

---

