# [ARC017C] 無駄なものが嫌いな人

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc017/tasks/arc017_3

私は無駄なものが嫌いなので、無駄なことを言わずに言いたいことだけ言おう。  
 世の中にはナップサック問題というものがあり、決まった大きさのナップサックにできるだけ価値が高くなるよう品物を詰めることを考えるらしいが、そんなことを考えても無駄である。  
 価値がいくら高くなったところで、ナップサックに無駄なスペースができてしまうのは許せない。私は無駄なものが嫌いなのだ。  
 さて、今ここに大きさ $ X $ のナップサックと $ N $ 個の品物がある。  
 $ i $ 番目の品物の大きさは $ w_i $ である。品物の価値については、考えても無駄なので無視する。  
 ナップサックに無駄なスペースができないよう品物を詰める方法は何通りあるだろうか？  
 つまり、$ N $ 個の品物から、大きさの総和が無駄なくぴったり $ X $ となる選び方が何通りあるか、ということだ。  
 私ははじめ手でこの問題を解こうとしたが、無駄が多い手段であると分かったので君に頼むことにした。  
 無駄な計算時間のないプログラムを書いてこの問題を解き、私の無駄な時間を省くのを手伝ってもらいたい。

入力は以下の形式で標準入力から与えられる。

> $ N $ $ X $ $ w_1 $ $ w_2 $ : $ w_N $

- $ 1 $ 行目には、品物の個数を表す整数 $ N\ (1\ \leq\ N\ \leq\ 32) $ とナップサックの大きさを表す整数 $ X\ (1\ \leq\ X\ \leq\ 10^9) $ が半角空白区切りで与えられる。
- $ 2 $ 行目から $ N $ 行では、品物の大きさが与えられる。このうち $ i\ (1\ \leq\ i\ \leq\ N) $ 行目には、$ i $ 番目の品物の大きさを表す整数 $ w_i\ (1\ \leq\ w_i\ \leq\ 5\ \times\ 10^7) $ が書かれている。
 
 $ N $ 個の品物のうちいくつかを選び、その大きさの和がぴったり $ X $ になるような方法が何通りあるかを表す整数を 1 行に出力せよ。 ```
<pre class="prettyprint linenums">
5 5
1
1
2
3
4
```

 ```
<pre class="prettyprint linenums">
4
```

 無駄のない品物の選び方は次の $ 4 $ 通りである。 - 品物 $ 1 $, 品物 $ 2 $, 品物 $ 4 $ を選ぶ: $ 1\ +\ 1\ +\ 3\ =\ 5 $
- 品物 $ 1 $, 品物 $ 5 $ を選ぶ: $ 1\ +\ 4\ =\ 5 $
- 品物 $ 2 $, 品物 $ 5 $ を選ぶ: $ 1\ +\ 4\ =\ 5 $
- 品物 $ 3 $, 品物 $ 4 $ を選ぶ: $ 2\ +\ 3\ =\ 5 $
 
 品物 $ 1 $ と品物 $ 2 $ は同じ重さの品物であるが異なる品物として扱うことに注意すること。 ```
<pre class="prettyprint linenums">
8 21
10
4
2
30
22
20
8
14
```

 ```
<pre class="prettyprint linenums">
0
```

 どのように品物を選んでも、その大きさの和がぴったり $ 21 $ になるようにはできない。 ```
<pre class="prettyprint linenums">
20 100000000
35576749
38866484
6624951
39706038
11133516
25490903
14701702
17888322
14423251
32111678
24509097
43375049
35298298
21158709
30489274
37977301
19510726
28841291
10293962
12022699
```

 ```
<pre class="prettyprint linenums">
45
```

 ```
<pre class="prettyprint linenums">
16 8
1
1
1
1
1
1
1
1
1
1
1
1
1
1
1
1
```

 ```
<pre class="prettyprint linenums">
12870
```

# 题解

## 作者：Dr_Gilbert (赞：2)

# AT809 無駄なものが嫌いな人

【题目大意】

一个容量为 $X$ 的背包，有 $N$ 个物品，每个物品有其体积 $w_i$，求恰好装满背包的方案数。

- $N\le32$，$w_i\le5\times10^7$，$X\le10^9$。

看到 $X\le10^9$ 的数据范围，发现本题一定不是普通的 DP。但注意到 $N$ 的数据范围为 $N\le32$，假如你学过双向搜索，应该可以想到用双向搜索解决这个问题。

双向搜索一般用于数据范围较小的题目，并且一般要求的答案是在“全部”的前提下计算的，同时最终的答案可以通过两部分答案进行累加计算。例如本题要求恰好把背包装满，且装满的方案可以通过一些没有恰好装满的方案相加得到，所以本题考虑双向搜索。

