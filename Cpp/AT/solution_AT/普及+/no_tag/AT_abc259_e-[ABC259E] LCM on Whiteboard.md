# [ABC259E] LCM on Whiteboard

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc259/tasks/abc259_e

$ N $ 個の整数 $ a_1,\ldots,a_N $ が白板に書かれています。  
 ここで、$ a_i $ は $ m_i $ 個の素数 $ p_{i,1}\ \lt\ \ldots\ \lt\ p_{i,m_i} $ と正整数 $ e_{i,1},\ldots,e_{i,m_i} $ を用いて $ a_i\ =\ p_{i,1}^{e_{i,1}}\ \times\ \ldots\ \times\ p_{i,m_i}^{e_{i,m_i}} $ と表せる整数です。  
 あなたは $ N $ 個の整数から $ 1 $ つ選んで $ 1 $ に書き換えます。  
 書き換えた後の $ N $ 個の整数の最小公倍数としてあり得る値の個数を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ m_i $
- $ \sum{m_i}\ \leq\ 2\ \times\ 10^5 $
- $ 2\ \leq\ p_{i,1}\ \lt\ \ldots\ \lt\ p_{i,m_i}\ \leq\ 10^9 $
- $ p_{i,j} $ は素数
- $ 1\ \leq\ e_{i,j}\ \leq\ 10^9 $
- 入力はすべて整数

### Sample Explanation 1

白板に書かれている整数は $ a_1\ =7^2=49,\ a_2=2^2\ \times\ 5^1\ =\ 20,\ a_3\ =\ 5^1\ =\ 5,\ a_4=2^1\ \times\ 7^1\ =\ 14 $ です。 $ a_1 $ を $ 1 $ に書き換えると白板に書かれている整数は $ 1,20,5,14 $ となり、これらの最小公倍数は $ 140 $ です。 $ a_2 $ を $ 1 $ に書き換えると白板に書かれている整数は $ 49,1,5,14 $ となり、これらの最小公倍数は $ 490 $ です。 $ a_3 $ を $ 1 $ に書き換えると白板に書かれている整数は $ 49,20,1,14 $ となり、これらの最小公倍数は $ 980 $ です。 $ a_4 $ を $ 1 $ に書き換えると白板に書かれている整数は $ 49,20,5,1 $ となり、これらの最小公倍数は $ 980 $ です。 以上より、書き換えた後の $ N $ 個の整数の最小公倍数としてあり得る値は $ 140,490,980 $ であり、この入力における答えが $ 3 $ と分かります。

### Sample Explanation 2

白板に書かれている整数はとても大きい場合があります。

## 样例 #1

### 输入

```
4
1
7 2
2
2 2
5 1
1
5 1
2
2 1
7 1```

### 输出

```
3```

## 样例 #2

### 输入

```
1
1
998244353 1000000000```

### 输出

```
1```

# 题解

## 作者：FFTotoro (赞：5)

本题显然我们可以用这种方法存储一个数：

用一个数组（可能是 `std::vector` 或其他的 STL 实现），每个元素是一个二元组，`first` 存的是底数，`second` 存的是指数。这样，最后我们可以统计出总共能产生多少个数，再丢到 set 里面去重一下即可。

现在我们来看看如何求这些数——可以根据最大公约数与最小公倍数的定义：

对于每个数判断它的某个质因数的次幂是不是所有中最高的，

- 如果不是最高的说明它对求出来的最小公倍数中分解的的这个质因数的次幂没有影响；

- 否则去除它外其他数的最小公倍数的这个质因数的次幂就是**其他数中的分解质因数中包含这个质因数次幂的最大值**。

这样，我们使用 `std::map` 可以很轻易地解决。

