# Tokitsukaze, CSL and Stone Game

## 题目描述

Tokitsukaze 和 CSL 正在玩一个石子游戏。

一开始有 $n$ 堆石子，第 $i$ 堆有 $a_i$ 个石子。两位玩家轮流操作，Tokitsukaze 先手。每次操作时，玩家选择一个非空的石子堆，从中取出恰好一个石子。如果在某位玩家操作前，所有石子堆都已经为空，或者在取走石子后，出现了两堆（可以为空）石子数量相同，则该玩家输掉游戏。假设两位玩家都采取最优策略，谁会赢得游戏？

举个例子：$n=3$，各堆石子数为 $a_1=2$，$a_2=3$，$a_3=0$。不能选择空堆，所以 Tokitsukaze 有两种选择：第一堆或第二堆。如果她选择第一堆，状态变为 $[1, 3, 0]$，这是一个好选择。但如果她选择第二堆，状态变为 $[2, 2, 0]$，她会立即输掉。因此她唯一的好选择是选择第一堆。

假设两位玩家始终采取最优策略且不会失误，谁会赢得游戏？

注意，即使一开始有两堆石子数量相同，Tokitsukaze 仍然可能有合法的第一步操作。只要在她操作后，没有两堆石子数量相同即可。

## 说明/提示

在第一个样例中，Tokitsukaze 无法取任何石子，因此 CSL 获胜。

在第二个样例中，Tokitsukaze 只能从第一堆取一个石子，此时两堆石子数相同，因此 CSL 获胜。

在第三个样例中，Tokitsukaze 会获胜。以下是一种最优操作方式：

- 首先，Tokitsukaze 选择第一堆，取走一个石子。
- 然后，CSL 只能选择第一堆，因为如果他选择第二堆会立即输掉。
- 最后，Tokitsukaze 选择第二堆，CSL 无法再操作，只能输掉游戏。

在第四个样例中，每一步他们都只有一种合理的选择，因此 Tokitsukaze 可以让游戏持续到最后并获胜。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
1
0
```

### 输出

```
cslnb
```

## 样例 #2

### 输入

```
2
1 0
```

### 输出

```
cslnb
```

## 样例 #3

### 输入

```
2
2 2
```

### 输出

```
sjfnb
```

## 样例 #4

### 输入

```
3
2 3 1
```

### 输出

```
sjfnb
```

# 题解

## 作者：hsfzLZH1 (赞：10)

## 题目大意

有 $n$ 堆石子，第 $i$ 堆有 $a_i$ 个石子。两人轮流取走石子，每次只能且必须取走一堆中的 **一个** 石子。要求取完后不能出现有两堆石子数相同的情况。无法行动（没有石子可以取）的玩家判负。假设两人都按最优策略行动。

注意如果一开始就有两堆相同的石子，仍然会让先手进行合法行动。如果不能行动，仍然先手判负。

如果先手必赢，输出 `sjfnb` ；如果后手必赢，输出 `cslnb` 。

$1\le n\le 10^5,0\le a_i\le 10^9$

## 解题思路

一个人被判负，当且仅当他无法行动，此时石子堆的状态有以下几种情况（不妨认为我们已经将石子堆按照石子数从小到大排序）：

1. 有大于等于两对的相邻数相同；

2. 只有一对相邻数相同，但是仍然存在一堆石子的石子数是相同的数 $-1$ ，即取走一个后仍然会相同；

3. 没有相邻数相同，石子数形如 $0,1,2,...,n$ ，不能取走第一堆，任取其他一堆都会和已有的一堆相同。

可以发现，情况 $1,2$ 只有在一开始会出现，如果取走后出现这两种情况是不合法的，如果出现这两种情况后手胜利。

如果一开始不是 $1,2$ 两种情况，每次双方玩家都会取走 $1$ 颗石子，直到变为情况 $3$ ，此时要行动的玩家判负。一开始的石子数为 $\sum_{i=1}^n a_i$ ，最后的石子数为 $\sum_{i=0}^{n-1}i=\frac {n\times (n-1)} 2$ ，取走的石子总数为 $\sum_{i=1}^n a_i-\frac {n\times (n-1)} 2$ 。判断其奇偶性，若为奇数，则先手胜利；若为偶数，则后手胜利。

## 代码展示

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
const int maxn=100010;
ll n,a[maxn],ans,cnt;
int main()
{
    scanf("%lld",&n);
    for(int i=1;i<=n;i++)scanf("%lld",a+i),ans+=a[i];
    sort(a+1,a+n+1);
    for(int i=2;i<=n;i++)if(a[i]==a[i-1])cnt++;
    if(cnt>1){printf("cslnb\n");return 0;}
    if(cnt==1)for(int i=2;i<=n;i++)if(a[i]==a[i-1])
    {
    	if(i!=2&&a[i-2]==a[i-1]-1){printf("cslnb\n");return 0;}
    	if(a[i]==0){printf("cslnb\n");return 0;}
    }
    ans-=n*(n-1)/2;
    if(ans<=0)printf("cslnb\n");
    else if(ans&1)printf("sjfnb\n");
    else printf("cslnb\n");
    return 0;
}
```

