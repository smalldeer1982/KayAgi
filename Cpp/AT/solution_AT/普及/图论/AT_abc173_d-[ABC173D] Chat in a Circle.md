# [ABC173D] Chat in a Circle

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc173/tasks/abc173_d

あなたはオンラインゲーム「ATChat」のチュートリアルを終え、その場に居合わせたプレイヤー $ N $ 人で早速とある場所を訪ねることにしました。この $ N $ 人には $ 1 $ から $ N $ の番号が振られており、人 $ i\ (1\ \leq\ i\ \leq\ N) $ の **フレンドリーさ** は $ A_i $ です。

訪ねる際、$ N $ 人は好きな順番で $ 1 $ 人ずつ到着します。あなたたちは迷子にならないために、既に到着した人たちで環状に並び、新たに到着した人は好きな位置に割り込んで加わるというルールを決めました。

最初に到着した人以外の各人は、割り込んだ位置から到着した時点で「時計回りで最も近い人」と「反時計回りで最も近い人」のフレンドリーさのうち小さい方に等しい **心地よさ** を感じます。最初に到着した人の心地よさは $ 0 $ です。

$ N $ 人が到着する順番や割り込む位置を適切に決めたとき、$ N $ 人の心地よさの合計の最大値はいくらになるでしょう？

## 说明/提示

### 制約

- 入力はすべて整数
- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ 10^9 $

### Sample Explanation 1

人 $ 4,\ 2,\ 1,\ 3 $ がこの順に到着し、図のように輪に割り込むことで、心地よさの合計は $ 7 $ になります。 !\[図\](https://img.atcoder.jp/ghi/766a260a0019ea93e86e0588cc4db868.png) 心地よさの合計を $ 7 $ より大きくすることはできないので、$ 7 $ が答えになります。

## 样例 #1

### 输入

```
4
2 2 1 3```

### 输出

```
7```

## 样例 #2

### 输入

```
7
1 1 1 1 1 1 1```

### 输出

```
6```

# 题解

## 作者：huhexuan (赞：2)

很明显的贪心吧。

首先，第一个人没有贡献，却会在第二个人时贡献自己的友谊度，很明显，如果第一个人不是友谊度最大的人，那么友谊度最大的人永远不会贡献自己的友谊度，所以第一个人一定是友谊度最大的人，以此类推，第二个人就是友谊度第二大的人，第三个人就是友谊度第三大的人……

其次，第一个人只会在第二个人时贡献友谊度，但第二个人左右有两个位置（是一个环），会贡献两次友谊度，之后的每一个人都是如此。

之后排一次序，优先队列维护即可。

模拟样例是很好看出来的。

代码如下：

```cppp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[200005];
bool cmp(int a,int b)
{
	return a>b;
}
priority_queue<int>q;
signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    if(n==1)
    {
    	cout<<0;
    	return 0;
	}
    sort(a+1,a+n+1,cmp);
    int ans=0;
    q.push(a[1]);
    for(int i=2;i<=n;i++)
    {
    	ans+=q.top(); 
    	q.pop();
    	q.push(a[i]);
		q.push(a[i]);
	}
	cout<<ans;
	return 0;
}
```

实测可AC。

---

## 作者：__Cby___ (赞：2)

## 解题思路
一道贪心题。我们采用经典的贪心算法，每次优先放入友好值大的。因为每个人的舒适度跟已加入的人的友好值有关，先加入友好值大的就不会让总体的舒适度被友好值小的人影响。   
第二个点就是每个人的友好值可以贡献两次，但友好值最大的人找不到比他更大的人来使他产生贡献，所以友好值最大的人贡献只算一次。  
我们采用优先队列来维护最大值。
## 代码
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
int a[200025];
int main() {
	int n;
	cin >> n;
	priority_queue<int,vector<int>,less<int>> pq;
	for (int i = 1; i <= n; i++)cin >> a[i];
	sort(a + 1, a + 1 + n, greater<int>());
	pq.push(a[1]);
	long long int sum = 0;
	for (int i = 2; i <= n; i++) {
		sum += pq.top();
		pq.pop();
		pq.push(a[i]);
		pq.push(a[i]);
	}
	cout << sum << endl;
	return 0;
}
```

---

## 作者：_Delete_ (赞：1)

### 思路

题意很好理解，直接考虑贪心。

由于要让舒适度最大，我们就要让每个人相邻两数都尽可能大，于是将大数优先插入队列。

将每个人的友好度进行排序，从大到小插入队列。不难看出，最大的数仅用一次就不会再次使用，因为它从插入第二个人后便没有可能再次成为两数中的较小数；最小的数不会进行使用，因为它是最后一个进入队列的人；其余各数分别可以使用两次，分别是顺时针被使用和逆时针被使用（由于贪心策略，每个数插入时，左右两数一定都比该数大，所以该数不管和顺时针数还是逆时针数都为较小数，所以可以使用一次）。

对于每个可获得的数，从大到小暴力求和。

### 代码

```cpp
#include<bits/stdc++.h>
#define endl "\n"
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
//value 
const ll MA=2e5+5;
ll a[MA];

//function 

 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0); 
	
	ll n;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>a[i];
	}
	sort(a,a+n);
	int p=n-2;//剩余求和人数
	//由于题目中首个插入的人不会获得舒适度，所以只需计算n-1人即可
	ll ans=a[n-1];//不开long long见祖宗
	for(int i=n-2;;--i){
		if(p<=0)break;
		if(p>=2){
			p-=2;
			ans+=a[i]*2;
		}
		else if(p==1){
			p--;
			ans+=a[i];
		}
	}
	cout<<ans<<endl;
	
	return 0;
}


