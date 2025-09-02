# k-DMC

## 题目描述

[problemUrl]: https://atcoder.jp/contests/dwacon5th-prelims/tasks/dwacon5th_prelims_c

ドワンゴのコンテンツ配信基盤システム Dwango Media Cluster は、略して DMC と呼ばれています。  
 この名前をかっこ良いと感じたニワンゴくんは、文字列の DMC らしさを数値として定義することにしました。  
 具体的には、長さ $ N $ のある文字列 $ S $ と3以上の整数 $ k $ が与えられた時、以下を満たす整数の3つ組 $ (a,b,c) $ の個数を $ S $ の $ k $-DMC 数と呼ぶことにします。

- $ 0\ \leq\ a $
- $ S[a] $ = `D`
- $ S[b] $ = `M`
- $ S[c] $ = `C`
- $ c-a $

ここで、$ S[a] $ は $ S $ の $ a $ 番目の文字を表します。先頭の文字は $ 0 $ 文字目として扱います (つまり、$ 0\ \leq\ a\ \leq\ N\ -\ 1 $ です)。

ある文字列 $ S $ と $ Q $ 個の整数 $ k_0,\ k_1,\ ...,\ k_{Q-1} $ に対して、$ k_i $-DMC 数をそれぞれ計算してください。

## 说明/提示

### 制約

- $ 3\ \leq\ N\ \leq\ 10^6 $
- $ S $ は`A` - `Z` からなる文字列
- $ 1\ \leq\ Q\ \leq\ 75 $
- $ 3\ \leq\ k_i\ \leq\ N $
- 入力として与えられる数値はすべて整数である

### Sample Explanation 1

$ (a,b,c)\ =\ (0,\ 6,\ 11) $ が条件を満たします。 Dwango Media Cluster は、ニワンゴくんの定義では意外と DMC らしくないようです。

### Sample Explanation 2

$ 6\times\ 5\times\ 7 $ 個の組み合わせがありえます。

### Sample Explanation 3

$ c-a\ 以外の条件は\ (a,\ b,\ c)\ =\ (0,\ 23,\ 36),\ (8,\ 23,\ 36) $ が満たします。 ちなみに、DWANGO は「Dial-up Wide Area Network Gaming Operation」の頭文字です。

## 样例 #1

### 输入

```
18
DWANGOMEDIACLUSTER
1
18```

### 输出

```
1```

## 样例 #2

### 输入

```
18
DDDDDDMMMMMCCCCCCC
1
18```

### 输出

```
210```

## 样例 #3

### 输入

```
54
DIALUPWIDEAREANETWORKGAMINGOPERATIONCORPORATIONLIMITED
3
20 30 40```

### 输出

```
0
1
2```

## 样例 #4

### 输入

```
30
DMCDMCDMCDMCDMCDMCDMCDMCDMCDMC
4
5 10 15 20```

### 输出

```
10
52
110
140```

# 题解

## 作者：CQ_Bob (赞：1)

## 分析

先考虑 $k=n$ 的情况。

对于 $s_j=M$ 的时候，其能够匹配的 $s_i=D$ 的数量很显然是 $i \le j-1$ 的时候的数量，求前缀和就能得到。而对于 $s_j=C$ 的时候，能够完整匹配的就是 $i \le j-1$ 的时候所有 $s_i=M$ 能够匹配的数量之和，再套个前缀和就行了。复杂度是 $O(n)$ 的。

考虑 $3 \le k \le n$ 的情况。