放代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define map unordered_map
using namespace std;
map<int,int> p[200001];
signed main(){
	int n,c=0; cin>>n;
	map<int,pair<int,int> > mp;
	set<vector<pair<int,int> > > s;
	for(int i=1;i<=n;i++){
		int m; cin>>m;
		for(int j=1;j<=m;j++){
			int x,y; cin>>x>>y; p[i][x]=y;
			if(y>=min(mp[x].first,mp[x].second)){
				if(mp[x].first>mp[x].second)mp[x].second=y;
				else mp[x].first=y;
			}
		}
	}// 记录最高次幂
	for(int i=1;i<=n;i++){
		vector<pair<int,int> > v;
		for(auto [f,e]:p[i]){
			if(e==max(mp[f].first,mp[f].second)&&e>min(mp[f].first,mp[f].second)){
				v.push_back(make_pair(f,e-mp[f].second));
			}
		}
		int sz=s.size(); s.insert(v);
		if(s.size()>sz)c++;
	} // 求出最小公倍数并去重
	cout<<c<<endl;
	return 0;
}
```

---

## 作者：__YSC__ (赞：4)

# 题目描述

给定 $N$ 个表示成 $A_i=\prod \limits_{j=1}^{M_i} P_{i,j}^{E_{i,j}}$ 的正整数 $A_i$，其中 $P_{i,j}$ 为质数。现在你要选择一个 $A_i$ 并将其变为 $1$。求有多少种可能的 $\operatorname{lcm}$。

# 思路

首先，我们可以得到 $\operatorname{lcm} = \prod \limits_{x\in \mathbb{P}} x^{\max \limits_{P_{i,j}=x}\{E_{i,j}\}}$，其中 $\mathbb{P}$ 表示质数集。如果一个 $A_i$ 中包含了某一个 $P_{i,j}^{\max \limits_{P_{x,y}=P_{i,j}}\{E_{x,y}\}}$ 并且只有 $A_i$ 包含，则当我们 $A_i \leftarrow 1$ 时 $\operatorname{lcm}$ 就会改变，否则不变。使用 `map` 统计最大值即可。

空间复杂度 $O(\sum \limits_{i=1}^N M_i)$，时间复杂度 $O(\sum \limits_{i=1}^N M_i \log (\sum \limits_{i=1}^N M_i))$

## 细节

注意还要统计 $\operatorname{lcm}$ 不变的情况。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 200001;

int n, m[MAXN], ans;
bool ok;
vector<int> p[MAXN], e[MAXN];
map<int, int> maxe, pos, cnt;

bool check(int x) {
  for(int i = 1; i <= m[x]; ++i) {
    if(pos[p[x][i]] == x) {
      return 1;
    }
  }
  ok = 1;
  return 0;
}

int main() {
  ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
  cin >> n;
  for(int i = 1; i <= n; ++i) {
    cin >> m[i];
    p[i].resize(m[i] + 1);
    e[i].resize(m[i] + 1);
    for(int j = 1; j <= m[i]; ++j) {
      cin >> p[i][j] >> e[i][j];
      if(maxe[p[i][j]] < e[i][j]) {
        maxe[p[i][j]] = e[i][j];
        pos[p[i][j]] = i;
      }else if(maxe[p[i][j]] == e[i][j]) {
        pos[p[i][j]] = 0;
      }
    }
  }
  for(int i = 1; i <= n; ++i) {
    ans += check(i);
  }
  cout << ans + ok;
  return 0;
}

```

---

## 作者：Ivan422 (赞：2)

题目大意：给出 $n$ 个分解质因数后的数，我们可以选择任意一个数将其设为 $1$，求操作后对所有数求最小公倍数的可能结果总数。

思路：首先看到数据范围，高精度显然已经存不下了，所以考虑其他方法。考虑求最小公倍数的性质，修改一个数只会对这个数分解后的质数有关，要是这个质数的次数是所有数对应质数次数的最大值有关。要是这个质数的次数不是最大值，那对其进行求最小公倍数显然没有变化。否则要是这个最大值没了，但是次大值依旧是与最大值相等，那也不会有变化。要是有一个变化，就说明这次修改产生了新的数，统计结果。要是一整个操作都没有影响，就是原数了。注意可能很多修改都没有作用，但是原数只能统计一次，就得开一个变量来判定是否出现原来的结果。最后输出即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,m[N],x,y,ans,fj;
vector<int>e[N],p[N];
map<int,int>fmx,smx;
signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>m[i];
        for(int j=1;j<=m[i];j++){
            cin>>x>>y;
            p[i].push_back(x);
            e[i].push_back(y);
            if(y>fmx[x]){smx[x]=fmx[x];fmx[x]=y;}
            else if(y>smx[x]){smx[x]=y;}
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<m[i];j++){
            if(e[i][j]==fmx[p[i][j]]&&e[i][j]!=smx[p[i][j]]){
                ans++;
                goto next;
            }
        }
        fj=1;
        next:;
    }
    cout<<ans+fj;
    return 0;
}
```

---

## 作者：Windy_Hill (赞：2)

## 题意
给定 $n$ 个数的质因数分解，将其中一个变为 $1$，问最后 $n$ 个数的最小公倍数的不同个数。

## 思路

观察第一个样例:

```
4
1
7 2
2
2 2
5 1
1
5 1
2
2 1
7 1
```

第一个数为 $49$

第二个数为 $20$

第三个数为 $5$

第四个数为 $14$

若删去第一个数 $49$，会将最小公倍数中的 $7$ 减少一个。

若删去第二个数 $20$，会将最小公倍数中的 $5$ 减少一个。

若删去第三个数 $5$，最小公倍数不变。

若删去第四个数 $14$，最小公倍数不变。

## 结论

我们会发现当且仅当这个数中有一项次数最大，且其他数的此项都 **严格小于** 这项的次数时，会多一个答案。

对于无贡献的数，只要有，答案也会加一。

## 代码

```cpp

