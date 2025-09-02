# [ABC140F] Many Slimes

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc140/tasks/abc140_f

$ 1 $ 匹のスライムがいます。

あなたはこのスライムの「体力」を自由な整数の値に設定できます。

スライムは $ 1 $ 秒ごとに、自分より真に小さい整数の体力をもつスライムを $ 1 $ 匹生成することで増殖していきます。生成されるスライムの体力は、スライムごとに毎回自由に決めることができます。最初の増殖はこれから $ 1 $ 秒後に起こります。

最初のスライム、および生成されるスライムの体力を適切に定めることで、これから $ N $ 秒後に存在する $ 2^N $ 匹のスライムの体力の集合を集合 $ S $ に一致させることができるか判定してください。

ここで $ S $ は $ 2^N $ 要素からなる重複を認める整数の集合で、その要素は $ S_1,~S_2,~...,~S_{2^N} $ です。

## 说明/提示

### 制約

- 入力は全て整数である。
- $ 1\ \leq\ N\ \leq\ 18 $
- $ 1\ \leq\ S_i\ \leq\ 10^9 $

### Sample Explanation 1

$ 2 $ 秒後に存在するスライムの体力の集合を $ S $ に一致させる一例を示します。 まず最初のスライムの体力を $ 4 $ に設定します。 最初のスライムに体力が $ 3 $ のスライムを生成させることで、$ 1 $ 秒後に存在するスライムの体力を $ 4,~3 $ とできます。 そして最初のスライムに体力が $ 2 $ の、$ 2 $ 匹目のスライムに体力が $ 1 $ のスライムを生成させることで、$ 2 $ 秒後に存在するスライムの体力を $ 4,~3,~2,~1 $ とできます。これは集合として $ S $ に一致しています。

### Sample Explanation 2

$ S $ は同じ整数を複数含むこともあります。

## 样例 #1

### 输入

```
2
4 2 3 1```

### 输出

```
Yes```

## 样例 #2

### 输入

```
2
1 2 3 1```

### 输出

```
Yes```

## 样例 #3

### 输入

```
1
1 1```

### 输出

```
No```

## 样例 #4

### 输入

```
5
4 3 5 3 1 2 7 8 7 4 6 3 7 2 3 6 2 7 3 2 6 7 3 4 6 7 3 4 2 5 2 3```

### 输出

```
No```

# 题解

## 作者：krazy (赞：5)

这个题可以直接根据题意模拟就行......

贪心一下，可以发现一定是先生成大的再生成小的，并且大的数一定去生成刚好小于它的那个数。我们就可以根据这个贪心来模拟。

然后模拟过程就需要一些乱搞了......比如我用了两个 multiset 和一个 set，一个 multiset 用来记录用来存还剩哪些数没生成，另一个用来存已经生成了哪些数，然后后面放数的时候就枚举第二个 multiset 来生成新的数。两个 multiset 都是默认从大到小排序的。

然后我那个 set 就是用来存还有哪几种数没放，因为根据贪心，我们需要找到第一个刚好小于它的数来生成，就可以在 set 上面二分一下即可。然后如果这个数在第一个 multiset 已经没了，那么我们就在这个 set 中把这个数删掉即可。

时间复杂度大概为 $\mathcal{O}(n\log^2n)$.

渣代码轻喷QAQ
```cpp
#include <bits/stdc++.h>
#define ll long long
#define ls id << 1
#define rs id << 1 | 1
#define mem(array, value, size, type) memset(array, value, ((size) + 5) * sizeof(type))
#define memarray(array, value) memset(array, value, sizeof(array))
#define pb(x) push_back(x)
#define st(x) (1LL << (x))
#define pii pair<int, int>
#define mp(a, b) make_pair((a), (b))
#define Flush fflush(stdout)
using namespace std;
const int N = 1000050;
const int inf = 0x3f3f3f3f;
const ll mod = 998244353LL;
clock_t TIME_START, TIME_END;
void program_end()
{
#ifdef ONLINE
    printf("\nTime used: %.6lf(s)\n", ((double)TIME_END - TIME_START) / CLOCKS_PER_SEC);
    system("pause");
#endif
}
int n;
int s[N];
multiset<int, greater<int>> S1, S2;
set<int> vis;
int id[N];
int tot;

inline int Query(int x)
{
    auto it = vis.lower_bound(x);
    if (it != vis.begin())
    {
        it--;
        return *it;
    }
    return -1;
}

void solve()
{
    cin >> n;
    for (int i = 1; i <= st(n); ++i)
        scanf("%d", &s[i]);
    for (int i = 1; i <= st(n); ++i)
        vis.insert(s[i]);
    for (int i = 1; i <= st(n); ++i)
        S1.insert(s[i]);
    sort(s + 1, s + st(n) + 1, greater<int>());
    S2.insert(s[1]);
    S1.erase(S1.find(s[1]));
    if (S1.count(s[1]) == 0)
        vis.erase(s[1]);
    int tim = 1;
    vector<int> tmp;
    while (tim <= n)
    {
        // puts("flag");
        tmp.clear();
        for (auto &i : S2)
        {
            int x = Query(i);
            if (S1.empty())
                return puts("Yes"), void();
            if (x == -1 || S1.find(x) == S1.end())
                return puts("No"), void();
            S1.erase(S1.find(x));
            if (S1.find(x) == S1.end())
                vis.erase(x);
            if (S1.empty())
                return puts("Yes"), void();
            tmp.push_back(x);
        }
        for (auto &i : tmp)
            S2.insert(i);
        tim++;
    }
    puts("No");
}

int main()
{
    TIME_START = clock();
    int Test = 1;
    // cin >> Test;
    while (Test--)
        solve();
    TIME_END = clock();
    program_end();
    return 0;
}
/*
3
5 4 4 4 3 3 2 1
*/
```


