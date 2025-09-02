# Sonya and Robots

## 题目描述

Since Sonya is interested in robotics too, she decided to construct robots that will read and recognize numbers.

Sonya has drawn $ n $ numbers in a row, $ a_i $ is located in the $ i $ -th position. She also has put a robot at each end of the row (to the left of the first number and to the right of the last number). Sonya will give a number to each robot (they can be either same or different) and run them. When a robot is running, it is moving toward to another robot, reading numbers in the row. When a robot is reading a number that is equal to the number that was given to that robot, it will turn off and stay in the same position.

Sonya does not want robots to break, so she will give such numbers that robots will stop before they meet. That is, the girl wants them to stop at different positions so that the first robot is to the left of the second one.

For example, if the numbers $ [1, 5, 4, 1, 3] $ are written, and Sonya gives the number $ 1 $ to the first robot and the number $ 4 $ to the second one, the first robot will stop in the $ 1 $ -st position while the second one in the $ 3 $ -rd position. In that case, robots will not meet each other. As a result, robots will not be broken. But if Sonya gives the number $ 4 $ to the first robot and the number $ 5 $ to the second one, they will meet since the first robot will stop in the $ 3 $ -rd position while the second one is in the $ 2 $ -nd position.

Sonya understands that it does not make sense to give a number that is not written in the row because a robot will not find this number and will meet the other robot.

Sonya is now interested in finding the number of different pairs that she can give to robots so that they will not meet. In other words, she wants to know the number of pairs ( $ p $ , $ q $ ), where she will give $ p $ to the first robot and $ q $ to the second one. Pairs ( $ p_i $ , $ q_i $ ) and ( $ p_j $ , $ q_j $ ) are different if $ p_i\neq p_j $ or $ q_i\neq q_j $ .

Unfortunately, Sonya is busy fixing robots that broke after a failed launch. That is why she is asking you to find the number of pairs that she can give to robots so that they will not meet.

## 说明/提示

In the first example, Sonya can give pairs ( $ 1 $ , $ 1 $ ), ( $ 1 $ , $ 3 $ ), ( $ 1 $ , $ 4 $ ), ( $ 1 $ , $ 5 $ ), ( $ 4 $ , $ 1 $ ), ( $ 4 $ , $ 3 $ ), ( $ 5 $ , $ 1 $ ), ( $ 5 $ , $ 3 $ ), and ( $ 5 $ , $ 4 $ ).

In the second example, Sonya can give pairs ( $ 1 $ , $ 1 $ ), ( $ 1 $ , $ 2 $ ), ( $ 1 $ , $ 3 $ ), ( $ 2 $ , $ 1 $ ), ( $ 2 $ , $ 2 $ ), ( $ 2 $ , $ 3 $ ), and ( $ 3 $ , $ 2 $ ).

## 样例 #1

### 输入

```
5
1 5 4 1 3
```

### 输出

```
9
```

## 样例 #2

### 输入

```
7
1 2 1 1 1 3 2
```

### 输出

```
7
```

# 题解

## 作者：LJB00131 (赞：3)

* 此算法是O(n)

注意到$a[i]$值域 $1e5$ 显然可以直接对于每种数计算贡献。那么显然每种数作数对第一个数，位置最前的最优。

然后从后扫一遍该加的加即可。