#include <bits/stdc++.h>

using namespace std;

map<int, int> t;// t[x] 表示 x 中次数最大的是几次
map<pair<int, int>, int> z; // t[{x, y}]表示数是 x 次数是 y 的数有几个
vector<pair<int, int> > a[200010];

int main()
{
    int n;
    scanf("%d", &n);
    
    for (int i = 1; i <= n; i ++ ) 
    {
        int k;
        scanf("%d", &k);
        while (k -- )
        {
            int x, y;
            scanf("%d%d", &x, &y);
            a[i].push_back({x, y});
            t[x] = max(t[x], y);//这项中次数最大的有几次
            z[{x, y}] ++ ;
        }
    }
    
    int res = 0, p = 1;
    for (int i = 1; i <= n; i ++ )
    {
        bool chenge = false;//表示是否有变化
        for (int j = 0; j < a[i].size(); j ++ )
            if (z[a[i][j]] == 1 && t[a[i][j].first] == a[i][j].second)//z[a[i][j]] 表示 有没有和他次数一样的
                chenge = true;
        if (chenge == true) res ++ ;
        else res += p, p = 0;//处理没有变化的情况
    }
    
    cout << res;
    
    return 0;
}

```

---

## 作者：LastKismet (赞：0)

# 题目链接
[ABC259E](https://atcoder.jp/contests/abc259/tasks/abc259_e)

[LG-ATabc259e](https://www.luogu.com.cn/problem/AT_abc259_e)

# 思路
首先我们了解一个最小公倍数的性质：

> 对于任意个数，其最小公倍数就是他们中每一种质因数的最大次数的乘积。
>
> $\text{e.g.}$ 对于 $15$、$21$ 和 $9$，它们的最小公倍数可以表示成 $7^1×5^1×3^2$，即 $315$。
>
> 这三个数中，$7^1$ 是由 $21$ 给出的，$5^1$ 由 $15$ 给出。
>
> **三个数中都含有 $3$ 这个质因子，但在 $9$ 中，质因子的次数最大为 $2$，因此就在 $9$ 取 $3^2$ 计算最大公倍数。**

因此，我们可以得出，**几个数的最大公倍数，只和这些数的所有质因子的最大次数项有关**。

下面，我将称呼更改之后会影响最大公倍数的数为*关键数*。

对于每一个数，我们只需要明白这个数中是否存在有**次数最大的**质因子项，就可以分辨出这个数是否是*关键数*了。

但题目要求的是**所有可能的最大公倍数个数**，怎么办？

首先介绍一个特别简单的性质：

> 质因子不同的数不同。

假设次数最大的质因子项只有一个，那么它所对应的*关键数*也就只有一个，那么更改每一个*关键数*，都会更改不同的质因子项，最后产生的最大公倍数也就各不相同，这种情况下直接输出*关键数*个数即可。

这里就有一个坑点——**次数最大的质因子项可能不止一个！！**

那么我们考虑这种情况，就会发现，**由于一次只能删一个项，所以这两个质因子项至少会留一个下来**，对最终的结果并不会产生影响。因此，这种情况下，**这两个数都不是*关键数***。

这样，我们就考虑完了所有情况……了吗？

这还有一个坑点：**有可能存在更改后最大公倍数和原来相同的情况。**

很明显，我们先前计算的*关键数*个数中并不包括这一种情况。另外，由于可能每一个数都是关键数，这一种情况不一定存在。

所以，在求*关键数*的时候，顺便看一下有没有非关键数，如果没有，最后结果 $+1$ 即可。

# 解法
对于每一个数，我们都遍历它的每一个质因子项 *（这可以和输入同时进行）*，如果它的某个质因子项大于当前的最大次数项，就更新这个质因子对应的最大次数，同时更新这个质因子最大次数的项数为 $1$。

如果如果它的某个质因子项等于当前的最大次数项，把项数 $+1$。

另外的，我们记录一下每个质因子最大次数项对应的是哪一个数，这是因为存在**多个最大次数项都对应了同一个*关键数***的情况。

为了解决上述情况，我们最后统计的时候只需要统计所有**对应了最大次数项**的数即可。

> 具体地，我们可以在最后统计前遍历所有质因子项，开一个统计*关键数*对应了最大项个数的数组，将每个质因子对应的*关键数*的对应最大项个数 $+1$，最后统计时统计对应最大次数项质因子 $>0$ 的所有*关键数*个数。

但我们还没有解决一个问题：**是否存在非关键数**。

这个方法其实很多，我使用的是在更新最高次数质因子项的时候实时更新每个数对应的最大次数项个数，最后没有对应数的就是非关键数。

特殊的，**当存在多个最高次数质因子项时，应该将第一个出现的质因子项的对应数 $-1$**，因为这时候这个质因子不对应任何关键字（也就是这个质因子不会改变最大公倍数）。

最后，因为质数的范围很大，直接开计数数组不太现实，使用 `map` 储存即可。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=2e5+5;

int n;
int m[N];
int p,e;
int pmxt[N];

map<int,int> maxt;
map<int,int> maxi;
map<int,int> maxn;
map<int,int> itim;

int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>m[i];
		for(int j=1;j<=m[i];j++){
			cin>>p>>e;
			if(e>maxt[p]){
				maxt[p]=e;
				pmxt[maxi[p]]--;
				maxi[p]=i;
				maxn[p]=1;
				pmxt[i]++;
			}
			else if(e==maxt[p]){
				maxn[p]++;
				pmxt[maxi[p]]--;
			}
		}
	}
	for(auto iter:maxi)if(maxn[iter.first]==1)itim[iter.second]++;
	int ans=itim.size();
	for(int i=1;i<=n;i++){
		if(!pmxt[i]){
			ans++;
			break;
		}
	}
	cout<<ans;
	return 0;
} 
```