---

## 作者：AlanFong (赞：4)

## [题目传送门](https://www.luogu.com.cn/problem/AT_abc140_f)
# 题意  
题意很清楚，不需要翻译。
# 思路  
这道题目一看，很快就发现可以使用贪心解决。  
那具体怎么贪呢？  
首先，我们进行排序，最大值为第一个，之后开始生，每一个已经生的找自己可以生的最大值。如果有已经被生过的史莱姆找不到可以生的，输出 `No`，如果按如此流程流畅地生到了最后，输出 `Yes`。  
# 具体实现  
听说大家都喜欢用 STL，但是本蒟蒻不懂，于是我用两个数组分别记录如今的状态和本次生之前的状态，然后使用两个下标分别寻找被生的和没被生的，因为如此寻找时，被生过的数值会从大到小递减，所以，我们寻找尚未被生的史莱姆的时候，只要从头找到尾，单次时间复杂度 $\mathcal{O}(2^n)$,总体时间复杂度 $\mathcal{O}(n2^n)$。  
最大的优势不在于时间复杂度，而是不需要理解与使用 STL。   
当然劣势在于码量比较大。 
# code  
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,num,a[3000005],vis[3000005],nvis[3000005];
bool cmp(int a,int b)
{
    return a>b;
}
signed main()
{
    //freopen("slimes.in","r",stdin);
    //freopen("slimes.out","w",stdout);
    cin>>n;
    num=n;
    n=(1<<n);
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    sort(a+1,a+n+1,cmp);
    if(a[1]==a[2])//当有两个最大值
    {
        cout<<"No"<<endl;
        return 0;
    }
    vis[1]=1;
    nvis[1]=1;//nvis为当前的状态，vis为此次生成前的状态
    for(int i=1;i<=num;i++)
    {
        int cnt=0,po=1,npo=1;
        while(po<=n&&npo<=n&&cnt<(1<<(i-1)))//当生成还没有完成且可以继续
        {
            if(vis[po]==0)
            {
                po++;
                continue;
            }
            if(vis[npo]==1)
            {
                npo++;
                continue;
            }
            if(a[po]>a[npo])
            {
                cnt++;
                nvis[npo]=1;
                po++;
                npo++;
            }else{
                npo++;
            }
        }
        if(cnt<(1<<(i-1)))//可生成数不足够
        {
            cout<<"No"<<endl;
            return 0;
        }
        for(int j=1;j<=n;j++)
        {
            vis[j]=nvis[j];
        }
    }
    cout<<"Yes"<<endl;
    return 0;
}
```

---

## 作者：shinzanmono (赞：4)

# ABC140F 题解

我们可以知道，如果这种集合可以作为最后的结果，那么第一个史莱姆一定是最大的，然后我们考虑剩下的情况。

对于每一秒，一个史莱姆一定生成的是剩余史莱姆中第一个小于它的史莱姆，这是一种贪心策略，一种可行的生成方式必然与上面这种相同。

当一个物品无法生成比他小的史莱姆的时候，这种情况就会被判定为无解。

我们使用三个 `std::multiset` 模拟即可。

```cpp
#include<iostream>
#include<algorithm>
#include<set>
const int sz=3e5+10;
int arr[sz];
int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n,m;
    std::cin>>n,m=1<<n;
    for(int i=1;i<=m;i++)std::cin>>arr[i];
    std::sort(arr+1,arr+m+1,std::greater<int>());
    std::multiset<int,std::greater<int>>s,t;
    std::multiset<int>rest;
    s.insert(arr[1]),t.insert(arr[1]);
    for(int i=2;i<=m;i++)rest.insert(arr[i]);
    for(int i=1;i<=n;i++){
        for(int x:s){
            auto it=rest.lower_bound(x);
            if(it==rest.begin())std::cout<<"No\n",exit(0);
            t.insert(*--it),rest.erase(it);
        }
        s=t;
    }
    std::cout<<"Yes\n";
    return 0;
}
```

---

## 作者：NahX_ (赞：3)

水题，发现每次分裂出大的史莱姆一定不劣，因为小的史莱姆能分裂的大的一定行，那么模拟 $n$ 轮分裂即可。

---

## 作者：_Life_ (赞：3)

### 题外话
给出一种 $O(n2^n)$ 的解法 跑得飞快

~~不知道比 $\sout{O(n^22^n)}$ 的解法高到哪里去了~~

暂时抢下了[最优解](https://www.luogu.com.cn/record/47978276) 
在不吸氧不大力卡常的情况下比目前最快的 ${O(n^22^n)}$解法 ~~`+1s`~~ 快一秒

### 题意

初始时有 $1$ 个东东，每个东东每秒都可以生出一个大小小于自己（正整数）的东东，问 $n$ 秒后，能否得到给定的东东序列（序列中共有 $2^n$ 个东东 ）

### 题解

可以用贪心+大力模拟的方法解决

先确定初始的东东，初始的东东显然是给定的东东序列中最大的那一个

然后按照贪心策略模拟：从大到小遍历东东序列，当前的东东生出了 在比他小的东东中 前 ($n$减去当前东东出生时间) 大的东东

这种贪心策略可以拿到 $81$ 分的高分 因为会被下面这组 `hack` 数据卡掉
```
Input:
3
1 1 1 1 2 3 4 5
Output:
Yes
```

下面才是正确的贪心策略 ~~个人感觉正确性挺显然的~~：

在目前已经出生的东东中从大到小遍历，每个东东都会生出 目前尚未出生的 比自己小的东东中 最大的东东

以上步骤要执行 $n$ 遍，最后判断生出的东东数量是否为 $2^n$ 即可

### 代码

因为同学都说我代码写的很怪 所以会给出部分核心代码的解释 ~~指全部核心代码都需要解释不然同学都说看不懂orz~~

```cpp
//对输入数据排序，进行离散化
//l,r中存储第num小的数的区间左端点和区间右端点（左闭右闭）
//fa实际上是链表的指针数组 而且还是带路径压缩的链表（大雾）
sort(x,x+n);
for(int i=0;i<n;i++)
	if(x[i]!=x[i+1])
	{
		fa[num]=num-1;
		r[num]=i;
		l[++num]=i+1;
	}
