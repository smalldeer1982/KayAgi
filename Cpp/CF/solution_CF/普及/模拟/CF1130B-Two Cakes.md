# Two Cakes

## 题目描述

Sasha and Dima want to buy two $ n $ -tier cakes. Each cake should consist of $ n $ different tiers: from the size of $ 1 $ to the size of $ n $ . Tiers should go in order from the smallest to the biggest (from top to bottom).

They live on the same street, there are $ 2 \cdot n $ houses in a row from left to right. Each house has a pastry shop where you can buy a cake tier. Unfortunately, in each pastry shop you can buy only one tier of only one specific size: in the $ i $ -th house you can buy a tier of the size $ a_i $ ( $ 1 \le a_i \le n $ ).

Since the guys carry already purchased tiers, and it is impossible to insert a new tier in the middle of the cake, they agreed to buy tiers from the smallest to the biggest. That is, each of them buys tiers in order: $ 1 $ , then $ 2 $ , then $ 3 $ and so on up to $ n $ .

Initially, Sasha and Dima are located near the first (leftmost) house. Output the minimum distance that they will have to walk in total to buy both cakes. The distance between any two neighboring houses is exactly $ 1 $ .

## 说明/提示

In the first example, the possible optimal sequence of actions is:

- Sasha buys a tier of size $ 1 $ near the $ 1 $ -st house ( $ a_1=1 $ );
- Dima goes to the house $ 2 $ ;
- Dima buys a tier of size $ 1 $ near the $ 2 $ -nd house ( $ a_2=1 $ );
- Sasha goes to the house $ 4 $ ;
- Sasha buys a tier of size $ 2 $ near the $ 4 $ -th house ( $ a_4=2 $ );
- Sasha goes to the house $ 5 $ ;
- Sasha buys a tier of size $ 3 $ near the $ 5 $ -th house ( $ a_5=3 $ );
- Dima goes to the house $ 3 $ ;
- Dima buys a tier of size $ 2 $ near the $ 3 $ -rd house ( $ a_3=2 $ );
- Dima goes to the house $ 6 $ ;
- Dima buys a tier of size $ 3 $ near the $ 6 $ -th house ( $ a_6=3 $ ).

So, Sasha goes the distance $ 3+1=4 $ , and Dima goes the distance $ 1+1+3=5 $ . In total, they cover a distance of $ 4+5=9 $ . You can make sure that with any other sequence of actions they will walk no less distance.

## 样例 #1

### 输入

```
3
1 1 2 2 3 3
```

### 输出

```
9
```

## 样例 #2

### 输入

```
2
2 1 1 2
```

### 输出

```
5
```

## 样例 #3

### 输入

```
4
4 1 3 2 2 3 1 4
```

### 输出

```
17
```

# 题解

## 作者：shiziyu111 (赞：2)

## 题目大意
找到两条路，每一条路的路径均为 $1,2,3,\dots,n$，求最短路径之和。
## 思路
由于售卖每一层的蛋糕只有两个，所以一共就只有两种情况：

1. 萨沙到店铺一，迪玛到店铺二。
1. 萨沙到店铺二，迪玛到店铺一。

所以，我们只需得出两种情况中相对较近的距离并累加到 $ans$ 中就能 AC 了。
## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e6 + 5;
const int inf=1e16;
int home1[MAXN],home2[MAXN];
signed main () {
	int n,ap=1,bp=1,ans=0;;	
	int a;
	cin>>n;
	for(int i=1;i<=n*2;i++)
	{
	
		cin>>a;
		if(home1[a]==0)
		{
			home1[a]=i;
		}
		else
		{
			home2[a]=i;
		}
	}
	
	for(int i=1;i<=n;i++)
	{
		if(abs(home1[i]-ap)+abs(home2[i]-bp)<=abs(home1[i]-bp)+abs(home2[i]-ap))
		{
			ans+=abs(home1[i]-ap)+abs(home2[i]-bp);
			ap=home1[i];
			bp=home2[i];
		}
		else
		{
			ans+=abs(home1[i]-bp)+abs(home2[i]-ap);
			ap=home2[i];
			bp=home1[i];
		}
	}
	cout<<ans;
	return 0;
}