---

## 作者：风格雨关 (赞：5)

 **博弈论?!**   
这里定义一个数组$cnt$,$cnt[i]$表有i个石子的石子堆有几堆.  
则当满足以下5种情况时,谁走谁**必败**:  
1. $cnt[x]\ge3$
2. $cnt[x]\ge2$ 且 $cnt[y]\ge2$
3. $cnt[x]\ge2$ 且 $cnt[x-1]\ge1$
4. $cnt[0]\ge2$
5. 石子堆成1,2,3~n-1的等差数列   



---

## 作者：Crazyouth (赞：4)

**分析**

容易想到，假如先手不是在开始的时候就输了，那么最终石子的序列一定是 $0,1,2,\dots,n-2,n-1$。这种情况我们只需要判断取走石子的奇偶性即可。

接下来看那些情况先手开始就输了。定义 $cnt_i$ 表示有 $cnt_i$ 堆石子的数量是 $i$ 个。

1. $cnt_0\ge2$，这种情况无论先手取什么下一步都会有两堆是 $0$，即他无法行动，输了。
2. 存在 $x$ 使 $cnt_x>2$，这种情况无论他取什么，下一步至少有两堆是 $x$。
3. 存在 $x,y$，使 $cnt_x\ge2$ 并且 $cnt_y\ge2$，这种情况不管他取等于 $x$ 的还是等于 $y$ 的一堆，另一个数量的都会有两堆。
4. 存在 $x$ 使 $cnt_x\ge2$ 且 $cnt_{x-1}\ge1$，这种情况他要是不取为 $x$ 的，为 $x$ 的就有两堆了，假如他取了，为 $x-1$ 的就有两堆了，依然会输。

假如出现这四种，就直接输出 `cslnb`，否则判断取走的奇偶性即可。

另外实现的时候需要一个 $vis$ 数组，统计是否判断过当前值得 $cnt$，不然会挂，因为我扫 $cnt$ 的时候是按 $a_i$ 看的，直接扫整个数组是不现实的。