---

## 作者：Meickol (赞：0)

一道挺简单易想的数论题。

因为若干数的最小公倍数是由这些数中每个数唯一分解出的每个质因数的最大次幂全部连乘起来得到。

因而将其中一个数的值变为 $1$，等价于将这个数删去。

考虑什么情况下删除某一个数会对整个序列的最小公倍数造成影响，显然当这个数会作为序列中某个质因数的唯一最大次幂时，删去这个数会对整个序列的最小公倍数造成影响。



因而首先可以给输入的这 $1 \sim N$ 这些数都处理一下，看看这些数是不是对应着序列中的唯一最大质因数次幂。

如果某个数是这样的话，那么这个数被删去后一定会给答案贡献 $1$。

但若该数的质因子含有最大次幂，而这个质因子的最大次幂并不只是这第 $i$ 个数有，那么不对答案产生贡献。



因为题目保证了给定的质因数不会超过 $2 \times 10^5$ 个，我们可以考虑直接对这些质因数进行统计处理。

考虑使用一个 `std::map` 容器来建立一个键值对。将质因数作为键，值则使用一个自定义结构体。

下方为对该结构体的定义：

```cpp
struct node{
    int e,pos,cnt; //e表示最该质因数大次幂的大小，pos表示对应数位置，cnt表示该质因数最大次幂出现次数
};
```

$e$ 表示该质因数最大次幂的值，$pos$ 表示最大次幂是由哪个数贡献的，$cnt$ 表示该质因数最大次幂出现次数。

首先我们在输入完 $n$ 个数分解的结果时，将每个数分解出的质因数的最大次幂统计起来。

我们定义的这个结构体用于维护质因数对应的最大次幂值，以及该质因数最大次幂出现了多少次且是由哪个数贡献而来。



最后留意，因为答案要求 “删去” 其中某一个数，最小公倍数共有多少种可能，而序列本身是具有一个最小公倍数的，也就是说如果我们删去的那一个数不会影响整个序列原来的最小公倍数，那么也算一种情况。



```cpp
#define rep(x,y,z) for(int x=y;x<=z;x++)
const int N=2e5+5;
int n;
struct node{
	int e,pos,cnt;
};
unordered_map<int,node> mp;
bool flag[N];
void solve(){
	cin>>n;
	rep(i,1,n){
		int m;
		cin>>m;
		while(m--){
			int a,b;
			cin>>a>>b;
			if(b>mp[a].e){
				mp[a]={b,i,1};
			}
			else if(b==mp[a].e) mp[a].cnt++;
		}
	}
	for(auto x:mp){
		int pos=x.second.pos,cnt=x.second.cnt;
		if(cnt<=1) flag[pos]=1; //某个质因数若存在唯一最大次幂，标记这个最大次幂对应是第几个数贡献的
	}
	int ans=0;
	bool pflag=false;
	rep(i,1,n){
		if(flag[i]) ans++;
		else pflag=1; //存在删除其中一个数但不改变序列原本的最小公倍数的情况
	}
	cout<<ans+pflag;
}
```