```

```cpp
//find函数会返回还未出生的 最大的 大小<=x的东东 的大小
int find(int x)
{
	if(l[x]<=r[x])//如果当前区间非空
		return x;
	return fa[x]=find(fa[x]);//你要的路径压缩
}
```

```cpp
//heap指向一个大根堆
//temp指向一个垃圾桶 用于回收目前已经出生的东东
heap=&a;temp=&b;
(*heap).push_back(num-1);//把初始的东东丢进堆里
l[num-1]++;//因为初始的东东被丢进堆里（删除）了 所以l++（该区间东东个数-=1） 
tot++;//tot是已出生的东东个数
```

```cpp
make_heap((*heap).begin(),(*heap).end());//建堆 注意make_heap的复杂度是线性的
(*temp).clear();//倒光垃圾桶
```

```cpp
int u=(*heap)[0];//取出堆中最大元素
pop_heap((*heap).begin(),(*heap).end()),(*heap).pop_back();//删除堆顶
(*temp).push_back(u);//在垃圾桶里备份

int v=find(u-1);//寻找比u小的未出生的东东
if(v!=0)//存在比u小的未出生的东东
{
	l[v]++;
	tot++;
	(*temp).push_back(v);//在垃圾桶里备份
}
```

```cpp
//指针的舞蹈 个人认为最神奇、最优美的一句（也是同学认为最难理解的一句orz）
//执行完上面的语句后 垃圾桶里备份了所有已经出生的东东大小
//所以我们现在让heap指向垃圾桶 temp指向原来的堆
//配合上面的make_heap((*heap).begin(),(*heap).end())和(*temp).clear()一起作用
//开启一次新的轮回
swap(temp,heap);
```

```cpp
//完整代码orz
#include<queue>
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
int s,x[300001];
int num=1,l[300001],r[300001],fa[300001];
int tot;
vector <int> *temp,*heap,a,b;
void read(int &x)
{
	int f=1;x=0;
	char s=getchar();
	while(s<'0'||s>'9')
	{
		if(s=='-')
			f=-1;
		s=getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=x*10+s-'0';
		s=getchar();
	}
	x*=f;
}
int find(int x)
{
	if(l[x]<=r[x])
		return x;
	return fa[x]=find(fa[x]);
}
int main()
{
	scanf("%d",&s);
	int n=(1<<s);
	for(int i=0;i<n;i++)
		read(x[i]);
	sort(x,x+n);
	for(int i=0;i<n;i++)
		if(x[i]!=x[i+1])
		{
			fa[num]=num-1;
			r[num]=i;
			l[++num]=i+1;
		}
	//for(int i=0;i<n;i++)printf("%d ",x[i]);
	//for(int i=1;i<=num;i++)printf("\n%d %d",l[i],r[i]);
	heap=&a;temp=&b;
	(*heap).push_back(num-1);
	l[num-1]++;
	tot++;
	for(int i=0;i<s;i++)
	{
		make_heap((*heap).begin(),(*heap).end());
		(*temp).clear();
		while(!(*heap).empty())
		{
			int u=(*heap)[0];
			pop_heap((*heap).begin(),(*heap).end());
			(*heap).pop_back();
			(*temp).push_back(u);

			int v=find(u-1);
			if(v!=0)
			{
				l[v]++;
				(*temp).push_back(v);
				tot++;
			}
		}
		swap(temp,heap);
	}
	if(tot==n)
		puts("Yes");
	else
		puts("No");
}
```

---

## 作者：csh0908 (赞：2)

## 思路
一开始看到这题时，很本能地想到了一个错解，就是从大到小排序，如果没有严格单调递减，那么不行。但很容易就被 hack 了。给组样例：$2$ $4$ $3$ $3$ $2$。

$4$ 可以生 $3$，$4$ 再生 $3$，第一个被生出的 $3$ 再生 $2$。按照上面的说法显然不对。

那么我们可以按照题目说的一个性质，进行大模拟。因为只有**大的能生小的**，所以我们可以从大到小排序，然后每次模拟生的过程。

## 实现过程
需要生 $n$ 轮，所以外面的 for 从 $1\sim n$ 循环，每次模拟用一个数组 $use[i]$ 去记录前 $i-1$ 轮是否被生过，$nuse[i]$ 去记录前 $i$ 轮是否可以被生，while 循环用一个指针从下标 $1$ 开始去找本轮可以生的，也就是 $use[i]$ 记录过被生过的，然后再用一个指针从下标 $1$ 开始去找没被生过的，如果生过的**大于**没被生过的，那么当前没被生过的就可以被生，用 $nuse[i]$ 记录一下，两个指针右移，同时还要记录本轮生的数量。否则找没被生过的的指针右移，继续找。找完后，如果本轮都没生够，那么后面肯定都生不够，那么直接输出 No。再把 $nuse[i]$ 赋给 $use[i]$，这样就把前 $i$ 轮的记录的生过的值传给了 $use[i]$。这里简单说一下为什么要开两个数组记录，只开一个的话，无法分清当前已经被生了的是不是上几轮被生的，这轮能不能生。

## 其他注意事项




1. 排序后要特判 $a[1]$ 是否等于 $a[2]$，最大的生不出和自己一样大的。
2. 数组记得开大于 $2^n$。
3. $use[1]$ 和 $nuse[1]$ 要初始化为 $1$，最大的必生。
4. 如果到最后都可以，别忘了输出 Yes。

---

## 作者：ycy1124 (赞：2)

### 题意
初始时有一只任意大的史莱姆，每一轮每只史莱姆会分裂出一只小于他的史莱姆（注意他自己不会变小）。给出一个大小为 $2^n$ 的集合，试问在 $n$ 轮后能否分裂出该集合。
### 思路
考虑贪心，首先不难发现最初的史莱姆就是集合中最大的史莱姆。然后考虑每只史莱姆每轮分裂出哪一只史莱姆，由于越小的史莱姆可选择的分裂对象越少，所以我们优先分裂出大的史莱姆。发现集合可重，所以使用 multiset。对于每一只史莱姆每轮分裂出集合中他所能分裂且还未被分裂出的最大的史莱姆，当有一只史莱姆无法再分裂时输出 `No`，否则输出 `Yes`。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
multiset<int>s;
int n,a[2<<18],tot,js;
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=(1<<n);i++){
        int w;
        cin>>w;
        s.insert(w);
    }
    auto it=s.end();
    --it;
    a[++tot]=*it;
    s.erase(it);
    s.insert(1e9+7);
    for(int i=1;i<=n;i++){
        js=tot;
        for(int j=1;j<=tot;j++){
            it=s.lower_bound(a[j]);
            if(*it==*s.begin()){ 
                cout<<"No";
                return 0;
            }
            --it;
            a[++js]=*it;
            s.erase(it);
        }
        tot=js;
    }
    cout<<"Yes";
    return 0;
}
```
[AC 记录。](https://www.luogu.com.cn/record/198376354)

---

## 作者：zzwdsj (赞：2)

## 思路
数据范围是 $1<=n<=18$，$2^{n}$ 最大是 $262144$，可以直接模拟。

不难想到，我们可以将第一个史莱姆的健康值设为集合中的最大值。如果第一个史莱姆的健康值大于集合中的最大值，那么就第一个史莱姆的健康值就不在集合中；如果第一个史莱姆的健康值小于集合中最大值。那么就不可能分裂出健康值达到集合中最大值的史莱姆。

可以使用贪心的思路，史莱姆由健康值从大到小的顺序依次分裂。当某个史莱姆需要分裂时，将它分裂出的史莱姆的健康值设为在集合 S 中**还未出现**的部分中小于那个史莱姆的健康值且最大的数。
## 实现方法
使用一个 map 存储还需要哪些健康值以及每个需要的健康值还需要几只史莱姆。再使用一个 multimap 存储已经产生的史莱姆健康值分别是什么。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,maxn,x,cnt,sum;
long long v[270000];
multiset<long long,greater<long long> >s;//由于需要从大到小遍历，multiset内部按从大到小的顺序排序
map<long long,long long,greater<int> > t;//由于需要查找小于某个数且最大的数，map内部按从大到小的顺序排序
int main()
{
	scanf("%lld",&n);
	m=1<<n;//m表示集合s的元素个数
	for(int i=1;i<=m;i++)scanf("%lld",&x),maxn=max(maxn,x),t[x]++;
	t[maxn]--;
	s.insert(maxn);
	while(s.size()!=m)//数量打不到集合s的元素个数就一直分裂
	{
		cnt=0;//cnt表示新分裂出的史莱姆有几个
		for(auto i:s)
		{
			auto h=t.upper_bound(i);//查找集合S中还未出现的部分中小于那个史莱姆的健康值且最大的数
			if(h==t.end())//如果找不到说明无法分裂出集合S
			{
				printf("No");
				return 0;
			}
			t[(*h).first]--;//对应健康值需要的史莱姆数量减1
			v[++cnt]=(*h).first;//记录下新分裂出的史莱姆
			if(t[(*h).first]==0)t.erase(h);//如果对应健康值需要的史莱姆数量是0则删除这个需要的健康值
		}
		for(int i=1;i<=cnt;i++)s.insert(v[i]);
	}
	printf("Yes");
	return 0;
}
```

---

## 作者：Composite_Function (赞：0)

每个点一定会选择生出恰好比自己小的可以生成的最大的史莱姆，这样对于后续的操作一定更优。

考虑怎么维护最大。我选择手写一颗线段树维护：

- 初始为多重集。
- 删除一个点。
- 维护最大值。

即可。

---

```cpp
#include <bits/stdc++.h>
using namespace std;

struct FastIO {
	inline FastIO& operator >> (short& x) {
		x = 0;
		char f = 0, ch = getchar();
		while (ch > '9' || ch < '0') f |= (ch == '-'), ch = getchar();
		while (ch <= '9' && ch >= '0') x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
		return x = (f ? -x : x), *this;
	}
	inline FastIO& operator >> (int& x) {
		x = 0;
		char f = 0, ch = getchar();
		while (ch > '9' || ch < '0') f |= (ch == '-'), ch = getchar();
		while (ch <= '9' && ch >= '0') x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
		return x = (f ? -x : x), *this;
	}
	inline FastIO& operator >> (long long& x) {
		x = 0;
		char f = 0, ch = getchar();
		while (ch > '9' || ch < '0') f |= (ch == '-'), ch = getchar();
		while (ch <= '9' && ch >= '0') x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
		return x = (f ? -x : x), *this;
	}
	inline FastIO& operator >> (double& x) {
		x = 0;
		char f = 0, ch = getchar();
		double d = 0.1;
		while (ch > '9' || ch < '0') f |= (ch == '-'), ch = getchar();
		while (ch <= '9' && ch >= '0') x = x * 10 + (ch ^ 48), ch = getchar();
		if (ch == '.') {
			ch = getchar();
			while (ch <= '9' && ch >= '0') x += d * (ch ^ 48), d *= 0.1, ch = getchar();
		}
		return x = (f ? -x : x), *this;
	}
} rin;

#define ll long long
#define uint unsigned int
#define reg register
#define ld long double
#define uint unsigned int
#define ull unsigned long long
#define qint const int&
#define qll const ll&
#define quint cosnt uint&
#define qull const ull&
#define endl "\n"

inline void qmod(int& x, const int& mod) {
	x = x >= mod? x - mod : x;
}

const int N = (1 << 18) + 1;
int n, a[N], cnt[N], lsh[N], top;
int tr[N << 2];

inline void build(int u, int l, int r) {
	if (l == r) {
		tr[u] = cnt[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(u << 1, l, mid);
	build(u << 1 | 1, mid + 1, r);
	tr[u] = tr[u << 1] + tr[u << 1 | 1];
}
inline void del(int u, int l, int r, int qx) {
	--tr[u];
	if (l == r) return;
	int mid = (l + r) >> 1;
	if (qx <= mid) del(u << 1, l, mid, qx);
	else del(u << 1 | 1, mid + 1, r, qx);
}
inline int rk(int u, int l, int r, int qx) {
	if (qx <= l) return 0;
	if (r < qx) return tr[u];
	int mid = (l + r) >> 1;
	if (mid >= qx) return rk(u << 1, l, mid, qx);
	else return tr[u << 1] + rk(u << 1 | 1, mid + 1, r, qx);
}
inline int bac(int u, int l, int r, int qrk) {
	if (l == r) return l;
	int mid = (l + r) >> 1, lnum = tr[u << 1];
	if (qrk <= lnum) return bac(u << 1, l, mid, qrk);
	else return bac(u << 1 | 1, mid + 1, r, qrk - lnum);
}
inline int pop(int x) {
	int rkx = rk(1, 1, top, x);
	if (rkx == 0) return 0;
	int res = bac(1, 1, top, rkx);
	del(1, 1, top, res);
	return res;
}

signed main() {
	rin >> n;
	for (int i = 1; i <= (1 << n); ++i)
		rin >> a[i], lsh[++top] = a[i];
	sort(lsh + 1, lsh + top + 1);
	top = unique(lsh + 1, lsh + top + 1) - lsh - 1;
	for (int i = 1; i <= (1 << n); ++i)
		a[i] = lower_bound(lsh + 1, lsh + top + 1, a[i]) - lsh;
	for (int i = 1; i <= (1 << n); ++i) ++cnt[a[i]];
	build(1, 1, top);
	vector<int> vec;
	vec.push_back(pop(top + 1));
	for (int i = 1; i <= n; ++i) {
//		cout << "turn " << i << " : ";
		vector<int> nvec = vec;
		for (int j : vec) {
			int ret = pop(j);
//			cout << j << " -> " << ret << "; ";
			if (ret == 0) {
				cout << "No" << endl;
				return 0;
			}
			nvec.push_back(ret);
		}
//		cout << endl;
		vec = nvec;
	}
	cout << "Yes" << endl;
	return 0;
}
```

---

## 作者：ztd___ (赞：0)

来点不一样的抽象做法。

### 题意
洛谷翻译似乎缺了点东西，所以补充一下。

你有一只史莱姆，你可以随意设定它的实力。在每一秒内，每只史莱姆都可以分裂出一只**实力严格小于它**的史莱姆，且分裂出的这只史莱姆也可以随意设定实力。现给定 $n$ 及大小为 $2^n$ 的集合 $S$，求问是否能分裂出该集合。

### 思路 & 分析
这部分可以参考其他的题解，讲的会更详细。

首先可以知道，肯定是先分裂实力更高的史莱姆。实力更低的显然不优。因为实力低的能分裂的，实力高的肯定也能分裂。

那么将 $S$ 排序，取最大值作为初始实力，直接模拟分裂过程。分裂中，每只史莱姆都尽可能分裂出更大的史莱姆。

抽象地说，对于实力为 $k$ 的史莱姆，分裂出的史莱姆大小应为： 
$$\max \limits _{i < k \And i \in S} i$$

~~本人没有学过公式里的这些数学知识，如出错请见谅。~~
### 实现
抽象的时候到了。

首先排序取最大值一步是好做的，`sort` 一下就好。

然后我们开始头脑风暴。

- - -

先考虑暴力应该怎么写。

暴力就是硬核模拟我们的思路过程。将所有已经被分裂出来的史莱姆塞到一个容器里面，每轮分裂就遍历一遍容器。

对于容器中的每个元素，我们直接在 $S$ 中暴力找**容器外**与它相差最小、且能**由这个元素分裂出来**的元素。找不到就输出 `No`。~~有点文字游戏的味道吧？~~


然后将这个元素再塞进容器里面，做完了。

好像有点烧脑，我们举个例子。
> 对于 $n = 2, S = \lbrace 1, 2, 3, 4 \rbrace$ 这组数据：
>
> 先取数列最大值：$4$，作为初始实力。
> 
> 接着将 $4$ 扔到容器里面，设这个容器叫做 $T$，则 $T = \lbrace 4 \rbrace$。
>
> 开始遍历。找到 $4$ 能够分裂出的最大元素：$3$，那么把 $3$ 也扔到容器里面。这是第一次操作，此时 $T = \lbrace 3, 4 \rbrace$。
>
> 第二次遍历，$4$ 能够分裂出的最大元素为 $2$，所以把 $2$ 扔到 $T$ 里面，此时 $T = \lbrace 2, 3, 4 \rbrace$。
> 
> 然后 $3$ 现在能够分裂出的最大元素为 $1$，因为只剩 $1$ 了。所以 $1$ 也被扔了进去，$T = \lbrace 1, 2, 3, 4 \rbrace$。
>
> 分裂完毕，输出 `Yes`。

分析一下复杂度：模拟 $n$ 轮需要一个 $O(n)$，遍历容器需要 $O(2^n)$，暴力找又需要 $O(2^n)$，总共是 $O(n \cdot 2 ^{2n})$。

考虑到 $n \le 18$，该复杂度无法通过。

- - -

暴力无法通过，我们考虑优化。

回想一下我们实现的过程：模拟 $n$ 轮是必须的，遍历容器进行分裂也是必须的，能够优化的只有暴力找。

发现我们已经将 $S$ 排好序了，所以满足单调性，可以使用二分进行优化，这样复杂度将会降到 $O(n \cdot 2 ^ n \cdot \log2^n) = O(n \cdot 2 ^ n \cdot n) = O(n ^ 2 \cdot 2 ^ n)$，足以通过本题。

- - -
现在我们考虑使用什么容器来**装还没有被分裂出来的史莱姆**。

一般人的思路是：可以重复，可以二分查找，那不就是个 multiset 吗？

作者思路：能够使用 upper_bound，能够支持重复元素，那用一个 map，将元素的大小作为 key，将元素的个数作为 value，不就秒掉了吗？

~~很抽象吧。~~  
但是我们用 map 装的是还没有被分裂出来的史莱姆，肯定还要一个容器**装分裂出来过的史莱姆**。

想想这个容器要满足什么条件：
1. 我们由大到小选择史莱姆进行分裂。
2. 我们在分裂史莱姆的时候，**分裂过别的史莱姆**的史莱姆是需要弹出来的，否则我们无法对下一个史莱姆进行操作。
3. 与此同时，我们也需要将**被分裂出来**的史莱姆塞进这个容器里面。这与上一个操作应同时进行。
4. 所以我们无法保证塞回容器的史莱姆还是按大小排序的。
5. 所以该容器应拥有自主排序的功能。

排序？自然想到了优先队列。

可是一个优先队列就够了吗？

我们在对优先队列进行任一操作时，它都会进行排序。所以如果只用优先队列的话，刚弹出的史莱姆又会立即被塞到队首，从而陷入死循环。

所以我们需要一个容器进行**缓存**，这里采用队列实现。

综上所述，我们需要 $3$ 个容器：
- 一个 map，用于装还没有被分裂出来的史莱姆。
- 一个 priority_queue，用于装分裂出来过的史莱姆。
- 一个 queue，用于缓存需要塞进 priority_queue 里面的数据。

总结一下每轮分裂的步骤：

1. 扫描 priority_queue 里的每个元素，且对于元素 $a$：
   - 在 map 中对 $a$ 用 upper_bound 查找一下（注意到 upper_bound 的排序方式需由**从小到大**变为**从大到小**）。
   - 如果没有找到，说明这个史莱姆分裂不出来，输出 `No`，并结束程序。
   - 将 $a$ 弹出，塞进缓存的 queue 里面。
   - 将 upper_bound 找到的位置的 **value** 减去 $1$。
   - 如果减去后的 **value** 为 $0$，删去这个位置，以防干扰到下一次的查找。
   - 将 upper_bound 找到的位置的 **key** 塞进缓存的 queue 里面。

2. 将缓存队列里所有的元素塞回 priority_queue 里。


结束了。如果 $n$ 轮分裂后没有出现问题，输出 `Yes`。

预处理就是把最大值塞进 priority_queue 里面，其他的塞到 map 里面。
### AC Code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 5e5 + 55;
int n, cnt, a[N];
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n;
    cnt = (1 << n);
    for (int i = 1;i <= cnt;i++) {
        cin >> a[i];
    }
    sort(a + 1, a + 1 + cnt, greater<int>());
    map<int, int, greater<int> > mp;
    priority_queue<int> que;
    queue<int> save;
    que.push(a[1]);
    for (int i = 2;i <= cnt;i++) mp[a[i]]++;
    for (int i = 1;i <= n;i++) {
        while (!que.empty()) {
            auto it = mp.upper_bound(que.top());
            if (it == mp.end()) {
                cout << "No";
                return 0;
            }
            save.push(que.top());
            que.pop();
            mp[it->first]--;
            save.push(it->first);
            if (mp[it->first] == 0) mp.erase(it);
        }
        while (!save.empty()) {
            que.push(save.front());
            save.pop();
        }
    }
    cout << "Yes";
    return 0;
}
```

相比 multiset 来说，实现方法还是太抽象了。

---

## 作者：AC_love (赞：0)

首先初始史莱姆健康值一定是 $S$ 中的最大值，否则不管怎么分裂都分裂不出这个最大值。

然后我们发现：小史莱姆能分裂出的史莱姆一定是大史莱姆能分裂出的真子集。所以优先分裂大史莱姆肯定更优。

那么可以直接贪心，用 `multiset` 来维护当前没有被分裂出来的史莱姆，每轮我们让每个史莱姆都分裂出他能分裂的最大的史莱姆即可。

[code](https://atcoder.jp/contests/abc140/submissions/59471230)

---

## 作者：iamajcer (赞：0)

# 思路

按照题意，我们很好想到一种特殊情况，就是当前有两个最大值，那么肯定是不合法的，有其中一个最大值无法被生出来。

按照贪心的思想，我们肯定要对数组排个序，这样才能每次用大的史莱姆去生成小的史莱姆对吧。

每一个大史莱姆都可以生成一个小史莱姆，我们假设当前生成的小史莱姆是 A。那么 A 肯定是第一个比大史莱姆小的史莱姆。这样才更优。如果有其它的小史莱姆需要生成，肯定小于或者等于 A，肯定不会大于 A，这样就可以用别的更小的史莱姆去生。而不会出现这种情况，之前大史莱姆生成了一个最小的史莱姆，但是集合中的某个史莱姆太大了，只能用这个大史莱姆生成，但是大史莱姆没有去生成，导致这个史莱姆没有被生成。

不过生成的这些小史莱姆要按照题目给的集合去生成。

既然要按照题目所给的集合去生成，我们按照题意模拟即可。

我这里用了三个 multiset，第一个不妨称作 s，第二个称作 s2，第三个之后再讲。

s 代表当前已经生成了的史莱姆集合，s2 代表题目给定的集合，也就是还需要生成的史莱姆集合。每次生成一个史莱姆，就在 s 中加入史莱姆，s2 删去史莱姆就好。

但是这样操作会让 s 集合不断更新，导致循环出问题，所以我们开一个辅助集合 t，这样把加入的史莱姆先加入在 t 中，最后再把 t 覆盖给 s 就行了。

这样的操作一共会进行 $n$ 次，简单模拟下就可以知道为什么了，这里不过多赘述。

如何去找第一个比自己要小的史莱姆？可以二分查找，因为 $a_i$ 排过序后，有单调性，且维护的集合带有自动排序的功能，也有单调性。

# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=270005;

int n, a[N], cnt=0;
multiset<int> s, t, s2;
multiset<int>::iterator it, it2;
bool cmp(int a, int b)
{
	return a>b;
}
int main()
{
	scanf("%d", &n);
	for (int i=1; i<=(1<<n); i++) scanf("%d", &a[i]);
	sort(a+1, a+1+(1<<n), cmp);
	
	if (a[1]==a[2])
	{
		printf("No");
		return 0;
	}
	
	s.insert(a[1]);
	t.insert(a[1]);
	for (int i=2; i<=(1<<n); i++) s2.insert(a[i]);
	
	for (int i=1; i<=n; i++)
	{
		for (it=s.begin(); it!=s.end(); it++)
		{
			it2=s2.lower_bound((*it));
			
			if (it2==s2.begin()) //没有史莱姆可以生成了
			{
				printf("No");
				return 0;
			}
			
			it2--;
			t.insert((*it2));
			s2.erase(it2);
		}
		s=t;
		
	/*	for (it=s.begin(); it!=s.end(); it++) printf("%d ", (*it));
		puts("");*/
	}
	printf("Yes");
	
	return 0;
}
```

---

## 作者：accgj_ (赞：0)

[题目链接](https://www.luogu.com.cn/problem/AT_abc140_f)


前言：时隔三月，闲来无事，水一篇。

------------
题意：每一秒，集合中的每一个数都**可以**生成一个**严格小于**自身的**正整数**（初始有一个正整数），现在给出一个集合，问这个集合能不能从某个只包含一个正整数的集合变化过来。



------------
题目限制很宽，并且数据范围不大，显然，我们肯定是先生成大的数再生成小的数，并且最大值只有一个，考虑保存下每一个回合可以生成多少数。

那么从大到小讨论每一个大小的数，用堆存下当前可以在哪些回合生成数，每新生成一个数，那么在生成它的回合之后的每一个回合都能再生成一个数。

由于从大到小考虑，不会出现不合题意的情况，而当某次生成时当前可以生成的数的个数不足以生成当前讨论到的这个大小，那么就无法生成，否则就可以。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int num;
int a[10000001];
bool cmp(int qw,int qe){return qw>qe;}
int x,nx;
priority_queue<int> q;
queue<int> q2;
int main()
{

	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;x=n;
	for(int i=1;i<=n;i++)q.push(i);//保存当前可以生成的数的回合
	num=pow(2,n);
	for(int i=1;i<=num;i++)cin>>a[i];
	sort(a+1,a+1+num,cmp);
	if(a[1]==a[2])
	{
		cout<<"No\n";return 0;//最大值只能有一个
	}
	for(int i=2;i<=num;i++)
	{
		nx=0;
		while(a[i]==a[i+1])i++,nx++;//讨论同一个大小的数
		nx++;
		if(nx>q.size())
		{
			cout<<"No\n";return 0;
		}//可生成的数不够
		for(int i=1;i<=nx;i++)
		{
			q2.push(q.top()-1);q.pop();
		}
		while(!q2.empty())
		{
			if(q2.front()==0)q2.pop();
			else 
			{
				for(int j=0;j<q2.front();j++)q.push(q2.front()-j);
				q2.pop();
			}
		}//从生成该数的下一个回合开始，每一个回合可以生成一个数
		if(x<0)
		{
			cout<<"No\n";return 0;
		}//这是三个月前的代码，我也不知道这有什么用，但是就不改了（
	}
	cout<<"Yes\n";
	return 0;
}
```


---