```
## 更简便的方法
让我们在第一种情况更简便时输出 ```A```，反之输出 ```B```。

拿三个样例试一下。

#1：
```
A
A
A
9
```
#2：
```
A
A
5
```
#3：
```
A
A
A
A
9
```
这是怎么回事？

原来，由于我们先存放的是较为靠前的房子，所以萨沙永远只会走在数组 $home1$ 中的房子。

而且，由于他们永远只会分别走在 $home1$ 与 $home2$，所以我们可以直接用 $home1[i-1]$ 和 $home2[i-1]$ 代替 $ap$ 和 $bp$。

# New Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e6 + 5;
const int inf=1e16;
int home1[MAXN],home2[MAXN];
signed main () {
	int n,ans=0;;	
	int a;
	cin>>n;
	home1[0]=home2[0]=1;
	for(int i=1;i<=n*2;i++)
	{
	
		cin>>a;
		if(home1[a]==0)
		{
			home1[a]=i;
		}
		else
		{
			home2[a]=i;
		}
	}
	for(int i=1;i<=n;i++)
	{
		ans+=abs(home1[i]-home1[i-1])+abs(home2[i]-home2[i-1]);
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：AnicoderAndy (赞：2)

### 思路
一道贪心题！

因为两个人每次都必须走到下一个数字的位置，我们可以先把输入数据按照蛋糕的尺寸排序，将其坐标化。例如对于下面的输入（样例3），

$$\large
4,1,3,2,2,3,1,4
$$

可以这样进行排序：

$$\large
1,1,2,2,3,3,4,4
$$

即可方便地按照顺序进行操作，当然要记录坐标（也就是第几个被输入的），所以最终记下的数组应该是这样的：

$$\large
2,7,4,5,3,6,1,8
$$
$$\large
(1,1,2,2,3,3,4,4)
$$

那么就可以从左到右执行循环，每次循环，一个人在该数字的第一次出现的位置，一个人在第二次出现的位置，比如第一次循环，Dima在位置2，Sasha在位置7，然后比较两种走到下一个位置的方法，即

1. Dima From 2 to 4 (2 steps)\
Sasha From 7 to 5 (2 steps)\
**总共走了$2+2$步。**
1. Dima From 2 to 5 (3 steps)\
Sasha From 7 to 4 (3 steps)\
**总共走了$3+3$步。**

每次加上两种方案中较小的那一个。

### 具体实现
```cpp
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

//定义结构体
struct shop{
    int cur, data; //该商店的位置，售卖蛋糕的尺寸
}a[200010];

long long n, ans = 0;