---

## 作者：xmy201315 (赞：0)

对于本题的数据范围，大家可能难以下手。

我们可以向一件事，在将这 $N$ 个数的最小公倍数分解质因数后，每个数分解质因数里面的素因子都会出现。那它的次数是这 $N$ 个数里面相应的素因子的次数的最大值。

我们把一个数变为 $1$ 对于最小公倍数的影响，如果他这个质因数 $p_{i,m_i}^{e_i,m_i}$ 他在这 $N$ 个数的分解质因数中出现或某个质因数跟它底数相同，次数比它大或等于，那么把它删去没有任何影响。否则把它变成 $1$ 最小公倍数一定会改变。

我们要记每个相同底数次方的最大值和次大值。但是数字太大了，所以我们要用 **map** 来记可以方便一些。

那为什么要记呢？因为找到相同底数次方的最大值后，把它变成 $1$， $\operatorname{LCM}$ 的取值就会多一种。

时间复杂度其实是 $\mathcal O(\sum m_i \log \sum m_i)$。用 **map** 更新最大值和次大值的时间复杂度是 $\mathcal O( \log \sum m_i)$。所以上面的时间复杂度要乘个 $ \log \sum m_i$。如果你不想乘 $ \log \sum m_i$，你可以用哈希或其他算法，这里就不用哈希了。

[AC记录](https://www.luogu.com.cn/paste/zc1qp5si)
```cpp
#include <bits/stdc++.h>
using namespace std;
struct Node{
	int p,v;
	Node(int ps,int vs){
		p=ps,v=vs;
	}
};
int n;
vector<Node> a[200001];
map<int,pair<int,int>> c;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int m;
		scanf("%d",&m);
		for(int j=1;j<=m;j++){
			int x,y;
			scanf("%d%d",&x,&y);
			a[i].push_back(Node(x,y));
			if(y>c[x].first)c[x].second=c[x].first,c[x].first=y;
			else if(y>c[x].second)c[x].second=y;
		}
	}
	int ans=0;bool ok=false;
	for(int i=1;i<=n;i++){
		bool z=false;
		for(auto j:a[i])
			if(j.v==c[j.p].first&&j.v!=c[j.p].second){
				++ans,z=true;
				break;
			}
		if(!z)ok=true;
	}
	if(ok)++ans;
	printf("%d\n",ans);
}
```

---

## 作者：Elairin176 (赞：0)

[传送门](https://www.luogu.com.cn/problem/AT_abc259_e)    
来一发哈希题解。   
## 题意
给定 $n$ 个数（以质因数分解的形式给出），每次将其中一项的值改成 $1$，求其最小公倍数。对 $i\in[1,n]$ 分别执行操作（相互独立），求不同的最小公倍数数量。   
## 解法
注意到最小公倍数实际上是在求相同底数下指数的最大值，故我们可以对最小公倍数分解质因数后的指数进行哈希，我这里采用将底数和指数相乘再求和的形式。   
故我们可以对相同的底数维护其指数的最大值和次大值，对某一位修改为 $1$ 时将相应取到最大值的底数修改为次大值即可。     
最后只需要求出有多少不同的哈希值，用 set 实现即可。    
时间复杂度 $O(n\log n+\sum m_i)$。     
Code：  

```cpp
//luogu paste jo5j6ogx
cst ll p=1e11+9;
cst int N=2e5;
int n;
umap<int,int>mp[N+10],mx,mx2;
ll now;
set<ll>st;
int main(void){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	n=read<int>();
	for(int i=1;i<=n;i++){
		int m=read<int>();
		while(m--){
			int x=read<int>(),k=read<int>();
			mp[i][x]=k;
			if(k>mx[x]){
				mx2[x]=mx[x];
				mx[x]=k;
			}else mx2[x]=_max<int>(mx2[x],k);
		}
	}
	for(auto [x,y]:mx) now=madd(now,1ll*x*y%p,p);
	for(int i=1;i<=n;i++){
		ll t=now;
		for(auto [x,y]:mp[i]){
			if(y==mx[x]){
				t=msub(t,1ll*x*y%p,p);
				t=madd(t,1ll*mx2[x]*x%p,p);
			}
		}
		st.insert(t);
	}
	write((int)st.size());
	ret 0;
}
```

---