```cpp
#include<bits/stdc++.h>

using namespace std;

#define N 100005

int n, a[N];

bool is[N], used[N];

int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) 
	{
		scanf("%d", &a[i]);
		if(!used[a[i]]) is[i] = 1;
		used[a[i]] = 1;
	}
	memset(used, 0, sizeof(used));
	long long cnt = 0, ans = 0;
	for(int i = n; i >= 1; i--)
	{
		if(is[i]) ans += cnt;
		cnt += (used[a[i]] == 0);
		used[a[i]] = 1;
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：Larry76 (赞：2)

## 题意描述：

给定 $n$ 个数，从前往后找，看看能和后面的数组成多少个不同的数对。

若两个数对仅仅是位置不同，我们也认为是两个不同的数对。

## 题目分析：

阅读题目，我们不难看出，若前面有一个数已经出现了，后面即使出现了重复的数，在以那个重复的数为开头时也不会被统计答案。

故我们易得以下思路：

维护两个 `map` 和一个 `set` 分别维护的是：每个数出现了多少次、是否出现过以某数为开头的情况和当前数的种类数。

然后我们从前往后扫，遇到一个数将其从第一个 `map` 中删去一次，若删除后第一个 `map` 关于这个数的信息为 $0$，则将其从 `set` 中删除。然后若该数在第二个 `map` 中被标记，则证明已经出现过以该数为开头的情况，否则将答案加上当前 `set` 的大小。

时间复杂度 $O(n \lg n)$。

## 代码实现：
```cpp
#include <bits/stdc++.h>
#define dbg(x) cerr<<#x<<": "<<x<<endl;
#define int long long
#define TIME_LIMIT 1
using namespace std;
#define MAX_SIZE (int)1.1e5
typedef pair<int,int> pii;

inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}

map<int,int>backet;
set<int>bbs;
map<int,bool>hashtable;

int a[MAX_SIZE];

signed main(){
    ios::sync_with_stdio(false);
#ifdef LOCAL
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
    double c1 = clock();
#endif
//============================================
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        bbs.insert(a[i]);
        backet[a[i]]++;
    }
    int ans = 0;
    for(int i=1;i<=n;i++){
        backet[a[i]]--;
        if(!backet[a[i]]){
            auto it = bbs.find(a[i]);
            bbs.erase(it);
        }
        if(!hashtable[a[i]])
            hashtable[a[i]] = true;
        else
            continue;
        ans += bbs.size();
    }
    cout<<ans<<endl;