//自定义比较函数，方便之后排序
bool cmp(shop a, shop b)
{
    //在尺寸不同时把尺寸小的蛋糕放前面
    if (a.data != b.data) return a.data < b.data;
    //反之把位置靠前的放前面（这个其实可以省略不写，也不影响判断）
    else return a.cur < b.cur;
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n * 2; i++) {
        cin >> a[i].data; //输入的是蛋糕的尺寸
        a[i].cur = i; //记录蛋糕的位置
    }

    sort(a + 1, a + 1 + n * 2, cmp); //排序

    //第一次两人的位置都在1，所以应该用尺寸为1的蛋糕位置分别-1相加
    //化简即为a[1].cur + a[2].cur - 2
    ans += a[1].cur + a[2].cur - 2;
    for (int i = 2; i <= n; i++) {
        //想要取得尺寸为i的蛋糕，必须从尺寸为i-1的蛋糕店出发

        //根据输入，尺寸为i的蛋糕位置分别是2i-1和2i
        int p = a[i * 2 - 1].cur, q = a[i * 2].cur;
        //尺寸为i-1的蛋糕位置分别是2i-3和2i-2
        int k = a[i * 2 - 3].cur, l = a[i * 2 - 2].cur;
        //比较两种方案，取最小值
        ans += min(abs(p - k) + abs(q - l), abs(p - l) + abs(q - k));
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：jiangjiangQwQ (赞：1)

### 思路
贪心题，两个人依次拾起 $1\to n$ 的蛋糕，做成两个高为 $n$ 的蛋糕层，求最小距离。假设某个人现在已经拾起了 $x$ 层，现在要出发到 $x+1$ 处，显然目标点有两种选择，分别为 $i$ 和 $j$，两人都要拾起 $x+1$ 的蛋糕，有两种方案。显然如果第一个人前往 $i$ 处，则第二个人只能前往 $j$ 处拾取，同理第二种方案是第一个人去 $j$ 处，第二个人前往 $i$ 处。比较两种方案的代价，得出最优方案，依次类推到拾起 $n$ 层的蛋糕。累加每次决策的答案即为最终所求的最小距离。由于每个人都要先拾起第一层，所以不管是两种方案中的哪一种，代价一致，所以可以直接从第二层蛋糕开始计算。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
#define int long long
#define For(i,j,k) for(register int i=j;i<=k;i++)
int n,a,ind[N][2];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin>>n;
    For(i,1,n*2){
    	cin>>a;
    	if(!ind[a][0]) ind[a][0]=i;
    	else ind[a][1]=i;
	}
	int sum=ind[1][0]+ind[1][1]-2;
	For(i,2,n){
		int x=abs(ind[i-1][0]-ind[i][0])+abs(ind[i-1][1]-ind[i][1]);
		int y=abs(ind[i-1][0]-ind[i][1])+abs(ind[i-1][1]-ind[i][0]);
		sum+=min(x,y);
	}
	cout<<sum;
    return 0;
}
```

---

## 作者：xyf007 (赞：1)

### 设a[i][0]表示第i层蛋糕第一次出现的位置，a[i][1]表示第i层蛋糕第二次出现的位置
### 那么每次都是两个人一起动，共两种情况：a[i][0]->a[i+1][0],a[i][1]->a[i+1][1]或a[i][0]->a[i+1][1],a[i][1]->a[i+1][0]
### 所以只要取最小值即可
---
```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
int n,a[100001][2];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=2*n;i++)
	{
		int x;
		scanf("%d",&x);
		if(a[x][0])
		{
			a[x][1]=i;
		}
		else
		{
			a[x][0]=i;
		}
	}
	long long sum=a[1][0]+a[1][1]-2;
	for(int i=2;i<=n;i++)
	{

		sum+=std::min(abs(a[i][0]-a[i-1][0])+abs(a[i][1]-a[i-1][1]),abs(a[i][0]-a[i-1][1])+abs(a[i][1]-a[i-1][0]));
	}
	printf("%lld",sum);
	return 0;
}
```

---

## 作者：pengzy (赞：0)

### 题意
有 $2\times{n}$ 家商店。从第 $1$ 到 $n$ 层的蛋糕，每层都可以在两家店买到（每家商店只出售一次）。相邻的两家商店距离为 $1$。

现在小 S 和小 D 都分别要买到第 $1$ 到 $n$ 层的蛋糕（必须按顺序买），问两人一共至少要走多少距离？（第一家商店就在旁边）

### 思路
输入。开一个大小为 $2\times{n}$ 的结构体。$p$ 记录能买到第 $i$ 层蛋糕的两个商店的位置，并根据层数进行排序。这样便于计算距离。

如样例 2：`2112`

排序后：`1122`

对应的 $p$：`2314`

贪心。按顺序买，所以两人首先要买一层的蛋糕。这时让谁去近的买谁去远的买是一样的。在买二层的蛋糕时，显然此时让离得近的去买是最优的。

### 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read()
{
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=x*10+c-48;c=getchar();}
	return x*f;
}
inline void write(int x)
{
	if(x>9)write(x/10);
	putchar(x%10+48);
}
const int Max=1e5+10;
int n;
ll ans;
struct cake{
	int t,p;
}a[Max*2];
bool cmp(cake x,cake y)
{
	if(x.t!=y.t)return x.t<y.t;
	else return x.p<y.p;
}
int main()
{
	n=read();
	for(int i=1;i<=n*2;i++) {
		a[i].t=read();
		a[i].p=i;
	}
	sort(a+1,a+1+n*2,cmp);
	ans=a[1].p+a[2].p-2;
	//先取一层蛋糕，排完序后，a[1]和a[2]都是一层的
	//因为第一家店就在边上，所以不需要走，花费为0 
	//但是我们记录的距离是1，所以减2 
	for(int i=3;i<=n*2;i+=2) {
		//从第二层蛋糕开始，每次循环2~n层蛋糕
		int m1=a[i].p,m2=a[i+1].p;
		int k1=a[i-1].p,k2=a[i-2].p; 
		//以i=3为例，m1，m2都是二层蛋糕的商店的位置 
		//k1，k2都是一层蛋糕的商店的位置 
		ans+=min(abs(m1-k2)+abs(m2-k1),abs(m1-k1)+abs(m2-k2));
		//判断两种情况哪种优 
	}
	cout<<ans;
	return 0;
}
```

## 证明
关于这个贪心的正确性，其实很显然。

设小 S 和小 D 分别在位置 a，b，下一层蛋糕的两个商店位置分别为 c，d，下下一层蛋糕的两个商店位置分别为 e，f。