```


---

## 作者：Lyw_and_Segment_Tree (赞：1)

## 题意简述
> 有 $n$ 个玩家在玩一个游戏，他们每人有一个友好度 $a_i$，现在这 $n$ 名玩家要围成一个圈，玩家们以特定的顺序依次进入这个圈，在那时每个玩家有一个舒适度 $s_i$，规定第一名进入的玩家的舒适度为 0，其他玩家的舒适度是其左边玩家的友好度和右边玩家的友好度中的较小者，问这些玩家所能获得的最大总舒适度是多少。  

## 开始解题！
首先这题的玩家插入顺序不明显，而题目又让我们求最大总舒适度，并且舒适度由玩家的友好度转移而来，考虑贪心。  
首先我们根据题意，简单模拟可知第 $i ( i \ge 2 )$ 个玩家的舒适度是 $a_{i-1}$，此时，我们就可以使用大根堆来进行维护。对于每个玩家，我们复制两份来进行运算即可。  
代码如下：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,a[200010],ans=0;
int main(){
    priority_queue<ll> q;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    sort(a+1,a+n+1);
    q.push(a[n]);
    for(int i=n-1;i>=1;i--){
        ans+=q.top();
        q.pop();
        q.push(a[i]);
        q.push(a[i]);
    }
    cout<<ans<<endl;
}
```

---

## 作者：Gaoyx (赞：1)

## 思路
- 一道贪心题，第一眼看到时想到了合并果子。

- 根据题意，优先放友好值高的，这样可以不让友好值低的影响了总体的舒适度。

- 每个友好值可以使用两次，但最高的只能使用一次，最少的不使用。

- 最后使用优先队列，每个数存入两次（除第一个数），在累计求和堆顶（最大值）。

## 代码
```
#include<bits/stdc++.h>
using namespace std;
priority_queue<long long>k; 
long long a[1000001], sum, n;
int main()
{
	cin >> n;
	for(int i=1;i<=n;i++)cin >> a[i];
	sort(a+1,a+n+1);
	k.push(a[n]);
	for(int i=n-1;i>=1;i--)
	{
		sum += k.top();
		k.pop();
		k.push(a[i]);
		k.push(a[i]);
	}
	cout << sum;
	return 0;
}
```


---

## 作者：DengDuck (赞：1)

考虑贪心，直觉告诉我们从大到小加入是最优的。

为什么呢？因为间隔的价值与放进去的元素的最小值有关，这样放可以尽量让当前的每个间隔的价值都最大，这样是最好的。

然后对于当前还是一个贪心，我们用一个大根堆维护当前插入每个位置的贡献值，这个很好维护。

具体来说，插入一个数，你肯定可以让左右两边的间隔价值变成你的值，插入即可。