//============================================
#ifdef LOCAL
    double c2 = clock();
    cerr<<"Used Time: "<<c2-c1<<" μs."<<endl;
    if(c2-c1>TIME_LIMIT*CLOCKS_PER_SEC)
        cerr<<"Warning!! Time Limit Exceeded!!"<<endl;
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}
```

$\text{Written on Ubuntu 22.10}$

---

## 作者：__Hacheylight__ (赞：2)

题意：

给你n个数，

从每一个数起向后找一个数，

是这两个数组成一个数对，

求一个有多少个数对。


解题思路：

把每个数值都记录下来，

并且记录共有多少中不同的数值，

然后从左向右走，

每到一个数是值这个数记录下，

以保证下次不会再记录它，

然后加上剩余剩的种类数。

注意：结果要用long long存。
---

```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 1000010 
typedef long long ll ;
ll a[N],c[N];
int main(){
	int n,x;
	scanf("%d",&n) ;
	set<int> s;
	for(int i=1;i<=n;i++){
		scanf("%d",&x) ;
		c[x]=s.size();
		s.insert(x);
	}
	ll sum=0;
	for(int i=0;i<N;i++)sum+=c[i];
	printf("%lld\n",sum) ;
}
```

---

## 作者：Elairin176 (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1004C)        
好题。      
当看到这道题的时候，我本来想暴力的。但是 $1\le n\le10^5$，显然不能暴力。          
在这个数据范围下，显然 $O(n\log n)$ 的算法是可以通过的。   
这里设 $f(l,r)$ 表示计算 $a_l$ 到 $a_r$ 有多少个不同的数。          
对于每一个 $i\in [1,n]$，它的贡献显然是 $f(i+1,n)$ 的，同时，相同的值只能计算一次贡献。        
时间复杂度还是 $O(n^2)$，不行。          
$f(l,r)$ 本质是对 $a_l$ 到 $a_r$ 进行去重操作，想到去重，我们就想到了一个 STL 容器。        
set。            
但是如果我们正着求解，是比较麻烦的。所以我们反过来。         
反过来会导致一些小错误的发生。       
比如样例，反过来会让靠后的 $1$ 贡献一次，而靠前的 $1$ 不能贡献。     
显然，我们应该让靠前的贡献。      
所以我们设 $cnt_i$ 为 $i$ 第一次出现的位置。       
我们让 $i$ 从 $n$ 跑到 $1$，如果 $i \neq cnt_{a_i}$，就跳过这次计算。每一次的贡献是 set 的大小。         
CODE：    
```cpp
//Code by __dest__ruct__or__(uid=592238)
#include <iostream>
#include <unordered_set>
#include <cstring>
using namespace std;
#define umap unordered_map
#define uset unordered_set
#define ll long long
#define ld long double
#define pii pair<int,int>
#define pll pair<long long,long long>
const ll INF=9223372036854775807;
namespace mySTL{
	inline int max(int a,int b){return a>b?a:b;}
	inline int min(int a,int b){return a<b?a:b;}
	inline ll max(ll a,ll b){return a>b?a:b;}
	inline ll min(ll a,ll b){return a<b?a:b;}
	inline ld min(ld a,ld b){return a<b?a:b;}
	inline ld max(ld a,ld b){return a>b?a:b;}
	inline int _abs(int a){return a<0?-a:a;}
	inline int read(){char c=getchar();int f=1,ans=0;
	while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9')ans*=10,ans+=c-'0',c=getchar();
	return ans*f;}
	inline long long readll(){char c=getchar();long long f=1,ans=0;
	while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9')ans*=10,ans+=c-'0',c=getchar();
	return ans*f;}
	inline void swap(int &a,int &b){a^=b,b^=a,a^=b;}
	inline void swap(ll &a,ll &b){a^=b,b^=a,a^=b;}
	inline void write(int x){if(x<0){putchar('-');x=-x;}
	if(x>=10){write(x/10);}putchar(x%10+'0');}
	inline void writell(long long x){if(x<0){putchar('-');x=-x;}
	if(x>=10){writell(x/10);}putchar(x%10+'0');}
	inline ll pw(ll a,ll b,ll p){if(b==0)return 1;
	if(b==1)return a%p;
	ll mid=pw(a,b/2,p)%p;
	if(b&1)return mid*mid%p*a%p;else{return mid*mid%p;}}
	inline int gcd(int a,int b){return b?gcd(b,a%b):a;}
	inline ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
	inline int lcm(int a,int b){return a*b/gcd(a,b);}
}
using namespace mySTL;
uset<int>s;
int n,a[100001],cnt[100001];
bool vis[100001];
ll ans;
int main(void){
	//freopen("data.txt","r",stdin);
	memset(cnt,0x3f,sizeof(cnt));
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		cnt[a[i]]=min(cnt[a[i]],i);//求出第一次出现的位置
	}
	for(int i=n;i>=1;i--){//计算结果
		if(i!=cnt[a[i]]){
			s.insert(a[i]);
			continue;
		}
		ans+=s.size();
		s.insert(a[i]);
	}
	writell(ans);
	return 0;
}
```


---

## 作者：JEB_Bem (赞：0)

## CF1004C Sonya and Robots

### Description
一个长度为 $ n $ 的序列，每个数向后搜做成若干个数对，要求每个数对不重复，问有多少个数对。

### Solution
首先考虑暴力：

正序枚举每一个数，然后向后枚举，如果我们用数组来检查每个数对，那么时间复杂度 $ O(n^2) $，空间复杂度 $ O(n^2)$。显然时空都会爆。

然后我们考虑一个贪心思想，对于两个相同的数，靠前的数显然可以将后面一个数组成的数对全部包含。因此，对于相同的几个数，只处理第一个数即可。

于是，我们可以从前往后遍历，对于每一个数，如果是这一种数的第一个，就统计它后面有多少个不同种类的数。

具体来讲：

**输入时**，用一个数组 $ m $ 统计一个数值的有多少个，并统计整个序列中一共有多少**种**数 $ kinds $。

然后从前往后遍历：

对于这**种**数 $ x $，如果是第一次访问并且不是这种数的最后一个，那么答案加上 $ kinds $(因为 $ (x,x) $ 也可以)，如果现在是最后一个了，那么无论是不是第一次访问都将 $ kinds $ 减  $ 1 $（减  $ 1 $ 的目的在于让后面的数不会统计到这种数），最后将 $ m_x $ 减 $ 1 $（其目的在于判断是不是最后一个数）。

### AC 代码

```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#define ll long long
#define PPP puts("Bing Bing");
using namespace std;
const int MAXN = 1e5 + 10;
int n,kinds;
int a[MAXN],map[MAXN];
ll ans;
bool vis[MAXN];

