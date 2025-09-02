# [ARC162B] Insertion Sort 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc162/tasks/arc162_b

$ (1,2,\ldots,N) $ の順列 $ P=(P_1,P_2,\ldots,P_N) $ が与えられます。

$ P $ に対し以下の操作を $ 2\times\ 10^3 $ 回以下行うことで $ P $ を昇順に並び替えられるか判定し、可能な場合は実際に操作手順を一つ示してください。

- $ 1\leq\ i\ \leq\ N-1,0\ \leq\ j\ \leq\ N-2 $ を満たす整数 $ i,j $ を選ぶ。$ Q\ =\ (Q_1,\ Q_2,\ldots,Q_{N-2}) $ を $ P $ から $ (P_i,P_{i+1}) $ を抜き出して得られる列としたとき、$ P $ を $ (Q_1,\ldots,Q_j,\ P_i,\ P_{i+1},\ Q_{j+1},\ldots,Q_{N-2}) $ で置き換える。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 10^3 $
- $ P $ は $ (1,2,\ldots,N) $ の順列
- 入力される数値は全て整数
 
### Sample Explanation 1

$ i=3,j=1 $ として操作を行います。 $ Q=(P_1,P_2,P_5)=(1,4,5) $ になるので、$ P=(Q_1,P_3,P_4,Q_2,Q_3)\ =\ (1,2,3,4,5) $ となります。 よって $ 1 $ 回の操作で $ P $ を昇順に並び替えられます。

### Sample Explanation 2

$ 2\times\ 10^3 $ 回以下の操作では $ P $ を昇順に並び替えられないことが証明できます。

### Sample Explanation 3

操作回数を最小化する必要はありません。

## 样例 #1

### 输入

```
5
1 4 2 3 5```

### 输出

```
Yes
1
3 1```

## 样例 #2

### 输入

```
2
2 1```

### 输出

```
No```

## 样例 #3

### 输入

```
4
3 4 1 2```

### 输出

```
Yes
3
3 0
1 2
3 0```

# 题解

## 作者：FyFive (赞：5)

#### 题意

每次取出相邻的两个数，插到剩余序列的任意位置。

#### 思路

ARC 的 B 题出这种水平的构造有失水准啊。。。

不难想到给出的高达 $2N$ 次操作的含义即为每次构造最多包含两次操作。

同时，从左往右依次排序在时间上显然是没有任何问题的，因为 $N$ 很小。

那么，考虑选择排序。当要排第 $j$ 位时，可以直接把 $i$ 和 $i+1$ 位上的数移到 $j$ 处，其中 $a[i]=j$。

与此同时，如果 $a[N]=j$，这代表不能直接选择 $i=N$，那么就需要让它可以选。不难想到可以把最后两个数往前移一位，这样就可以选了。

考虑什么情况下无解。当排序一直到 $N-2$ 全部排好之后，如果最后两个数反了，不难想到这种情况下是不能排序的。那么判无解直接顺着做就好了。

平方复杂度选择，每次暴力修改序列，整体复杂度依然是平方，一点压力都没有，想怎么写怎么写。

#### 核心代码
```cpp
for(int i=1;i<=n-2;++i)
{
    int wz=1; for(int j=1;j<=n;++j) if(p[j]==i) wz=j; 
    if(wz==i) continue;
    if(wz==n)
    {
        ai[++ans]=n-1; aj[ans]=n-3; change(ai[ans],aj[ans]);
        ai[++ans]=n-1; aj[ans]=i-1; change(ai[ans],aj[ans]);
    }
    else {ai[++ans]=wz,aj[ans]=i-1; change(ai[ans],aj[ans]);}
}
if(p[n-1]>p[n]) ans=-1;
```

---

## 作者：KυρωVixen (赞：3)

## 题意：

给你一个长为 $N$ 的序列，其正好是 $1\sim N$ 的一个排列，每次你可以选一个长度为 $2$ 的子段插入到任意位置，求是否能将其从小到大排序，并求需操作次数、具体方案。

操作次数上限 $2\times10^3$，$N\leq 10^3$。

## 解法：