此时若 $\lvert a-c \rvert + \lvert b-d \rvert < \lvert a-d \rvert + \lvert b-c \rvert$，且 $\lvert c-e \rvert + \lvert d-f \rvert < \lvert c-f \rvert + \lvert d-e \rvert$，我们记录的花费就是 $\lvert a-c \rvert + \lvert b-d \rvert + \lvert c-e \rvert + \lvert d-f \rvert$。如果第二步不是 $a$ 去 $c$，而是去 $d$，显然会更大。

另两种情况同理。

所以说，当前步步优，全局最优。

---

## 作者：enyyyyyyy (赞：0)

- 算法：
  贪心算法！用 $a_{i,0}$ 表示第一次出现的位置和 $a_{i,1}$ 第二次出现的位置。~~因我是红名巨佬~~，所以不会直接用数组模拟，只会用 `vector` 来做。
  
- 思路：
  用 `l` 表示上一家蛋糕店第一次出现的下标，用 `r` 表示上一家蛋糕店第二次出现的下标，用这一次家蛋糕店第一次出现的下标减家上一家蛋糕店第一次出现的下标加上这一次家蛋糕店第二次出现的下标减家上一家蛋糕店第二次出现的下标，便为答案。

- 代码：
 ```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef __int128 lint;
typedef double db;
typedef void vd;
typedef bool bl;
inline ll read() {
	ll s = 0,w = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9') {
		if(ch == '-')w = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9')s = s * 10 + ch - '0',ch = getchar();
	return s * w;
}
inline void print(long long x) {
	if(x < 0) {
		putchar('-');
		x = -x;
	}
	if(x>=10) print(x/10);
	putchar(x%10+'0');
	return;
}
vector<ll>a[2000005];
ll n,ans;
int main(){
	n=read();
	for(ll i=1;i<=2*n;i++){
		ll op;
		op=read();
		a[op].push_back(i);
	}
	ll l=1,r=1;
	for(ll i=1;i<=n;i++){
		ans+=abs(a[i][0]-l)+abs(a[i][1]-r);
		l=a[i][0];
		r=a[i][1];
	}
	print(ans);
	return 0;
}
```

  



---

## 作者：_Only_this (赞：0)

### CF1130B Two Cakes 题解

------------

和别人 solo 然后险胜的一个题，差点就祭了。。

------------

Sasha 和 Dima 最初都在最左端，因此考虑减少重复的路径来获取最优答案。

将 $2n$ 个数分成两组，对于每种数，下标较小的数为一组，下标较大的数为一组。

在这样的贪心下，很显然，可以使两个人重复路径最少，因为这样 Sasha 走的路径是尽可能靠前的，一定是最短路，并且剩下的位置也最大程度上避免了 Dima 的路径。

最后模拟路径即可。

贴个代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn = 4e5+5;
ll n;
ll a[maxn],nxt[maxn],dic[maxn],mp[maxn];
vector<ll>A[maxn];
bitset<maxn>vis;
int main(){
	scanf("%lld",&n);
	for(ll i=1;i<=(n<<1);i++){
		scanf("%lld",&a[i]),mp[a[i]]++;
		if(mp[a[i]]==1){
			vis[i]=1;
		}
		A[a[i]].push_back(i);
	}
	for(ll i=0;i<=(n<<1);i++){
		if(a[i]==n){
			continue;
		}
		if(abs(A[a[i]+1][0]-i)<abs(A[a[i]+1][1]-i)){
			nxt[i]=abs(A[a[i]+1][0]-i);
			dic[i]=(A[a[i]+1][0]>i);
		}
		else{
			nxt[i]=abs(A[a[i]+1][1]-i);
			dic[i]=(A[a[i]+1][1]>i);
		}
	}
	ll now=0,ans=-1,num=0;
	for(ll i=1;i<=n;i++){
		if(vis[A[num+1][0]]){
			ans+=abs(now-A[num+1][0]),now=A[num+1][0];
		}
		else{
			ans+=abs(now-A[num+1][1]),now=A[num+1][1];
		}
		num++;
	}
	now=0,ans--,num=0;
	for(ll i=1;i<=n;i++){
//		printf("now=%lld\n",now);
		if(!vis[A[num+1][0]]){
			ans+=abs(now-A[num+1][0]),now=A[num+1][0];
		}
		else{
			ans+=abs(now-A[num+1][1]),now=A[num+1][1];
		}
		num++;
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