int main(){
    cin >> n;
    for (int i = 1;i <= n;i ++){
        cin >> a[i];
        if (!map[a[i]]) ++ kinds;
        ++map[a[i]];
    }

    for (int i = 1;i < n;++ i){
        if (!vis[a[i]]){
            if (map[a[i]] == 1) --ans;
            vis[a[i]] = 1,ans += kinds;
        }

        if (map[a[i]] > 1) -- map[a[i]];
        else -- kinds;
    }

    cout << ans << endl;

    return 0;
}
```
附[AC](https://www.luogu.com.cn/record/92346237)记录，目前次优解

---

## 作者：Tzs_yousa (赞：0)

## 做法
很简单，就是找出所有数对然后再去重之后剩下的个数，暴力算法就是枚举。

但是我们观察到数据范围有 100000 之大，那显然 $n^2$ 的算法不可做了。

那我们就要考虑优化暴力算法，思考线性算法。

我们去重的方法是加一些 $vis$ 数组来判断是否这个数用过，只要记录下每个数第一次出现的位置，之后只加上这些位置的贡献即可，因为假如一个数出现第二次，那这个数所能组成的数对一定是小于等于第一个的，那么就可以舍去这种情况，并起到去重的作用。

## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
const int MAXN = 1e5 + 10;
using namespace std;
int n, a[MAXN], vis1[MAXN], vis2[MAXN], pos[MAXN], ans;

signed main() {
	scanf("%lld", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &a[i]);
		if (!vis1[a[i]])
			pos[i] = 1;
		vis1[a[i]] = 1;
	}
	int num = 0;
	for (int i = n; i >= 1; i--) {
		if (pos[i] == 1)
			ans += num;
		if (vis2[a[i]] == 0)
			num++;
		vis2[a[i]] = 1;
	}
	printf("%lld\n", ans);
	return 0;
}
```


---

## 作者：Cuiyi_SAI (赞：0)

## 解题思路

这道题的关键就是去重。

考虑对于每一个 $a_i$，若 $i<j$ 且 $a_i=a_j$ ，则我们只计 $a_i$ 的贡献。因为无论 $j$ 为何，它能产生的数对都与 $a_i$ 一样。

在考虑计算 $a_i$ 贡献时，同样需要对后面的数进行去重。我们将 $[i,n]$ 中**不同**的数的**种数** 记为 $len_i$，则 $a_i$ 的贡献就是 $len_i-1$。$ len$ 可以通过预处理 $O(n)$ 得到。

综上所述，我们结合两种去重方案，就可以的到所求的答案，复杂度为 $O(n)$。