然后你插在哪里呢？注意间隔的价值不会因插入元素的价值而改变，啥时候插入价值都一样，所以我们贪心的找最大值即可。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=2e5+5;
priority_queue<LL,vector<LL>,less<LL> >p; 
LL n,a[N],ans;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i]; 
	}
	sort(a+1,a+n+1);
	p.push(a[n]);
	for(int i=n-1;i>=1;i--)
	{
		ans+=p.top();
		p.pop();
		p.push(a[i]);
		p.push(a[i]);
	}
	printf("%lld",ans);
}
```

---

## 作者：Xiphi (赞：1)

贪心策略，每次选最大的值插入。如果最大值在最后插入，就会被比它小的值影响。

首先，我们要排序原序列。然后计算结果时，最大值单独加。其余的都贡献了两次值。

核心代码：

```cpp
	long long n,ans=0;
	cin>>n;
	for(int i=1;i<=n;++i) cin>>a[i];
	sort(a+1,a+n+1,greater<int>());
	ans=a[1];
	for(int i=3;i<=n;++i) ans+=a[i/2];
	cout<<ans<<"\n";
```


---

## 作者：pm_fp (赞：0)

### 思路

一眼题目考虑贪心，先从小到大排序一遍，然后定义一个优先队列，让最大值先进，这样可以不被后面的较小值影响，使其始终是最优的。

因为在往后的判断中最大值始终是最大的，所以只能用一次。

然后把其他的依次压入队列，每个数都存两次，因为每个人左右都能插入别人，所以每个数（除最大值）能用两次，最后是最小值用不着，这道题就迎刃而解了

### 码

```
#include<bits/stdc++.h>
using namespace std;
priority_queue<long long>q; 
int n;
long long a[1919810];
long long sum;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+n+1);
	q.push(a[n]);
	for(int i=n-1;i>=1;i--){
		sum+=q.top();
		q.pop();
		q.push(a[i]);
		q.push(a[i]);
	}
	cout<<sum;
	return 0;
}
```


---

## 作者：guowenxuan101 (赞：0)

## 思路
读完题目，考虑贪心，首先插入友好值最大的人，从大到小插入，友好值最小的人不用，因为两边的值都可以选，所以除了首先插入的，其他的友好值都可以用两次，所以除了第一个值每个值都塞两次。
## 代码
不难想到用大根堆。
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#define int long long
using namespace std;
const int X=1145140;
int n;
int a[X];
bool cmp(int x,int y){//sort从大到小排序
	return x>y;
}
int ans=0;
priority_queue<int>q;
signed main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	sort(a+1,a+n+1,cmp);
	q.push(a[1]);
	for(int i=2;i<=n;i++)//注意从第二个枚举
	{
		ans+=q.top();
		q.pop();
		q.push(a[i]);//记得要放入两次权值
		q.push(a[i]);
	}
	cout << ans;
	return 0;
}
```
### 相关知识
[大根堆](https://www.luogu.com.cn/blog/966803/solution-at-tkppc4-1-k)

来自神犇：A_grasser



---

## 作者：Symbolize (赞：0)

# $\tt{Solution}$
思路还是很简单，如果你将友好度大的人优先加入，可以给后面的人带来更好的选择空间，所以一定是从大到小加入，而每次加入后又该如何考虑呢？实际上，顺时针与逆时针的最小值这句话干扰了我们的思考，我们要的只有小的，那也就是说我们要在已有的当中挑一个最大的数，而这个数旁边还有比它小的，不难想到中间大小的那个数，不难证明，由于每次都会把一个大的数插入中间大的数旁边（不妨从开始就一直插到右边），每次整体长度会增加 $1$，所以中间大小的那个数旁边一定有比它大的（因为上次插入的数一定在它旁边）。那么每次答案加上当前中间大小的那个数就行了。注意单独处理下前面的两个人。

```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define x first
#define y second
#define rep1(i,l,r) for(register int i=l;i<=r;++i)
#define rep2(i,l,r) for(register int i=l;i>=r;--i)
#define rep3(i,h,x,ne) for(register int i=h[x];~i;i=ne[i])
#define debug() puts("----------")
const int N=2e5+10;
using namespace std;
int n,a[N],ans;
int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	n=read();
	rep1(i,1,n) a[i]=read();
	sort(a+1,a+n+1);
	reverse(a+1,a+n+1);
	ans=a[1];
	rep1(i,3,n) ans+=a[i+1>>1];
	cout<<ans<<endl;
	return 0;
}

```

---

## 作者：_Flora_ (赞：0)

## 题目意思

有一排数字，要将这排数字按顺序放入一个圈，每个数字在插入圈时，它的权值就是相邻两个数字中较小的那个，第一个插入的数字权值为0。

求总权值。

## 解析

要使权值最大，就要让大的值先插入，否则就会被相邻的较小值影响，从而使其不能贡献权值。

因为是一个圈，圈的两边都能贡献权值，所以除了最大的数只能贡献一次权值，其余的数都可以贡献两次。

## 代码

```c
#include <bits/stdc++.h> 
using namespace std;

int a[200001];

int compare(int a,int b)
{
	return a>b;
}
int main()
{
	int i,n;
	
	long long ans=0;
	
	cin>>n; 
	
	for(i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	
	sort(a+1,a+1+n,compare);
	
	ans=ans+a[1];
	
	for(i=3;i<=n;i++)
	{
		ans=ans+a[(i+1)/2];
	}
	
	cout<<ans<<endl; 
	return 0;
}
```


---

## 作者：YangXiaopei (赞：0)

## Solution:
明显的一个贪心，想让最终舒适值最大，就尽可能的让每一步最大，所以让友好度大的人先去。

除去友好度最大的人，每个人在理论上最多可贡献 $2$ 次舒适值，而友好度最大的人，除了一个左右均为他的人，都不可能比别人小，也就有且仅有一次贡献舒适度的机会。并且一共会贡献 $n - 1$ 次舒适值。

好了，有了这个思路，让我们一起来捋捋做着题的步骤。

* 按舒适度大小排序。
* $sum$ 加上舒适度最高的人。
* $sum$ 加上 $2$ 次 舒适度第 $2$ 到 $(n - 1 - 1) \div 2$ 的人。
* 如果才加上 $n - 2$ 次， $sum$ 加上舒适度第 $n - 2 - ((n - 2) \div 2) \times 2$ 的人。

## Code:
```cpp
#include<bits/stdc++.h>
#define int unsigned long long
using namespace std;
int n, a[200005];
bool cmp(int x, int y){
	return x > y;//按友好度大小排序
}
signed main(){
	cin >> n;
	for(int i = 1; i <= n; i++){
		cin >> a[i];
	}
	int sum = 0;
	int x = (n - 2) / 2;//加两次的人
	sort(a + 1, a + n + 1, cmp);
	sum += a[1];//最大只能加一次
	for(int i = 2; i <= 1 + x; i++){
		sum += 2 * a[i];
	}
	int ans = n - 2 - x * 2;
	sum += ans * a[2 + x];//如果才加上 n - 2 次， sum 加上舒适度第 n - 2 - ((n - 2) / 2) * 2 的人。
	cout << sum;
	return 0;
}
```
## 华丽结束

---

## 作者：封禁用户 (赞：0)

# 思路      
   看到这种求最大值的，就想到贪心。\
 	那么这道题怎么“贪”呢？为了不让友好较小值影响整体舒适度（每个人的舒适度为旁边的两人**较小**值），所以我们应该先放舒适度较大的人。\
   所以说我们就可以让第三大与第四大和第二大挨在一起，第五大与第六大和第三大挨在一起······\
   循环下去，我们会发现，两两一组，与他们的编号除以二的人挨在一起，这样循环下去，就能使舒适度最大。  
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[2000005],ans;
bool cmp(long long a,long long b){return a>b;}
int main(){
	cin >> n;
	for(int i = 1; i <= n; i++)
		cin >> a[i];
	sort(a+1, a+n+1,cmp);//从大到小排序 
	ans += a[1];//第一个人只能贡献一次 
	for(int i = 3; i<=n; i++)//从第三个人开始 
		ans += a[(i+1)/2];//核心代码：通过整除两两一组 
	cout << ans;
	return 0;
}
```

---

## 作者：Neilchenyinuo (赞：0)

- 很明显的一道贪心。

## 题目大意

有一排数字，要将这排数字按顺序放入一个圈，每个数字在插入圈时，它的权值就是相邻两个数字中小的那个，第一个插入的权值为 0，问总权值是多少。

## Solution

1. 贪心策略，每次选最大的值插入。如果最大值在最后插入，就会被比它小的值影响。

2. 我们可以维护一个优先队列（大根堆）维护最大值，定义一个 $ans$ 累加总和即可。 

3. 为什么这样做？因为间隔的价值不会因插入元素的价值而改变，啥时候插入价值都一样，所以是可以贪心找最大值的。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
priority_queue<int>pq; 
int n,a[N],ans;
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	sort(a+1,a+1+n);
	pq.push(a[n]);
	for(int i=n-1;i>=1;i--)
	{
		ans+=pq.top();
		pq.pop();
		pq.push(a[i]);
		pq.push(a[i]);
	}
	cout<<ans<<"\n";
	return 0;
}
```

---