**AC Code**
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[int(1e5+10)];
map<int,int> cnt,vis;//a[i]有1e9，用map存
int main()
{
	long long n,tp=0,sum=0;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		sum+=a[i];//统计a的和
		cnt[a[i]]++;
	}
	if(cnt[0]>1||cnt[0]==n)
	{
		cout<<"cslnb";//情况1成立或0的个数有n个（n比较小）
		return 0;
	}
	for(int i=1;i<=n;i++)
	{
		if(vis[a[i]]) continue;
		if(cnt[a[i]]>2)//第二种情况
		{
			cout<<"cslnb";
			return 0;
		}
		if(cnt[a[i]]>1) tp++,vis[a[i]]=1;//统计cnt大于等于2的个数，方便判情况3
		if(cnt[a[i]]>1&&cnt[a[i]-1]>0)//情况4
		{
			cout<<"cslnb";
			return 0;
		}
	}
	if(tp>1)//情况3
	{
		cout<<"cslnb";
		return 0;
	}
	if((sum-(n*(n-1)/2))%2) cout<<"sjfnb";//判奇偶性
	else cout<<"cslnb";
	return 0;
}

---

## 作者：cosf (赞：1)

## [CF1190B](https://codeforces.com/problemset/problem/1190/B)

[洛谷传送门](https://www.luogu.com.cn/problem/CF1190B)

---

## 思路

我们令 $c(x)$ 表示石子个数为 $x$ 的堆。

我们可以发现，当存在下列情况之一时，当前操作的人必败：

1. $c(0) \ge 2$。
2. $\exists x, c(x) \ge 3$。
3. $\exists x \not= y, c(x), c(y) \ge 2$；
4. $\exists x, c(x) \ge 1, c(x + 1) \ge 2$；
5. 当前的石子堆为 $0$ 到 $n-1$ 的一个排列，共有石子 $\sum_{i=0}^{n-1}i = \frac{n(n-1)}{2}$ 个。

显然，为了统计方便，我们可以给每堆石子从小到大排个序。

对于前 $4$ 种情况，都要求某种石子出现 $2$ 次或以上，所以在中间不可能出现，因为谁使局面满足前 $4$ 种情况谁就输了。

于是我们可以统计所有石子的和，令其为 $S$。若 $S \lt \frac{n(n-1)}{2}$，则此时必属于前 $4$ 种情况之一，读者可以自行证明。

若 $S \ge \frac{n(n-1)}{2}$，我们可以通过判断 $S-\frac{n(n-1)}{2}$ 的奇偶性来判断谁赢。

---

## 代码

```cpp
ll val[MAXN];

int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> val[i];
    }
    sort(val + 1, val + n + 1);
    int sc = val[1] == val[2];
    if (sc && !val[1]) // 情况 1
    {
        cout << "cslnb" << endl;
        return 0;
    }
    int sjf = true;
    for (int i = 1; i < n - 1; i++)
    {
        if (val[i] == val[i + 1] - 1 && val[i + 1] == val[i + 2])
        {
            sjf = false; // 情况 4
            break;
        }
        if (val[i + 1] == val[i + 2])
        {
            sc++;
        }
        if (sc >= 2) // 情况 2 & 3
        {
            sjf = false;
            break;
        }
    }
    if (!sjf)
    {
        cout << "cslnb" << endl;
        return 0;
    }
    ll sum = 0;
    for (int i = 1; i <= n; i++)
    {
        sum += val[i];
    }
    sum -= (n * (n - 1)) / 2;
    if (sum % 2 /* == 1*/)
    {
        cout << "sjfnb" << endl;
    }
    else
    {
        cout << "cslnb" << endl;
    }
}
```

---

话说 Tokitsukaze 应该比 CSL 难赢。


---

## 作者：伟大的王夫子 (赞：1)

首先我们看看题目。根据题意，如果刚开始就有两堆石子个数相同，那么必须取掉其中的石子。如果去完之后还有，那么先手输，否则就继续我们的算法

首先，我们将数组$a$排个序

先提一个引理:到最后每个石堆的石子数$a_i$都会变成$i-1$

这个引理的证明比较困难，我们可从几个简单的例子来找规律。

比如$a=\{1,2, 6\}$时，

取石子的几步是这样的

$1, 2, 6 \to1,2,5\to 1,2,4 \to 1,2,3\to0,2,3\to0,1,3\to0,1,2$

然后便可以取分胜负了，通过步数的奇偶性。

具体的，将数组$a$排序，判断$\sum_{i=1}^n {a_i -(i-1)}$的奇偶性。

如果刚开始有两堆石子相同，那么先手已经取过，奇偶性就取反即可

说实话，不要想多了，跟sg函数没什么关系。也许没学过博弈论还能更容易做出此题

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, a[100010];
bool flag;
int main() {
	cin >> n;
	for (register int i = 1; i <= n; ++i) cin >> a[i];
	sort(a + 1, a + n + 1);
	int cnt = 0;
	for (register int i = 1; i <= n - 1; ++i) {
		if (a[i] == a[i + 1] && a[i]) {
			--a[i], flag = 1;
			break;
		}
	}
	for (register int i = 1; i <= n - 1; ++i) {
		if (a[i] == a[i + 1]) {
			puts("cslnb");
			return 0;
		}
	}
	int num = 0;
	for (register int i = 1; i <= n; ++i) num += a[i] - (i - 1);
	if (flag) num ^= 1;//奇偶性的取反
	if (num & 1) puts("sjfnb");
	else puts("cslnb");
}
```

---

## 作者：KEBrantily (赞：1)

## 扯在前面

我们老师刚讲过的题目，很考验思维，本蒟蒻WA了十发才过，然后看到题解里只是指出了特殊情况没多解释，可能有人看不懂，特来分享一下

首先题目就很有意思，思考的过程也很有趣，想把所有情况思考全思考对是件很不容易的事


------------
# 正文

##  题意：

两人取n堆数量不定的石子，当某一方取完后剩下了两堆一样的或本轮无石子可取（当前石子数为0），则失败。问给出石子各堆的数量，求先手胜还是后手胜。

##  分析：

首先，站在博弈论的角度，或者说把自己当做参与者，思考一下什么情况下是对自己最有利的，也就是说什么情况下自己必胜

然后抱着这样的心态，我们可以手玩几组样例。

**我们就可以知道**：
1. 若场上有两堆石子，一堆数量多一堆数量少，那我们宁可取少的，因为那样出现取完后两堆相同的概率最低；

1. 当两边都这样想时，就会不停取，一直取到一种极端情况，那就是每堆石子的数量是以一递增的，那时游戏就结束了，因为不管再怎么取，都会出现两堆相同数量的石子（两堆0也是）；
1. 当场上已经有两堆相同的石子时，下一次操作的人必取两堆其中之一，因为他如果不取，取完后这两堆相同，他就输了；
1. 若刚刚那人取完后，场上仍存在两堆相同的，他还是输了，即当时还存在一堆石子数量是刚刚那两堆数量减一或场上存在另外两堆以上数量相同但与这两堆数量不同的石子
1. 若场上存在三堆及以上石子时，先手无论怎么取，都会输，原因同上

**然后可得出情况如下可以判断某方必胜：**

1. 场上石子数已经是按1递增的
1. 场上存在三堆及以上石子相等
1. 场上存在两堆石子相同且还有一堆石子数比这两堆少一
1. 场上存在两堆0

这些先判断出来，剩下的统计原来的石子总数与极端情况的石子总数之差，**若为偶数则后手赢，反之则先手赢**

# 代码
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<queue>
#include<algorithm>
#define maxn 1000100

using namespace std;

int n,a[maxn],tot,cnt,js;

int main(){
	scanf("%d",&n);
//	if(n==1 &&a[1]==0){
//		cout<<"cslnb";
//	    return 0;
//	} 
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		tot+=a[i];
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++){
		if(a[i]==a[i+1]) js++;
	}
	if(js>=2){
		cout<<"cslnb";//有两堆以上一样的时后手必赢 
		return 0;
	} 
	if(js==1){
		for(int i=1;i<=n;i++){
			if((a[i]==a[i+1] &&a[i-1]+1==a[i] && i!=1) ||(a[i]==a[i+1] &&a[i]==0)){
			cout<<"cslnb";//此时先手无所下手，后手赢 
		    return 0;
			}
		}
	} 
//	if(n==2 &&((a[1]==1&&a[2]==0) ||(a[2]==1 &&a[1]==0))){
//		cout<<"sjfnb";
//		return 0;
//	}
	for(int i=1;i<=n;i++){
		cnt+=i;
	}
	cnt-=n;
	if(tot-cnt==0){
		cout<<"cslnb";
		return 0;
	}
	if((tot-cnt)%2==0) cout<<"cslnb";
	else cout<<"sjfnb";
	return 0;
}
```
请批评指正

---

## 作者：naught (赞：0)

[更好的阅读体验](https://www.cnblogs.com/naughty-naught/p/18503180)

# Tokitsukaze, CSL and Stone Game

## 题外话

~~对于某些人说降绿甚至降黄，本人是很不同意的，毕竟多一道水蓝有什么不好。~~

## 题意

翻译得很简洁，不再赘述。

## Solution

不难发现有以下几种情况：

* 只有两堆不等的，肯定选少的那堆，因为这样不易使得两堆相等。

* 若两堆相等，一定破坏相等的情况，否则取完后就输了，若之后还有两堆相等的，还是输。

* 就一堆，先后手分别取。

* 若剩下的堆形成首项为 $0$ 的公差为 $1$ 的等差公式，那么操作者输，因为不论怎么操作一定会使得操作完后有两堆相等的。

* 有三堆，那么先手必输，原因由上述。

其余就是暴力实现了，看码力，详见代码。

## Code

```cpp
// written by Naught
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define Maxn 100005
#define fo(i, l, r) for (int i = l; i <= r; ++i)
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21], *p1 = buf, *p2 = buf;
inline int read(int x=0, bool f=0, char c=getchar()) {for(;!isdigit(c);c=getchar()) f^=!(c^45);for(;isdigit(c);c=getchar()) x=(x<<1)+(x<<3)+(c^48);return f?-x:x;}

int n, a[Maxn], sum, m;

int main()
{
    n = read();
    fo(i, 1, n) a[i] = read(), sum += a[i];
    sort(a + 1, a + n + 1);
    fo(i, 1, n) if(a[i] == a[i + 1]) ++m;
    if(m >= 2) return puts("cslnb"), 0;
    if(m == 1) fo(i, 1, n) if( (a[i] == a[i + 1] && a[i - 1] + 1 == a[i] && i != 1) || (a[i] == a[i + 1] && a[i] == 0) ) return puts("cslnb"), 0;
    m = 0;
    fo(i, 1, n) m += i;
    m -= n;
    if(sum - m == 0) return puts("cslnb"), 0;
    if(((sum - m) & 1) == 0) return puts("cslnb"), 0;
    else return puts("sjfnb"), 0;
    return 0;
}
```

---

## 作者：LYY_yyyy (赞：0)

首先将初始必败情况判掉：有出现次数超过三次的重复数字、有大于等于两种重复数字、只有一种重复数字 $k$ 但存在 $k-1$，有重复的 $0$。之后考虑必败态，我们发现必败态在排序后一定形如 $0,1,2,3,4,5,....n-1$，否则就一定有还可以操作的堆。于是我们就判一下初始局面和必败局面差值的奇偶性即可。

代码：
```cpp
#include<bits/stdc++.h>
#define lowbit(x) (x&(-x))
#define pb emplace_back
using namespace std;
int n;
int a[100010];
map<int,int> cnt;
int main()
{
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n;for(int i=1;i<=n;i++) cin>>a[i],cnt[a[i]]++;
	sort(a+1,a+n+1);int s=0,p=2e9;
	int ans=0;
	for(auto o:cnt)
	{
		if(o.second>2)
		{
			cout<<"cslnb";return 0;
		}
		if(o.second==2) p=min(p,o.first),s++;
	}
	if(s>1||!p||cnt[p-1])
	{
		cout<<"cslnb";return 0;
	}
	for(int i=1;i<=n;i++) ans+=a[i]-i+1;
	if(ans&1) cout<<"sjfnb";
	else cout<<"cslnb";
	return 0;
}
```

---

## 作者：兮水XiShui丶 (赞：0)

考虑必胜情况:在另外一个人开始取的时候有$2$个或者以上的重复组.或者在有1个重复组时,取出一个重复组(因为不取就会输)之后回和另外一个元素再组成一个重复组.  

我们再考虑完这种情况之后,可以发现,我们在将原来的数组排序之后,如果两边都按照最优方式取石子,那么最后的(在决定胜负之前),石子的序列一定是$B_i=i-1$的这样的一个等差数列.所以我们需要对原数组排序,然后统计一个$\sum_{i=1}^n A_i-(i-1)$,判断一下这个$sum$的奇偶性就可以了.  


PS:一定要先判断有没有例外的必胜情况(我就是这么WA了4发qwq....)  

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int n,idxx;
int num[N],dis[N];
map<int,bool>mp;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>num[i];
	sort(num+1,num+1+n);
	int sum=0,dpp=0;
	for(int i=1;i<=n;i++){
		if(num[i]==num[i-1]&&i>=2){
			dpp++;
			dis[++idxx]=num[i];
		}
		sum+=num[i]-i+1;
		mp[num[i]]=1;
	}
	if(n==1){
		if(sum&1)
			cout<<"sjfnb"<<endl;
		else
			cout<<"cslnb"<<endl;
		return 0;
	}
	if(dpp==1&&num[1]==0&&num[2]==0){
		cout<<"cslnb"<<endl;
		return 0;
	}
	if(dpp==1&&n==2){
		cout<<"sjfnb"<<endl;
		return 0;
	}
	if(dpp==1){
		if(mp[dis[1]-1])
				cout<<"cslnb"<<endl;
		else {
			if(!(sum&1))
				cout<<"cslnb"<<endl;
			else
				cout<<"sjfnb"<<endl;
		}
		return 0;
	}
	if(dpp>=2){
		cout<<"cslnb"<<endl;
		return 0;
	}
	if(!(sum&1))
		cout<<"cslnb"<<endl;
	else
		cout<<"sjfnb"<<endl;
	return 0;
}

```


---

## 作者：xukuan (赞：0)

好题

一个比较新奇的博弈论

我们来看什么情况下一方必输：

- 有大于等于两对的数相同；

- 只有一对数相同，但是存在一堆石子的石子数是相同的数-1

- 有一对0

- 石子数是0,1,2,...,n-1

显然对于前三种情况只会在开始时出现，特判掉即可。

最后的时候算 $\sum_{i=1}^{n} a[i]-n*(n-1)/2$的奇偶性，为奇则先手胜，为偶则后手胜

代码：

```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;

ll n,sum,ans,a[100010];

inline ll read(){
	ll x=0,tmp=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') tmp=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return tmp*x;
}

int main(){
	n=read();
	for(ll i=1; i<=n; i++) a[i]=read(),ans+=a[i];
	sort(a+1,a+1+n);
	for(ll i=1; i<n; i++){
		if(a[i]==a[i+1]) sum++;
	}
	if(sum>1) return printf("cslnb\n")&0;
	else if(sum==1){
		for(ll i=1; i<=n; i++){
			if(a[i]==a[i+1]){
				if(i!=1&&a[i-1]==a[i]-1) return printf("cslnb\n")&0;
				if(a[i+1]==0) return printf("cslnb\n")&0;
			}
		}
	}
	ans-=n*(n-1)/2;
	if(ans<=0) return printf("cslnb\n")&0;
	else if(ans&1) return printf("sjfnb\n")&0;
	else printf("cslnb\n")&0;
}
```

---