## CODE:

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a[100010],len[100010];
long long ans=0;
bool vis[100010],v[100010];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	len[n]=1;
	for(int i=n-1;i>=1;i--) len[i]=len[i+1]+(!vis[a[i+1]]),vis[a[i+1]]=1;
	for(int i=1;i<=n;i++)
	{
		if(v[a[i]]) continue;
		v[a[i]]=1;
		ans+=len[i]-1;
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：lightningZ (赞：0)

## 思路
首先，在读完题之后，可以发现这道题最关键的地方在于**判重**。一开始本来想用排列组合的思路去解，后来因为~~我不会~~所以放弃了。后来想到，如果判重的话其实就是，从前往后找第一个数，如果这个第一个数被找过了，那就直接跳过就行了。

然后就是关于优化找第二个数的复杂度，可以用一个桶，记一下找到的第一个数后面又多少个不同的数字，那么这个第一个数就能组成多少个数对，这里注意，因为是看每一个数的后面，所以直接从后往前去扫一遍 $O(n)$ 即可。因为第一个判重，所以就不需要考虑两个数相同的情况。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[100005],t[100005],b[100005],ans;
signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	for(int i=n;i>=1;i--)//桶
	{
		t[a[i]]++;
		if(t[a[i]]==1) b[i-1]++;
		b[i]+=b[i+1];
	}
	memset(t,0,sizeof(t));//懒得再开一个数组了，之前清空接着用
	for(int i=1;i<=n;i++)
	{
		if(!t[a[i]]) ans+=b[i];//记录答案
		t[a[i]]=1;
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：Aw顿顿 (赞：0)

一开始以为题意出错了，但是实际上并没有，这需要我们考虑一个去重的问题。

首先用 $f$ 表示出现过的数，对于其第一次出现的位置进行记录。然后从后往前扫，如果在扫描过程中他是第一次出现，记为一次贡献，而如果当前位置是某个数第一次出现的位置，那么先前累计的所有贡献都可以计入答案。

感性理解一下这个算法的正确性。对于每一个数第一次出现的位置，在它之后的所有位置都可以与其配对，而当我们计算贡献只计算不重复的时候，直接累加就可以得到每一个位置对应的组数。

题目的 $n$ 是在 $10^5$ 范围内的，可以接受，代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 100005
using namespace std;
int n,a[N],used[N],fir[N],res;
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		if(!used[a[i]])fir[i]=i;//如果是第一次出现 
		used[a[i]]=1;
	}int cnt=0;
	memset(used,0,sizeof used);
	for(int i=n;i>0;i--){
		if(fir[i])res+=cnt;
		if(!used[a[i]])cnt++;
		used[a[i]]=1;
	}printf("%lld\n",res);
	return 0;
}
```


---

## 作者：_Clown_ (赞：0)

# C.Sonya and Robots
$\mathtt{Difficulty}$=$\mathtt{1400}$

这道题目唯一的问题就是如何去重。

首先，对于数列中两个相同的数，

前面元素所成的数对，

后面元素一定都能造出。

那么我们就有了一个思路，

相同的数只需要算最后一个，

而前面的显然全部重复。

可以使用 set 维护，

然后代码就不难写出了。
```cpp
#include<bits/stdc++.h>
#define BetterIO ios::sync_with_stdio(false)
using namespace std;
#define int long long
#define MAX 100001
int N,Ret,A[MAX],Cnt[MAX];
set< int >Set;
signed main(void)
{
	BetterIO;
	register int i;cin>>N;
	for(i=1;i<=N;i++)cin>>A[i];
	for(i=1;i<=N;i++)Ret-=Cnt[A[i]],Ret+=(Cnt[A[i]]=Set.size()),Set.insert(A[i]);
	cout<<Ret<<endl;
	return 0;
}
```

---

## 作者：YuanZhizheng (赞：0)

题意：给你一序列，每个数能和它后面的数两两组成数对，求数对个数，重复的数对只记1次。

比如序列1 2 1 3。对于数字3来说没有数对，对于3旁边的1来说，有（1，3）这个数对，对于2来说，有（2，1）（2，3）两个数对，对于最左边的1来说，有（1，2）（1，1）两个数对。所以一共5个数对。

其中，（2，1）和（1，2）是不同的数对，所以记为2。而（1，3）会重复出现，只记一次。

看到这种题，第一眼会想到暴力，但是数据范围是1e5，所以O(n^2)的复杂度是会超时的。

不过这题的话，是有O（n）的做法的，在此我使用了类似**链式前向星**的方法。

其实我们是可以发现的，由于数**对不能重复，所以每个位置能和后面的数字形成多少种数对，实际上是和它后面有多少种数字是有直接关系的**。

我拿一个长一点的序列举例，比如1 2 3 4 5 1 6 7这个序列。

对于6来说，其后边有一种数字，所以是1个数对，对于最右边的1来说，其后边有两种数字，所以是2个数对，对于5就同理了，有3个数对。

然后你会发现，有两个1，数对不能重复，所以最左边的1所能形成的数对，其实就是看在两个1之间有多少不同的数字。显然有4种，（不记录（1，1），（1，1）（2，2）这种会另外处理）。

至此，大家应该可以想到了，采用我们需要统计每个数字之后，一共有多少种数字，这就需要**前缀和**。

同时，如果出现了像上面序列中出现了两个1（重复出现数字）的情况，那么我们就另**外需要数组来判断当前位置的数字，在其后面是否存在相同的数字，如果不存在，组成的数对数量就是其后面不同种类的数字数量；如果存在，组成的数对数量就是两个相同数字之间不同种类数字的数量**。这就需要**链式前向星**。

所谓链式前向星，就是用一个nex数组让我们知道当前位置的数字，在其后面第一次出现的位置是哪里，如果没出现那么就是0。同时需要一个head数组来不断保存数字最新出现的位置。

同时，我们还需要vis数组，来记录某个数字出现的次数，如果某个数字x出现了两次或者更多，那么一定可以组成（x，x）数对，这就是我前面说的另外处理。

下面就是AC代码，附有详细注释。
```
#include<bits/stdc++.h>
using namespace std;
int a[100005];//接收数字
int head[100005],nex[100005];//链式前向星
int num[100005];//前缀和，记录当前这个位置之后有多少不同种的数字
int vis[100005];//记录每个数字出现数量
inline int read()//快读
{
    int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9')
    {
        if(c=='-')
            f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9')
    {
        x=x*10+c-'0';
        c=getchar();
    }
    return x*f;
}
int main()
{
    int n;
    int i;
    n=read();
    for(i=1;i<=n;i++)
        a[i]=read();
    for(i=n;i>=1;i--)//由于我们需要的是每个数字后面的情况，所以我们倒着跑数组
    {
        if(vis[a[i]]==0)//前缀和
            num[i]++;
        num[i]+=num[i+1];
        vis[a[i]]++;
        
        //链式前向星
        nex[i]=head[a[i]];
        head[a[i]]=i;
    }
    long long ans=0;//记录答案
    
    for(i=0;i<=100000;i++)//如果某数字x出现两次，那么一定能组成（x，x）数对
        if(vis[i]>1)ans++;
        
    for(i=n;i>=1;i--)//开始遍历
    {
        if(nex[i]==0)//如果为0，说明这个数字的后面没有出现过相同数字，直接利用前缀和。
                     //为什么要-1？因为前缀和保存的是当前位置及其后面不同种类数字的数量，如果当前位置之后是没有这个数字的，那么后面数字的种类肯定比num[i]少一。
            ans+=num[i]-1;
        else
            ans=ans+num[i]-num[nex[i]];//两相同数字之间的不同数字种类数量
    }
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：玉环小姐姐 (赞：0)

解题思路：

想法一：硬生生的枚举开头和结尾，并进行一定的优化，但是呢，除非你牛得不得了，否则算法复杂度都会保持在O（N * N）。绝对会炸，我们班上已经有一个炸了。

想法二：他既然要求的只是总数，为什么要枚举每个状态呢，只要算总数就行了。就是一个O（n）的算法。

本程序操作如下：

1.定义三个数组a,b,c，数组a存储的是读入的数组，数组b存储的是到目前为止，余下数组内，每个数字出现的此数（为何是余下的数组，后文会有解释）。

2.读入不做解释，但读入时我干了两件事。第一件：在数组b内操作，不断更改现在每个数出现的次数。第二件：若此数第一次出现，则在变量s中累加，可以用```b[a[i]]==1```来判断（之所以是等于一，是因为我是先加再判断）

3.操作分三步。第一步：在b数组中将目前所指向的数字的出现次数减一；第二步：若```b[a[i]]==0```，那么说明余下的数组中已经没有此数了，```s--```（此时的s表示后面数字的总类别数）；第三步：如果```c[a[i]]==0```表示```a[i]```是第一次出现，那么在答案变量ans里加上目前的s；并把```c[a[i]]```设为一；

4.输出，这个不做解释。

5.#注意：答案一定要开long long 不然会爆，~~我已经爆过了~~。

---