这个题显然可以借用插入排序的思路：从 $1$ 开始考虑，逐渐扩大序列已经升序排序过的部分，每次把找到的数和它后面的那个数作为一个整体，挪到有序部分的最后面，然后继续考虑下一个数，以此类推，直到 $N-2$。如果结束的时候 $N-1$ 在 $N$ 前面，那么有解，输出方案，反之无解。

------

**等等！**

这个算法有一个显然的问题：如果正在找的数在结尾，那么它后面岂不是没有数，无法继续这个算法了吗！

不过看到这个操作次数，我们就可以有一个简单的补救方式：将它与它前面的数往前挪到第 $N-2$ 个数后面，然后重复上面的过程即可。可以看到：最坏的情况下肯定不止 $10^3$ 次操作，会有两倍左右，所以操作次数上限乘上了 $2$。

然后这道题就很干净利落的做完了，时间复杂度 $O(N^2)$，而且比官方题解做法更好想。

## AC Code：

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define Puts(x) cout<<x<<'\n'
using namespace std;
int n; vector<int>v;
vector<pair<int,int>>sol;
signed main(){
	cin>>n;
	rep(i,1,n){
		int x; cin>>x; v.push_back(x);
	}
	auto beg=v.begin();
	if(n==2){
		if(v[1]==1) puts("No");
		else puts("Yes\n0");
		return 0;
	}
	rep(i,1,n-1){
		bool flag=0;
		TE:
		rep(j,0,n-2){
			if(v[j]==i){
				int t1=v[j],t2=v[j+1];
				v.erase(beg+j); v.erase(beg+j);
				v.insert(beg+i-1,t1);
				v.insert(beg+i,t2);
				sol.push_back(make_pair(j+1,i-1));
				flag=1; break;
			}
		}
		if(!flag){
			int t1=v[n-2],t2=v[n-1];
			v.erase(beg+n-2); v.erase(beg+n-2);
			v.insert(beg+n-3,t1);
			v.insert(beg+n-2,t2);
			sol.push_back(make_pair(n-1,n-3));
			goto TE;
		}
	}
	if(v[n-1]!=n){
		puts("No"); return 0;
	}
	puts("Yes");
	Puts(sol.size());
	rep(i,0,sol.size()-1)
		cout<<sol[i].first<<" "<<sol[i].second<<endl;
}
```

代码只要 1KB，而且思路也比较板，赛时因为有个地方忘了记录方案没有 AC，但是赛后十分钟就做出来了。

评分参考：黄左右，比一般 ARC B 简单很多。


---

## 作者：CrTsIr400 (赞：1)

[9. [ARC162B] Insertion Sort 2](https://www.luogu.com.cn/problem/AT_arc162_b)

观察这是给你一个长度为 $n\le 1000$ 的**排列**，然后构造一种方案，每次拿出两个数绑在一起做 `insertion sort`，求构造方案。

手玩一下样例，一个很自然的想法就是直接挑出最大的数丢到最后面。$n\le 1000$，直接暴力一点问题没有。然后直接交上去挂了，怎么回事呢？

最好手玩多几组，发现问题所在。比如 `3 1 2`。

最大的数在第一个位置上怎么办呢？此时似乎没有解。那么我们还有许多未选的数啊，直接把第二个第三个数左移一位，把最大的数挤到第三个位置上不就行了。

于是这个题就结束了。思维也不难，多想想可能无解的时候是否能够有解。

```cpp
#include<bits/stdc++.h>
#define fo(i,a,b) for(I i(a),_ed(b);i<=_ed;++i)
using namespace std;using I=int;using LL=long long;using V=void;
const I N=1003;
I n,a[N];vector<pair<I,I>>v;
I main(){ios::sync_with_stdio(0);cin.tie(0);
	cin>>n;
	fo(i,1,n)cin>>a[i]; 
	for(I i=n;i>=2;--i){
		I p=find(a+1,a+i+1,i)-a;
		assert(p);
		if(p==1){
			if(i<3)return puts("No"),0;
			v.push_back({2,1-1});swap(a[1],a[2]);swap(a[2],a[3]);
			p=3;}
		if(p==i)continue;
		rotate(a+p-1,a+p+1,a+i+1);
		v.push_back({p-1,i-2});
	}
	if(a[1]>a[2])return puts("No"),0;
	printf("Yes\n%d\n",v.size());
	for(auto i:v)printf("%d %d\n",i.first,i.second);
	return 0;}
```



---