和上面的差不多，对于 $s_j=C$ 的时候，它能够得到贡献的 $M,D$ 都是在 $[j-k+1,j]$ 的。处理这个，只需要在 $j-k$ 没有越界的时候减去 $s_{j-k}$ 的贡献。如果 $s_{j-k}=M$，因为 $s_{j-k}$ 之前所有的 $D$ 对 $j$ 的贡献都减完了，所以将 $M$ 出现数量的和 $-1$（这个后面会用到）。如果 $s_{j-k}=D$，其贡献是 $[j-k+1,j]$ 中 $M$ 的数量，这个已经统计出来了，直接剪掉即可。如果 $s_{j-k}=C$，则不理会，因为它本身不会产生贡献。至于 $s_j=M,D$ 的情况，跟 $k=n$ 的时候差不多，只需要注意 $M$ 的数量。

单次询问的答案就是所有 $s_j=C$ 的时候得到贡献之和。复杂度 $O(qn)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline
#define PII pair<int,int>
#define x first
#define y second 

const int N=1e6+10;
int n,q,k;
string s;

il void solve(){
	cin>>n>>s>>q;
	while(q--){
		cin>>k;
		int ans=0,sum_d=0,sum_m=0,sum=0;
		for(re int i=0;i<n;++i){
			if(i-k>=0){
				if(s[i-k]=='D') sum-=sum_m,--sumd;
				if(s[i-k]=='M') --sum_m;
			}
			if(s[i]=='D') ++sum_d;
			if(s[i]=='M') sum+=sum_d,++sum_m;
			if(s[i]=='C') ans+=sum;
		}
		cout<<ans<<"\n";
	}
	return ;
}

signed main(){
	solve();
	return 0;
}

```


---

## 作者：yuheng_wang080904 (赞：0)

## 题目分析

~~这道题好像没人做嘛！~~

这道题一开始读时很难想到办法，$N$ 的范围是 $1000000$，$Q$ 的范围是 $75$，乘起来是 $75000000$，因此算法只能是 $O(n)$。

对于每次查询，字符串是必须要遍历一遍的，这一遍遍历，是必须要完成 $(D,M,C)$ 的配对的。

$k$ 的限制导致我们循环遍历时，像滑动窗口一样，会有 $D$ 离开这个窗口，而因此导致数量减少。

既然这样，那么这次遍历，我们可以找到所有的 $D$，由于 $k$ 的限制，而要找到 $M$，只能再次遍历，为了省掉这次遍历，我们很快就能想到使用前缀和！

至此，对于每个循环 $i$ 值时的 $(D,M)$ 配对的个数就可以知道了， 每次 $i$ 加一时要注意离开窗口的 $D$ 的判断！这时就要用到预处理的前缀和。

然后每当窗口内进入 $C$ 时，$ans$ 就要增加窗口内的 $(D,M)$ 配对个数。

这样，这道难题就能被我们成功解决了！

## 代码

接下来贴代码，希望大家能掌握思路，不要抄袭！

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,k[100];
int m[1000005];//m数组做前缀和用
string s;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>s>>q;
    for(int i=0;i<q;i++)cin>>k[i];
    for(int i=1;i<=n;i++)m[i]=m[i-1]+(s[i-1]=='M');//预处理做'M'数量的前缀和
    for(int i=0;i<q;i++){
	long long sumD=0,sumpair=0,ans=0;
        //sumD是D的数量
        //sumpair是窗口内满足条件的(D,M)的组数
	for(int j=0;j<n;j++){
	    if(j-k[i]>=0&&s[j-k[i]]=='D'){//这里注意要判断离开窗口的D
		sumD--;//离开一个D，于是sumD的值减去1
		sumpair-=(m[j]-m[j-k[i]]);//同时sumpair的值也要减去由离开的D产生的(D,M)组合
	    }
	    if(s[j]=='D')sumD++;//出现D时，sumD加1
	    if(s[j]=='M')sumpair+=sumD;//出现M时，(D,M)组合要增加sumD的值，因为这个M可以和窗口内的所有D产生组合
 	    if(s[j]=='C')ans+=sumpair;//出现C时，结果ans要增加sumpair的值，因为这个C可以和窗口内的所有(D,M)产生组合
	}
	cout<<ans<<"\n";
    }
    return 0;
}

```

---