双向搜索一般将搜索折半，先搜前一半，并且将各状态存到一个 `map` 里。接下来搜后一半，后一半搜完后用“全部”减去状态，尝试将前一半和后一半进行拼接。具体可以参考以下代码实现：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,tot,val[40],ans;
unordered_map<int,int> mp;
void dfs1(int x, int v){
	if (x>n/2){
		mp[v]++;return;
	}
	dfs1(x+1,v+val[x]);
	dfs1(x+1,v);return;
}
void dfs2(int x, int v){
	if (x>n){
		int tmp=tot-v;
		ans+=mp[tmp];return;
	}
	dfs2(x+1,v+val[x]);
	dfs2(x+1,v);return;
}
signed main(){
	cin>>n>>tot;
	for (int i=1;i<=n;i++) cin>>val[i];
	dfs1(1,0);dfs2(n/2+1,0);
	cout<<ans<<endl;return 0;
}
```

同时，双向搜索也有其他几道比较简单的例题，如[[CEOI2015 Day2]世界冰球锦标赛](https://www.luogu.com.cn/problem/P4799)，[[USACO09NOV]Lights G](https://www.luogu.com.cn/problem/P2962)。

---

## 作者：MY（一名蒟蒻） (赞：2)

这里介绍两种折半搜索写法。

首先这题直接爆搜一定会炸。~~如果您没有搜炸大概率也不会看题解。~~

那么考虑折半搜索~~五五开~~。

## 思路一 map
好像已经有大佬讲过这种做法了。

将搜索区间五五开之后处理出一半结果，另一半搜索出结果`v`时直接将上一半`X-v`的数量统计进答案。
### Code
```cpp
int n,x,w[50];
int ans;
map <int,int> m;

void dfs(int sum,int l,int r,bool f)
{
	if(sum > x) return ;
	if(l > r)
	{
		if(f) m[sum]++;
		else ans+=m[x-sum];
		return ;
	}
	dfs(sum+w[l],l+1,r,f);
	dfs(sum,l+1,r,f);
	return ;
}

int main()
{
//	freopen("work.in","r",stdin);freopen("work.out","w",stdout);
	scanf("%d%d",&n,&x);
	for(int i=1;i<=n;i++)
		scanf("%d",&w[i]);
	int mid=(1+n) >> 1;
	dfs(0,1,mid,true);
	dfs(0,mid+1,n,false);
	printf("%d\n",ans);
//	fclose(stdin);fclose(stdout);
	return 0;
}
```
时间447ms，空间9.43MB。
## 思路二 vector
`vector`的想法是处理一半结果存进去并二分。

但是题目要求刚好装满

所以要判等

注意**能判断**的条件是有一个`a[i] >= x-b[i]` 

然后用`upper_bound`出来的下标减掉`lower_bound`的下标计入答案

`upper_bound`和`lower_bound`找不到答案没有影响，读者可以思考一下为什么。

常数小空间少，性能完胜map，但是代码复杂度高一些，不过问题不大。

时间280ms，空间3.86MB
### Code
```cpp
int n,x,w[50],ans;
vector <int> a,b;

void dfs(int sum,int l,int r,vector <int> &v)
{
	if(sum > x) return ;
	if(l > r) {v.push_back(sum); return ;}
	dfs(sum+w[l],l+1,r,v);
	dfs(sum,l+1,r,v);
	return ;
}

int main()
{
//	freopen("work.in","r",stdin);freopen("work.out","w",stdout);
	scanf("%d%d",&n,&x);
	for(int i=1;i<=n;i++)
		scanf("%d",&w[i]);
	int mid=(1+n) >> 1;
	dfs(0,1,mid,a); dfs(0,mid+1,n,b);
	sort(a.begin(),a.end());
	for(int i=0,t;i<(int)b.size();i++)
	{
		t=lower_bound(a.begin(),a.end(),x-b[i])-a.begin();
		if(t < (int)a.size() && a[t] == x-b[i])
			ans+=upper_bound(a.begin(),a.end(),x-b[i])-a.begin()-t;
	}
	printf("%d\n",ans);
//	fclose(stdin);fclose(stdout);
	return 0;
}
```
**AT题库记得行末输出换行。**
## Thank you for your reading!
点个赞再走嘛QwQ

---

## 作者：shenmadongdong (赞：0)

折半搜索裸题。

暴力枚举前 $\left\lfloor\dfrac{n}{2}\right\rfloor$ 个物品所占体积种类，再暴力枚举剩下物品所占体积求出答案

具体的，将前半段暴枚出的体积存到 map 里，然后如果后半段暴枚出 $m$ 体积，把答案加上 map 里 $X-m$ 的值即可

代码大概是这样的：
```cpp
map<int,int> mp;
int w[33],n,x,ans;
int main()
{
	cin>>n>>x;
	for(int i=1;i<=n;i++) w[i]=read();
	for(int j=0;j<(1<<n/2);j++)
    {
		int s=0;
		for(int i=1;i<=n/2;i++) if (j>>i-1&1)s+=w[i];
		mp[s]++;
	}
	for(int j=0;j<(1<<n-n/2);j++)
    {
		int s=0;
		for(int i=n/2+1;i<=n;i++) if (j>>i-n/2-1&1) s+=w[i];
		ans+=mp[x-s];
	}
	cout<<ans<<'\n';
	return 0;
}
```

---

