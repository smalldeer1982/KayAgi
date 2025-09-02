# [ARC182A] Chmax Rush!

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc182/tasks/arc182_a

長さ $ N $ の整数列 $ S $ があります。はじめ、$ S $ の要素はすべて $ 0 $ です。

また、長さ $ Q $ の整数列 $ P=(P_1,P_2,\dots,P_Q) $ と $ V=(V_1,V_2,\dots,V_Q) $ が与えられます。

すぬけ君は、数列 $ S $ に $ Q $ 回の操作を順に行いたいです。$ i $ 回目の操作は以下です。

- 以下のどちらかの操作を行う。
  - $ S_1,S_2,\dots,S_{P_i} $ をすべて $ V_i $ に置き換える。ただし、この操作の前に $ S_1,S_2,\dots,S_{P_i} $ の中に $ V_i $ より真に大きい要素がある場合、すぬけ君は泣き出す。
  - $ S_{P_i},S_{P_i+1},\dots,S_N $ をすべて $ V_i $ に置き換える。ただし、この操作の前に $ S_{P_i},S_{P_i+1},\dots,S_N $ の中に $ V_i $ より真に大きい要素がある場合、すぬけ君は泣き出す。

すぬけ君が泣き出さないように $ Q $ 回の操作をすべて行うことのできるような操作列の個数を $ 998244353 $ で割った余りを求めてください。

ただし、$ 2 $ つの操作列が異なるとは、ある $ 1\leq\ i\leq\ Q $ が存在して、$ i $ 番目の操作でどちらの操作を選択したかが異なることを指します。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 5000 $
- $ 1\ \leq\ Q\ \leq\ 5000 $
- $ 1\ \leq\ P_i\ \leq\ N $
- $ 1\ \leq\ V_i\ \leq\ 10^9 $
- 入力はすべて整数

### Sample Explanation 1

以下のようにするとすぬけ君が泣き出さないように $ 3 $ 回の操作を行うことができます。 - $ S_1 $ を $ 8 $ に置き換える。 - $ S_8 $ を $ 1 $ に置き換える。 - $ S_2,S_3,\dots,S_8 $ を $ 1 $ に置き換える。 これ以外に条件を満たす操作列はないので、$ 1 $ が答えです。例えば、$ 1 $ 回目の操作で $ S_1,S_2,\dots,S_8 $ を $ 8 $ に置き換えると、$ 2 $ 回目の操作でどちらを選んでもすぬけ君が泣き出してしまいます。

### Sample Explanation 2

$ 2 $ 回目までの操作をどのように行っても $ 3 $ 回目の操作ですぬけ君が泣き出してしまいます。

### Sample Explanation 3

$ 998244353 $ で割った余りを求めることを忘れないでください。

## 样例 #1

### 输入

```
8 3
1 8
8 1
2 1```

### 输出

```
1```

## 样例 #2

### 输入

```
8 3
8 1
1 8
1 2```

### 输出

```
0```

## 样例 #3

### 输入

```
241 82
190 3207371
229 3639088
61 4428925
84 17258698
34 42692503
207 59753183
180 67198566
78 99285033
60 102449991
234 122146510
111 126959145
141 152331579
78 159855439
11 169658471
22 189991287
37 204602946
73 209329065
72 215363269
152 236450854
175 237822921
22 261431608
144 252550201
54 268889550
238 276997357
69 313065279
226 330144323
6 335788783
126 345410019
220 348318997
166 365778763
142 382251905
200 406191336
234 392702679
83 409660987
183 410908761
142 445707116
205 470279207
230 486436406
156 494269002
113 495687706
200 500005738
162 505246499
201 548652987
86 449551554
62 459527873
32 574001635
230 601073337
175 610244315
174 613857555
181 637452273
158 637866397
148 648101378
172 646898076
144 682578257
239 703460335
192 713255331
28 727075136
196 730768166
111 751850547
90 762445737
204 762552166
72 773170159
240 803415865
32 798873367
195 814999380
72 842641864
125 851815348
116 858041919
200 869948671
195 873324903
5 877767414
105 877710280
150 877719360
9 884707717
230 880263190
88 967344715
49 977643789
167 979463984
70 981400941
114 991068035
94 991951735
141 995762200```

### 输出

```
682155965```

# 题解

## 作者：Double_Light (赞：8)

设 $f_{i,0}$ 代表第 $i$ 次询问是否能修改左边，$f_{i,1}$ 代表第 $i$ 次询问是否能修改右边。初始时假设 $f_{i,0}=f_{i,1}=1$。

对于 $V_i\leq V_j$ 且 $i<j$，显然第 $i$ 次询问不会对第 $j$ 次询问产生影响。所以产生影响的只能是逆序对。

对于一对逆序对 $i,j$，我们分类讨论：

- $P_i=P_j$：显然第 $j$ 次询问向左和向右都不能修改。Snuke 不管怎样都会哭泣，故答案为 $0$。
- $P_i<P_j$：为使两次修改区间没有交集，第 $i$ 次询问只能修改左边，第 $j$ 次询问只能修改右边。$f_{i,1}=0,f_{j,0}=0$。
- $P_i>P_j$：为使两次修改区间没有交集，第 $i$ 次询问只能修改右边，第 $j$ 次询问只能修改左边。$f_{i,0}=0,f_{j,1}=0$。

显然，随着修改操作的进行，$S_i$ 的值只会越来越大，**不会**出现形如 $i<k<j$ 且 $V_k<V_j<V_i$ 的第 $k$ 次询问，使得原本不能被 $V_j$ 修改的 $S_{1\sim P_j}$ 或 $S_{P_j\sim n}$ 在第 $k$ 次询问后可以被修改。

最后答案就是 $\prod_{i=1}^q(f_{i,0}+f_{i,1})$。
```cpp
#include<iostream>
using namespace std;
int n,q;
int f[5005][2];
int a[5005],b[5005];
int ans=1;
const int mod=998244353;
int main(){
	cin>>n>>q;
	for(int i=1;i<=q;i++)cin>>a[i]>>b[i];
	for(int i=1;i<=q;i++){
		f[i][0]=f[i][1]=1;
	}
	for(int i=1;i<=q;i++){
		for(int j=i+1;j<=q;j++){
			if(b[i]>b[j]){
				if(a[j]>a[i])f[i][1]=0,f[j][0]=0;
				if(a[j]<a[i])f[i][0]=0,f[j][1]=0;
				if(a[i]==a[j])f[j][0]=f[j][1]=0;
			}
		}
	}
	for(int i=1;i<=q;i++){
		ans*=(f[i][0]+f[i][1]);
		ans%=mod;
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：zeroflows (赞：5)

# [题目传送门](https://www.luogu.com.cn/problem/AT_arc182_a)

### 思路
我们只需要枚举每一个 $v_i$，对于 $i$ 后面的 $v_j$ 如果 $v_i > v_j$ 进行以下讨论。

* $p_i = p_j$   
* $p_i < p_j$   
* $p_i > p_j$

当 $p_i = p_j$ 的时候。因为不论选哪个方案 $p_i$ 这个位置都要替换，所以无解，直接输出。    
当 $p_i < p_j$ 的时候。我们可以确定对于 $i$ 只能选方案一，对于 $j$ 只能选方案二，这样才能保证两段没有交集。    
而当 $p_i > p_j$ 的时候。我们可以确定对于 $i$ 只能选方案二，对于 $j$ 只能选方案一，这样才能保证两段没有交集。    

对于每一个 $i$ 最初都有两种选择，而在讨论的时候，每排除一种情况 $i$ 与 $j$ 的方案数都要减一，最后答案就是每一个 $i$ 的方案数的乘积。


---


 ### 代码
 ```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int p[1000000],v[1000000];
int hh[6000][5];
int main()
{
    ios::sync_with_stdio(false);
	cin.tie(),cout.tie();
	cin>>n>>m;
	for(int i=1;i<=m;i++)
		cin>>p[i]>>v[i];
	for(int i=1;i<=m;i++)
		hh[i][1]=hh[i][2]=1;
	for(int i=1;i<=m;i++)
	{
		for(int j=i+1;j<=m;j++)
		{
			if(v[i]>v[j])
			{
				if(p[j]>p[i])
				{
					hh[i][2]=0;
					hh[j][1]=0;
				}
				if(p[j]<p[i])
				{
					hh[i][1]=0;
					hh[j][2]=0;
				}
				if(p[j]==p[i])
				{
					cout<<0;
					return 0;
				}
			}
		}
	}
	int ans=1;
	for(int i=1;i<=m;i++)
	{
		ans*=(hh[i][1]+hh[i][2]);
		ans%=998244353;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：xyin (赞：3)

惨兮兮，这次连第一道题都没能切，我太菜了。。。以后还是要多打 AtCoder 和 CF 的比赛。

## 题意简述

一个长度为 $n$ （~~$n$ 好像没什么用~~）的整数序列 $S$，所有元素的初始值都为 $0$。

你总共需要依次完成 $Q$ 次操作，对于每个操作 $P_i$，$V_i$，你要将区间 $[S_1,S_{P_i}]$ 或者区间 $[S_{P_i},S_n]$ 覆盖为 $V_i$。

要求每次选择的区间中的元素**严格大于** $V_i$，求有多少种合法的操作方案数能完成 $Q$ 个操作，答案对 $998244353$ 取模。

## 思路历程

通过观察数据范围，能大致得出最终解法的复杂度应该是 $O(n^2)$，$O(nq)$，$O(q^2)$ 中的一个。

我们顺着这个思路往下考虑，如果采用 $O(n^2)$ 只枚举位置，在执行到不同操作的时候，$i$ 位置的元素都不大相同，只枚举位置不是很方便，pass。

如果采用 $O(nq)$ 枚举位置和操作，只有一个操作作为判断依据，也不好判断，pass。

最终我们来尝试采用 $O(q^2)$ 枚举两个操作。

我们考虑什么时候某操作只能**被迫**选择一个**确定**的覆盖区间（$[S_1,S_{P_i}]$ $or$ $[S_{P_i},S_n]$ 中的一个）。

* 当 $i<j$，$V_i > V_j$ 时，此时的操作区间应该是确定的：

  1.    $P_i=P_j$，此时无论如何都不合法，直接输出 $0$。
 
  2.    $P_i>P_j$，此时 $P_i$ 只能选择它的右区间（$[S_{P_i},S_n]$），$P_j$ 只能选择它的左区间（$[S_1,S_{P_i}]$）。
 
  3.    同理 $P_i<P_j$ 也一样能确定，建议自己画图看看。
 
* 而当 $i<j$，$V_i \le V_j$ 时，若只考虑 $i$ 和 $j$ 操作，（只考虑这两个操作！！！），此时无论 $i$，$j$ 怎么放都是合法的，所以它是无法确定的。

综上，我们每次枚举操作 $i$，$j$，确定 $i$，$j$ 操作的覆盖区间，如果与之前确定的违背，则肯定不合法，直接输出 $0$。

在所有能确定的操作都确定完后，我们可能还会剩下一些没有确定的操作（~~写到这儿，我都差点给忘了这题到底是要求啥~~），此时根据这些没有确定的操作的**个数**（设为 $cnt$），我们就能求得答案了（因为每种操作都有两种选择可能，所以答案为 $2^{cnt}$）。

最后记得开 long long 和取模。

**代码实现**：

```cpp
//vis数组的含义：1->right 2->left 0->unknown 
signed main(){
	n=read();q=read();
	bool tag=1;
	for (int i=1;i<=q;i++)
	  p[i]=read(),v[i]=read();
	for (int i=1;i<=q;i++)
	  for (int j=i+1;j<=q;j++)
	    if (v[i]>v[j]){
	    	if (p[i]==p[j]){
	    		tag=0;goto _4781;
			}
			else if (p[i]<p[j]){
				if (vis[i]==1||vis[j]==2){
					tag=0;goto _4781;
				}
				else vis[i]=2,vis[j]=1;
			}
			else {
				if (vis[i]==2||vis[j]==1){
					tag=0;goto _4781;
				}
				else vis[i]=1,vis[j]=2;
			}
		}
	_4781:;
	if (!tag){
		printf("0");
		return 0;
	}
	for (int i=1;i<=q;i++)
	  if (!vis[i]) cnt++;
	printf("%lld\n",qpow(2,cnt));
	return 0;
}
```

---

## 作者：sndd (赞：2)

原题链接->[ARC182A](https://www.luogu.com.cn/problem/AT_arc182_a)

## 题意

给定长度为 $n$ 的序列 $S$（$S_i$初始值均为 $0$）。

需要完成 $Q$ 次操作，对于第 $i$ 次操作给定 $P_i$，$V_i$，可对序列 $S$ 进行如下两种操作：

* 将区间 $[1,P_i]$ 中所有元素替换为 $V_i$，需保证所有 $S_i<V_i$。
* 将区间 $[P_i,n]$ 中所有元素替换为 $V_i$，需保证所有 $S_i<V_i$。

需求出共有多少种不同的操作方式（对 $998244353$ 取模）。

# 思路

设两次操作 $i$，$j$（$i<j$）。

如果 $V_i \le V_j$，那么对两次询问都无影响。

然而如果存在 $V_i>V_j$，则需要分类讨论：

* 如果 $P_i=P_j$，则无解。
* 如果 $P_i<P_j$，则第 $i$ 次操作不能覆盖区间 $[P_i,n]$，第 $j$ 次操作不能覆盖区间 $[1,P_j]$。
* 如果 $P_i>P_j$，则第 $i$ 次操作不能覆盖区间 $[1,P_i]$，第 $j$ 次操作不能覆盖区间 $[P_j,n]$。

对于每个选择 $i$，枚举其前后的操作 $j$（若同时出现不能覆盖区间 $[1,P_i]$ 和 $[P_i,n]$ 的情况则也无解）。

对于有解的情况，如果有 $k$ 次选择没有限制，则答案为 $2^k$ 种。

时间复杂度 $O(q^2)$。

注：别忘了取模，开 long long。

## 完整代码

~~在题解区看到的~~巧妙方法。


```cpp
#include<bits/stdc++.h>
#define int long long			//？好像不开也能过 
using namespace std;
const int N=5001;
const int mod=998244353;

int n,Q;
int p[N],s[N],v[N];
int ans=1;				//别忘了赋初值 

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>Q;
	for(int i=1;i<=Q;i++){
		cin>>p[i]>>v[i];
	}
	for(int i=1;i<=Q;i++){
		int l=1,r=1;
		for(int j=1;j<i;j++){				//分别枚举前后的选择并分类讨论 
			if(v[j]>v[i]){
				if(p[j]<=p[i]) l=0;
				if(p[j]>=p[i]) r=0;
			}
		}
		for(int j=i+1;j<=Q;j++){
			if(v[j]<v[i]){
				if(p[j]<=p[i]) l=0;
				if(p[j]>=p[i]) r=0;
			}
		}
		ans=(ans*(l+r))%mod;				//一种巧算，l 或 r 值为 1 则可选，为 0 则不可选 
		if(!ans) break; 					//如果无解就跳出 
	}
	cout<<ans;
	return 0;
} 
```

---

## 作者：okra_l (赞：2)

### 题意

有一个长度为 $N$ 的整数序列 $S$。最初，所有元素都为 $0$。

你还给定了两个长度为 $Q$ 的整数序列：$P=(P_1, P_2,\ldots,P_Q)$ 和 $V = (V_1,V_2,\ldots,V_Q)$。

Snuke 想在序列 $S$ 上按顺序执行 $Q$ 个操作。第 $i$ 个操作如下：

- 将 $S_1,S_2,\ldots,S_{P_i}$ 的每个元素替换为 $V_i$。但是，在执行此操作之前，如果 $S_1,S_2,\ldots,S_{P_i}$ 中有任何一个元素大于 $V_i$，Snuke 将会开始哭泣。

- 将 $S_{P_i},S_{P_i+1},\ldots,S_N$ 的每个元素替换为 $V_i$。但是，在执行此操作之前，如果 $S_{P_i},S_{P_i+1},\ldots,S_N$ 中有任何一个元素大于 $V_i$，Snuke 将会开始哭泣。

找到 Snuke 可以在不哭泣的情况下执行所有 $Q$ 个操作的序列的数量，结果对 $998244353$ 取模。

### 思路

考虑每对操作 $(i,j),1 \le i<j \le Q$。如果操作 $i$ 对操作 $j$ 有影响，当且仅当 $v_i>v_j$。

如果 $V_i>V_j$，可以分为 $3$ 种情况:

1. $P_i=P_j$

无论 $i$ 如何操作，都会把 $P_i$ 的位置改为 $V_i$。无论 $j$ 如何操作，都需要满足 $P_j$ 的位置不大于 $V_j$。这显然是不能同时满足的。

2. $P_i<P_j$

如果 $i$ 选择向右，则会把 $P_j$ 位置改为 $V_i$，此时 $j$ 无法再操作，因此 $i$ 必须向左。

此时 $P_i$ 的位置已经为 $V_i$。如果 $j$ 选择向左，则 $P_i$ 的位置不满足 $P_i$ 不大于 $P_j$，无法操作。因此 $j$ 必须向右。

3. $P_i>P_j$

方式同上，$i$ 必须向右，$j$ 必须向左。

这样对于每个 $i$，我们都已经考虑了它对前面和后面所有操作的影响，因此不会再有其它冲突的情况了。$i$ 的方案数就是 $i$ 可以选的方向数，最后把所有的乘起来即为答案。

### 代码

```cpp
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int M=998244353;
const int N=5100;
int p[N],v[N];
int l[N],r[N];//l[i]表示i是否可以向左，1为可以，0为不行。r[i]同理。
int main(){
	int n,q;
	scanf("%d%d",&n,&q);
	for(int i=1;i<=q;i++){
		scanf("%d%d",&p[i],&v[i]);
	}
	for(int i=1;i<=q;i++){
		l[i]=r[i]=1;//初始时都可以操作
	}
	for(int i=1;i<=q;i++){
		for(int j=1;j<i;j++){
			if(v[j]>v[i]){
				if(p[i]==p[j]){
					l[i]=r[i]=0;//无论如何选择都无法满足条件，如果把l[i]与r[i]都置为0，则会让最后答案在这一位乘0，满足答案。
				}
				if(p[j]<p[i]){
					r[j]=0;
					l[i]=0;//j只能选右，i只能选左。
				}
				if(p[j]>p[i]){
					l[j]=0;
					r[i]=0;//j只能选左，i只能选右。
				}
			}
		}
	}
	int ans=1;
	for(int i=1;i<=q;i++)  ans=(1ll*ans*(l[i]+r[i]))%M;//l[i]+r[i]就是这一位的方案数。
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Guizy (赞：2)

#### 题意

给你一个长度为 $n$ 的整数序列 $s$（初始时 $s$ 中所有元素都为 $0$）和 $q$ 次操作，每次操作给你一个 $p$ 和 $v$。

对于每次操作，有一个致命二选一：

- 将 $s_1\sim s_p$ 替换为 $v$，但是如果在这之前，$s_1\sim s_p$ 中有某个元素的值严格大于 $v$，$\mathrm{Snuke}$ 就会哭。

- 将 $s_p\sim s_n$ 替换为 $v$，但是如果在这之前，$s_p\sim s_n$ 中有某个元素的值严格大于 $v$，$\mathrm{Snuke}$ 就会哭。

统计可以让 $\mathrm{Snuke}$ 不哭并且可以完成 $q$ 次操作的方案数。

> $n,q\le 5000$

#### 思路

考虑什么操作会对当前操作造成影响，和这个操作会对之后的什么操作造成影响，来对每个操作的选择进行约束。

对于操作 $i$，如果之前有一个操作 $j$，满足 $v_j\le v_i$，那 $j$ 肯定不会对 $i$ 造成影响。

$v_j>v_i$ 的情况我们分讨一下：

- $p_j<p_i$：第 $j$ 个操作选左边，第 $i$ 个选右边。
- $p_j=p_i$：两边都选不了，即无解。
- $p_j>p_i$：第 $j$ 个选右边，第 $i$ 个选左边。

对于之后的操作 $j$ 同理。

如果对于操作 $i$ 两边都可以选，那就把答案乘上 $2$；如果只能选一边，答案不变，如果两边都选不了答案为 $0$。

#### 实现

```cpp
const int Max=2000010;
const int p=998244353;
int n,q,a[Max],b[Max];

signed main(){
	
	cin.tie(0)->sync_with_stdio(0);
	
	cin>>n>>q;
	for(int i=1;i<=q;i++) 
		cin>>a[i]>>b[i];
	
	int ans=1;
	for(int i=1;i<=q;i++){
		int l=1,r=1;
		for(int j=1;j<i;j++)
			if(b[j]>b[i]){
                if(a[j]<=a[i]) l=0;
				if(a[j]>=a[i]) r=0;
			}
		for(int j=i+1;j<=q;j++)
			if(b[j]<b[i]){
                if(a[j]<=a[i]) l=0;
				if(a[j]>=a[i]) r=0;
			}
        (ans*=(l+r))%=p;
	}
	cout<<ans;
}
```

---

## 作者：Down_syndrome (赞：2)

## 题意

有一个长度为 $n$ 的序列 $S$，初始时 $S$ 内所有元素的值都为 $0$。给出 $q$ 次操作，每次给出 $V_i$ 和 $P_i$，需要你按顺序执行。一次操作为：

> 你每次可以选择以下其中一种操作：
> 
> 1. 令 $S_i\gets V_i(\forall i\in[1,P_i])$，需要保证操作前 $S_i\le V_i$。
> 2. 令 $S_i\gets V_i(\forall i\in[P_i,n])$，需要保证操作前 $S_i\le V_i$。

问你有多少种不同的操作方式，对 $998244353$ 取模。

## 思路

假设存在 $V_i>V_j(i<j)$，那么 $i$ 和 $j$ 的操作必定相反，因为 $S$ 中的元素在操作后只增不减，所以若两区间重合一定不行。所以如果 $P_i=P_j$ 则无解。

继续思考，如果存在 $V_i,V_j>V_k(i,j<k)$，且 $P_i<P_k<P_j$，那也无解，因为 $k$ 必定和 $i,j$ 有交集。

往后找也是同理，如果有 $P$ 相等或存在 $V_k>V_i,V_j,(i,j>k)$，且 $P_i<P_k<P_j$，也是无解。

考虑有解的情况。对于每个 $i$，如果存在 $j<i,V_j>V_i$ 或 $j>i,V_j<V_i$，并且所有 $P_j$ 都在 $P_i$ 的其中一边（不在同一边无解），那么 $i$ 操作的方向就固定了，只有一种操作方式，否则 $i$ 操作方向任意。

所以 $ans=2^k$，$k$ 是没有限制的操作数量。

[code](https://atcoder.jp/contests/arc182/submissions/56604690)

---

## 作者：LLLLLL7381 (赞：2)

~~ARC的题目向来考察人类智慧，这次更是。~~

老规矩，上题意：

## 题目大意
有一个长度为 $n$ 的序列 $S$，初始值均为 $0$。有两个长度为 $q$ 的序列 $P$ 和 $V$，接下来你有两种操作。也就是对于第 $i$ 次操作在下面任选其一。       
1.将 $S_j$ 替换为 $V_i$，其中 $j \in [1,P_i]$。        
2.将 $S_j$ 替换为 $V_i$，其中 $j \in [P_i,n]$。       
输出符合条件的操作数，满足被替换的所有元素均小于等于 $V_i$，否则输出 $0$。

## 思路
首先题目数据范围并不大，可以分别枚举操作 $i$ 和 $j$。                       
接下来分类讨论：                    
1.当 $V_i \le V_j$ 的时候，因为在替换的过程中序列元素只增不减，所以任何操作都是可以的。                
由于第一种情况下可行的操作实在太多了，所以可以考虑先将所有可行的操作排除以后再处理最后的结果。

注意：接下来所有的情况都建立在 $V_i > V_j$ 上。                 

2.当 $P_i=P_j$ 的时候，这个时候只会让序列 $S$ 元素越来越小，无论在 $P$ 的左侧还是右侧，显然这种情况寄了。                                       
3.$P_i<P_j$，这种情况下，如果这个时候把较大的 $V_i$ 直接安排在 $P_i$ 右侧，这个时候会导致无论在 $P_j$ 哪一边修改都会导致存在元素大于 $V_j$。可以画图“感性理解一下”。所以这个时候 $i$ 操作在 $P_i$ 左，$j$ 操作在 $P_j$ 右。                            
4.$P_i>P_j$，按照上面的思路，可以得出 $i$ 操作在 $P_i$ 右，$j$ 操作在 $P_j$ 左。                        
经过上面的重重筛选，最后如果答案不是 $0$，必定会有没有附加约束条件的操作（即每种操作必须在哪一个位置执行或者不可执行），因为每种操作都有两种选择，所以如果有 $cnt$ 个操作符合条件，那么最后结果为 $2^{cnt}$。**千万别忘了取模啊！！！！！！！！**。

最后是 $O(q^2)$，能过。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read()
{
   int x=0,f=1;
   char ch=getchar();
   while(ch<'0'||ch>'9')
   {
       if(ch=='-')
           f=-1;
       ch=getchar();
   }
   while(ch>='0' && ch<='9')
       x=x*10+ch-'0',ch=getchar();
   return x*f;
}
const int maxn = 5005;
const int mod = 998244353;
int chk[maxn],p[maxn],v[maxn];
inline int ksm(int x,int y)
{
	int res=1;
	while(y)
	{
		if(y&1)
		{
			res=res*x%mod;
		}
		x=x*x%mod;
		y>>=1;
	}
	return res;
}
inline void work(int pos,int val)
{
	if(chk[pos]==0)
	{
		chk[pos]=val;
	}
	else if(chk[pos]!=val)
	{
		puts("0");
		exit(false);
	}
	return;
}
signed main()
{
	int n=read(),q=read();
	for(int i=1;i<=q;i++)
	{
		p[i]=read(),v[i]=read();
	}
	for(int i=1;i<=q;i++)
	{
		for(int j=i+1;j<=q;j++)
		{
			if(v[i]<=v[j])
			{
				continue;
			}
			if(p[i]==p[j])
			{
				puts("0");
				exit(false);
			}
			if(p[i]<p[j])
			{
				work(i,-1);
				work(j,1);
			}
			else
			{
				work(i,1);
				work(j,-1);
			}
		}
	}
	int cnt=0;
	for(int i=1;i<=q;i++)
	{
		if(chk[i]==0)
		{
			cnt++;
		}
	}
	cout<<ksm(2,cnt)<<endl;
	return 0;
}
```

---

## 作者：WuMin4 (赞：2)

# 思路
分类讨论。  
对于 $Q$ 次操作中的第 $i$ 次 操作和第 $j$ 次操作 $(i<j)$：  
* 若 $V_i\le V_j$，则这两次操作之间不会影响。
* 若 $V_i>V_j$ 且 $P_i=P_j$，则这两次操作之间一定冲突，因为 $i$ 这个位置一定会修改。  
* 若 $V_i>V_j$ 且 $P_i<P_j$，则操作 $i$ 一定替换前 $P_i$ 个元素，操作 $j$ 一定替换从 $P_j$ 开始到末尾的元素。  
* 若 $V_i>V_j$ 且 $P_i>P_j$，则操作 $i$ 一定替换从 $P_i$ 开始到末尾的元素，操作 $j$ 一定替换前 $P_j$ 个元素。

注意到 $1\le Q\le 5000$，于是可以 $O(Q^2)$ 枚举 $i,j$。设 $k$ 为不确定的操作数量（及替换前面或后面都可以的操作），答案即为 $2^k\bmod 998244353$。  
# 代码
```cpp
#include<bits/stdc++.h>
#define md 998244353
using namespace std;
int n,q,ans=1,dir[5005];//0为不确定，1为向前，2为向后
struct node{
	int p,v;
}a[5005];
signed main(){
	cin>>n>>q;
	for(int i=1;i<=q;i++){
		cin>>a[i].p>>a[i].v;
		for(int j=1;j<i;j++){
			if(a[j].v>a[i].v){
				if(a[j].p>a[i].p){
					if(dir[j]==1||dir[i]==2){//与之前确定的方向冲突
						cout<<0;
						return 0;
					}
					dir[j]=2;
					dir[i]=1;
				}
				else if(a[j].p<a[i].p){
					if(dir[j]==2||dir[i]==1){//同理
						cout<<0;
						return 0;
					}
					dir[j]=1;
					dir[i]=2;
				}
				else{//位置相同冲突
					cout<<0;
					return 0;
				}
			}
		}
	}
	for(int i=1;i<=q;i++)
		if(!dir[i])
			ans=(ans*2)%md;
	cout<<ans;
	return 0;
}
```

---

## 作者：banned_gutongxing (赞：1)

## 思路

因为前面不允许出现比这次的替换的值还要大的情况，所以如果我们知道下标 $i,j$ 满足 $i<j$ 且 $V_i>V_j$ 的话，我们就必须把它们两次修改分开。具体地：

1. 若 $P_i<P_j$：\
   此时，我们只能将 $[1,P_i]$ 的值设为 $V_i$，将 $[P_j,n]$ 的值设为 $V_j$。
2. 若 $P_i>P_j$：\
   此时，我们只能将 $[P_i,n]$ 的值设为 $V_i$，将 $[1,P_j]$ 的值设为 $V_j$。
3. 若 $P_i=P_j$：\
   此时，一定无解。

我们可以选择倒序枚举，逐渐推出前面的值一定不能是左边或一定不能是右边。

+ 对于两边都能选的情况，直接 $ans\gets ans\times 2$。
+ 对于两边只有一边能选的情况 $ans$ 不变。
+ 对于两边都不能选的情况，直接无解。

## 代码
```cpp
// Problem: A - Chmax Rush!
// Contest: AtCoder - AtCoder Regular Contest 182
// URL: https://atcoder.jp/contests/arc182/tasks/arc182_a
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define int long long
namespace gtx{
//	Fast IO
	void read(int &x){
		x = 0;int h = 1;char tmp;
		do{tmp=getchar();if(tmp=='-')h*=-1;}while(!isdigit(tmp));
		while(isdigit(tmp)) x*=10,x+=tmp-'0',tmp=getchar();
		x*=h;
	}
	void read(char &x){do{x=getchar();}while(x==' '||x=='\n'||x=='\r');}
	void write(char x){putchar(x);}
	void write(int x){
		if(x<0) putchar('-'),x=-x;int st[200]={0},tot=0;
		do{st[++tot]=x%10,x/=10;} while(x);
		while(tot){putchar(st[tot--]+'0');};
	}
	void write(int x,char y){write(x);write(y);}
	const int MAXN = 5100;
	const int MOD = 998244353;
	int n,q,p[MAXN],v[MAXN];
	bool can_be[2][MAXN];
	signed main(){
		read(n);read(q);
		for(int i = 1;i<=q;i++){
			read(p[i]);read(v[i]);
			can_be[0][i] = can_be[1][i] = 1;
		}
		int ans = 1;
		for(int i = q;i>=1;i--){
			for(int j = i-1;j>=1;j--){
				if(v[j]>v[i]){
					if(p[i]==p[j]) return puts("0"),0;
					if(p[i]<p[j]){
						can_be[1][i] = 0;
						can_be[0][j] = 0;
					}else{
						can_be[1][j] = 0;
						can_be[0][i] = 0;
					}
				}
			}
			ans = (ans*(can_be[0][i]+can_be[1][i]))%MOD;
		}
		write(ans);
		return 0;
	}
}
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
//	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int T = 1;
//	gtx::read(T);
	while(T--) gtx::main();
	return 0;
}
```

---

## 作者：Coffins (赞：1)

来气，于是写个题解（？

首先~~因为 ARC A 不会考真计数所以~~考虑一下有哪些性质。

然后发现如果有 $i< j，v_i>v_j$，那么 $i$ 和 $j$ 的方向就确定了，因为这两者覆盖的地方不能重。

这样的话发现许多位置的操作方向都是确定的，一个操作 $i$ 的方向不确定当且仅当 $\forall j< i,v_j<v_i$ 且 $\forall i<j,v_i<v_j$，我们称其为“自由操作”。

我们发现这些操作没有任何影响，只要合法即可，于是我们在确定其他操作方向后直接看当前“自由操作”有多少种合法方向即可，若有合法方案且 $k$ 个“自由操作”两个方向都可以选，那么方案数就是 $2^k$。

于是我们直接暴力判即可，复杂度为 $O(nq+q^2)$。

然而唐诗的我赛时一直按照 $O(n\log n)$ 做的，浪费不少时间，于是~~为了不白因此掉分~~讲一下 $O(n\log n)$ 的做法。

我们发现我们其实没有必要把所有存在约束条件的 $(i,j)$ 对都 check 一遍，考虑找出非“自由操作”的所有操作前任意一个大于它或后面任意一个小于它的操作，这样即使不合法也可以最后一起判掉，这样就把需要的 check 次数降到 $O(q)$，然后加上线段树便可以实现 $O(q\log n)$。

https://atcoder.jp/contests/arc182/submissions/56607629

---

## 作者：時空 (赞：0)

[In Luogu](https://www.luogu.com.cn/problem/AT_arc182_a)

好题。

考虑一对操作 $(i,j)$，其中 $i < j$。若 $v_i \le v_j$，此时操作 $i$ 对操作 $j$ 没有影响。

考虑 $v_i > v_j$ 的情况，对 $p_i, p_j$ 进行分讨。

1. $p_i=p_j$，此时无论操作 $i$ 向左还是向右进行操作，都会将 $p_j$ 替换为 $v_i$，而操作 $j$ 时又需要 $p_j = v_i \le v_j$，这与 $v_i > v_j$ 矛盾，故答案为 $0$。

2. $p_i > p_j$，此时若操作 $i$ 向左操作，将 $p_1 \sim p_i$ 替换为 $v_i$，会将 $p_j$ 替换为 $v_i$，矛盾。具体原因同上。故此时操作 $i$ 只能向右操作，操作 $j$ 只能向左操作。

3. $p_i < p_j$，此时若操作 $i$ 向右操作，将 $p_i \sim p_Q$ 替换为 $v_i$，会将 $p_j$ 替换为 $v_i$，矛盾。具体原因同上。故此时操作 $i$ 只能向左操作，操作 $j$ 只能向右操作。

那么对于每个 $i$，我们都得到了它可以操作的方向数（若没有出现 $v_i > v_j$ 的情况就是两个方向均可）。相乘得到答案。

---

## 作者：_Weslie_ (赞：0)

第一次打 ARC，涨了 $24$ 分。

## 思路

我们称 $i$ 对 $j$ 有限制，当且仅当 $i<j$ 且 $v_i>v_j$。

我们枚举 $i$，从 $i$ 往后找 $j$，找到第一个被 $i$ 限制的 $j$。

接下来我们分类讨论：

- 如果 $p_i=p_j$，无论如何也没有答案，输出 $-1$。
- 如果 $p_i>p_j$，则第 $i$ 次操作只能往右赋值，第 $j$ 次只能往左。
- 如果 $p_i<p_j$，则第 $i$ 次操作只能往左赋值，第 $j$ 次只能往右。

找到之后我们赋值 $a_i$（$a_i$ 表示第 $i$ 次赋值的方向），然后退出寻找。当我们枚举到 $i=x$ 时，接着分类：

- 如果 $a_x$ 已经被赋值，则把该方向上的所有点都赋值。如果发现无法赋值，输出不可以，退出程序。
- 如果 $a_x$ 未被赋值，则分别检验两个方向是否可以赋值，如果没有一个可以，则输出不可以。反之，则将答案乘以可行的方向数量（乘法原理可得）。

于是就做完了。

## 代码

```
#include<bits/stdc++.h>
using namespace std;
int n,q;
int a[5005];
int p[5005],v[5005],z[5005];
long long ans=1;
int main() {
	scanf("%d%d",&n,&q);
	for(int i=1; i<=q; i++) {
		scanf("%d%d",&p[i],&v[i]);
		z[i]=-1;
	}
	for(int i=1; i<=q; i++) {
		for(int j=i+1; j<=q; j++) {
			if(v[i]>v[j]) {
				if(p[j]>p[i]) {
					if(z[j]==0) {
						printf("0");
						return 0;
					} else z[j]=1;
					if(z[i]==1) {
						printf("0");
						return 0;
					} else z[i]=0;
				} else {
					if(z[j]==1) {
						printf("0");
						return 0;
					} else z[j]=0;
					if(z[i]==0) {
						printf("0");
						return 0;
					} else z[i]=1;
				}
				break;
			}
		}
		if(z[i]==-1) {
			int tot=2;
			for(int j=p[i]; j>=1; j--) {
				if(a[j]>v[i]) {
					tot--;
					break;
				}
				a[j]=v[i];
			}
			for(int j=p[i]; j<=n; j++) {
				if(a[j]>v[i]) {
					tot--;
					break;
				}
				a[j]=v[i];
			}
			ans=ans*tot%998244353;
			if(tot==0) {
				printf("0");
				return 0;
			}
		} else {
			if(z[i]==1) {
				for(int j=p[i]; j<=n; j++) {
					if(a[j]>v[i]) {
						printf("0");
						return 0;
					}
					a[j]=v[i];
				}
			}
			else{
				for(int j=p[i]; j>=1; j--) {
				if(a[j]>v[i]) {
					printf("0");
					return 0;
				}
				a[j]=v[i];
			}
			}
		}
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：ben090302 (赞：0)

试考虑对于任意一个 $i<j$，如果 $V_i>V_j$，那么 $i$ 与 $j$ 就会互相干扰。

如果 $P_i=P_j$，那太好了，$j$ 不管怎么选操作最后在 $P_i$ 这个点都会出现 $S_{P_i}>V_j$ 的现象，此时可以通报答案为 $0$。

如果 $P_i\neq P_j$，那么我们就让 $P$ 小的那个执行操作 $1\to P$，大的那个 $P\to n$ 就可以了。

我们记录一个方向数组，如果 $sd_i=1$ 代表必须往 $n$ 操作，$sd_i=-1$ 代表必须往 $1$ 操作，$sd_i=0$ 代表无约束，枚举 $i,j$ 即可，如果出现我们既要一个操作向左又要他向右也是无解。

答案统计就遍历 $1\to Q$，$ans$ 初始设为 $1$，如果 $sd_i=0$ 就把答案乘 $2$。

复杂度 $O(Q^2)$。

code:

```
#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;
const int N=5005;
int P[N],V[N];//S[N];
int n,q;  
int sd[N];
int ans=1;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>q;
    for(int i=1;i<=q;i++){
        cin>>P[i]>>V[i];
    }
    for(int j=1;j<=q;j++){
        for(int i=j+1;i<=q;i++){
            if(V[i]>=V[j]) continue;
            if(P[i]==P[j]){
                cout<<0;
                return 0;
            }
            if(P[j]<P[i]){
                if(sd[i] and sd[i]!=1){
                    cout<<0;
                    return 0;
                }
                if(sd[j] and sd[j]!=-1){
                    cout<<0;
                    return 0;
                }
                sd[j]=-1,sd[i]=1;
            }
            else{
                if(sd[i] and sd[i]!=-1){
                    cout<<0;
                    return 0;
                }
                if(sd[j] and sd[j]!=1){
                    cout<<0;
                    return 0;
                }
                sd[j]=1,sd[i]=-1;
            }
        }
    }
    for(int i=1;i<=q;i++) ans=ans*((1+(sd[i]==0)))%mod;
    cout<<ans;
}
```

---

## 作者：EricWan (赞：0)

很毒瘤的一个题，结论很简洁，但是样例太水，根本看不出来，样例过水，我还吃了一个罚时。

我们一步步思考：

对于一个操作，如果前面的操作中有一个 $V$ 比它小的，那么它肯定不能走那一边，否则会出事。

对于一个操作，如果前面的操作中有一个 $V$ 比它大的，那么它肯定不能走那一边，否则会出事。

我们扫一遍就可以知道每一个操作是否可以走右或者走左。

之后我们可以证明求出来的可以的操作都可以取（简要证明：前面不比它大的不用考虑，前面比它大的考虑了，同时，前面比它大的也考虑了它），我们直接通过乘法原理计算答案即可。

代码：

```cpp
#include <bits/stdc++.h>
#define mod 998244353
#define MAXN 1000005
using namespace std;
int n, q, flag1[MAXN], flag2[MAXN], p[MAXN], v[MAXN], maxn[MAXN], minn[MAXN], un[MAXN];
signed main() {
	int ans = 1;
	cin >> n >> q;
	for (int i = 1; i <= q; i++) {
		cin >> p[i] >> v[i];
		for (int j = 1; j <= p[i]; j++)
			if (maxn[j] > v[i])
				flag1[i] = 1;
		for (int j = p[i]; j <= n; j++)
			if (maxn[j] > v[i])
				flag2[i] = 1;
		maxn[p[i]] = max(maxn[p[i]], v[i]);
	}
	for (int i = 1; i <= n; i++)
		minn[i] = 2e9;
	for (int i = q; i >= 1; i--) {
		for (int j = 1; j <= p[i]; j++)
			if (minn[j] < v[i])
				flag1[i] = 1;
		for (int j = p[i]; j <= n; j++)
			if (minn[j] < v[i])
				flag2[i] = 1;
		minn[p[i]] = min(minn[p[i]], v[i]);
	}
	for (int i = 1; i <= q; i++) {
		if (flag1[i] && flag2[i]) {
			cout << 0;
			return 0;
		}
		if (flag1[i] == 0 && flag2[i] == 0) {
			ans = ans * 2 % mod;
		}
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：2023lpx (赞：0)

## 题目大意

给你序列 $P$ 和 $V$，要求你按顺序对序列 $S$ 进行操作。

有两种操作，每次选其中一种。

- 将元素 $S_1​,S_2​,\dots,S_{P_i}$​​ 替换为 $V_i$。但是，在此操作之前，要求 $S_1​,S_2​,…,S_{P_i} \le V_i$。
  
- 将元素 $S_{P_i},S_{P_i+1},\dots,S_{N}$​​ 替换为 $V_i$。但是，在此操作之前，要求 $S_{P_i},S_{P_i+1},\dots,S_{N}\le V_i$。
  

求合法的顺序的个数。

$1 \leq N,Q\leq 5000$。

## 思路

很明显，$Q$ 非常小，$O(Q^2)$ 能过。

于是考虑暴力。

我们对于每一个 $V_i$，查询所有的 $V_j(j \neq i)$，判断 $V_i$ 是否能在 $V_j$ 前或后进行两种操作即可。

显然，若两种操作都可行，$ans\times2$。

若两种操作都不可行，输出 $-1$。

## code

[link](https://atcoder.jp/contests/arc182/submissions/56603437)

---

## 作者：D0000 (赞：0)

为了方便，这里规定：

$E_i=0$ 表示第 $i$ 步选择操作 1。

$E_i=1$ 表示第 $i$ 步选择操作 2。

因为操作有先后，所以对于第 $i$ 步，需要看是否会影响 $i+1$ 至 $q$ 步，因此对于所有 $i<j$：

如果 $v_i\le v_j$，则没有影响。

否则若 $p_i<p_j$，则 $E_i=0,E_j=1$；若 $p_i=p_j$，则 $E_i\ne E_j$；若 $p_i>p_j$，则 $E_i=1,E_j=0$。原因是第 $i$ 次操作的区间不得与第 $j$ 次的重合。

比较所有条件看有没有矛盾。如果没有矛盾，则一定有解。再看上面，一些位置的 $E_i$ 是确定的。一些没有，但是对于某个位置的 $E_i$ 确定了，一些位置也会确定，形成了一个联通块（貌似是二分图），DFS 一下，答案就是 $2^k$，其中 $k$ 是未确定的位置中通过关系 $E_i\ne E_j$ 给 $(i,j)$ 连边，形成的联通块的个数。

时间复杂度 $O(n+q^2)$，可以通过本题。

代码：

```cpp

#include<cstdio>
#include<algorithm>
#include<vector>
int n,q,p[5005],v[5005],ans=1,mod=998244353;
struct node{
    int b;
    std::vector<int>v;
    int ans;
}a[5005];
bool dfs(int now,int id=-1){
    if(id==-1)id=a[now].ans;
    if(id==-1)a[now].ans=id=1;
	if(a[now].ans!=id)return 0;
    if(a[now].b)return 1;
    a[now].b=1;
    
    for(int v:a[now].v){
        if(!dfs(v,!id))return 0;
    }
    return 1;
}
bool solve(int x){
    for(int i=1;i<=x;i++)a[i].ans=-1,a[i].b=0,a[i].v.clear();
    for(int i=1;i<=x;i++)for(int j=i+1;j<=x;j++)if(v[i]>v[j]){
        if(p[i]==p[j]){
            a[i].v.push_back(j);
            a[j].v.push_back(i);
        }
        else if(p[i]<p[j]){
            if(a[i].ans==1||a[j].ans==0)return 0;
            a[i].ans=0,a[j].ans=1;
        }
        else{
            if(a[i].ans==0||a[j].ans==1)return 0;
            a[i].ans=1,a[j].ans=0;
        }
    }
    for(int i=1;i<=x;i++)if(!a[i].b&&a[i].ans!=-1)if(!dfs(i))return 0;
    for(int i=1;i<=x;i++)if(!a[i].b){
    	if(!dfs(i))return 0;
    	ans<<=1;
    	ans%=mod;
	}
    return 1;
}
int main(){
	scanf("%d%d",&n,&q);
    for(int i=1;i<=q;i++)scanf("%d%d",&p[i],&v[i]);
    if(!solve(q))return !puts("0");
    printf("%d",ans);
}

```

---

## 作者：I_will_AKIOI (赞：0)

对于每个操作，你可以选择从该点开始往左或往右染色，但是不能染到比这个数大的颜色上。所以发现只有当大的数比小的数先操作才可能出现无解的情况。由于每个点只有 $2$ 种染色方案，所以答案一定是 $2$ 的幂或无解。

假设当前枚举到了操作 $i$，那么我们再枚举一个 $j\in[i+1,q]$。如果 $V_i>V_j$，就接着分类讨论。这时如果 $P_i<P_j$，那么 $i$ 只能往左染色，$j$ 只能往右染色。这时如果 $P_i>P_j$，那么 $i$ 只能往右染色，$j$ 只能往左染色。如果在枚举的过程中，发现 $i$ 既要往左染，还要往右染色，那么就说明无解。否则如果不存在这样的 $j$，说明 $i$ 往左往右都可以，有两种方案，否则就只有一种。最后乘法原理乘起来就行。

但是可能会出现 $i$ 用 $j$ 判断，$j$ 不能判断 $i$ 的情况。所以我们需要枚举 $j\in[1,i-1]$ 的情况。

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 998244353
#define N 5005
#pragma GCC optimize("O3")
using namespace std;
int n,m,ans=1,a[N],b[N],f[N];
signed main()
{
	ios::sync_with_stdio(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++) cin>>a[i]>>b[i];
	for(int i=1;i<=m;i++)
	{
		int f=0;
		for(int j=i+1;j<=m;j++)
		{
			if(b[i]>b[j])
			{
				if(a[j]<a[i]) f=2;
				else if(a[j]>a[i]) f=1;
				else f=-1;
			}
			if(f==-1)
			{
				cout<<0;
				return 0;
			}
		}
		for(int j=1;j<i;j++)
		{
			if(b[j]>b[i])
			{
				if(a[i]>a[j])
				{
					if(f==1) f=-1;
					else f=2;
				}
				else if(a[i]<a[j])
				{
					if(f==2) f=-1;
					else f=1;
				}
				else f=-1;
			}
			if(f==-1)
			{
				cout<<0;
				return 0;
			}
		}
		if(f==0) ans=ans*2%mod;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：lkjzyd20 (赞：0)

### 思路
首先题目数据范围 $(1\le Q \le 5000)$ 并不大，可以分别枚举操作 $i$ 和 $j$。

接下来分类讨论:
+ 当 $V_i \le V_j$ 的时候，因为在替换的过程中序列元素只增不减，所以任何操作都是可以的。

+ 当 $V_i>V_j$ 的时候，有三种情况。
  + 当 $P_i=P_j$ 的时候，这个时候只会让序列 $S$ 元素越来越小，则这两次操作之间一定冲突。
  
  + 当 $P_i<P_j$ 的时候，这种情况下，如果这个时候把较大的 $V_i$ 直接安排在 $P_i$ 右侧，这个时候会导致无论在 $P_i$ 哪一边修改都会导致存在元素大于 $V_i$。则操作 $i$ 一定替换前 $P_i$ 个元素，操作 $j$ 一定替换从 $P_j$ 开始到末尾的元素。
 
  + 当 $P_i>P_j$ 的时候，按照上面的思路，可以得出操作 $i$ 一定替换从 $P_i$ 开始到末尾的元素，操作 $j$ 一定替换前 $P_j$ 个元素。
 
最后注意如果答案不为 $0$，必定会有没有附加约束条件的操作（即每种操作必须在哪个位置执行或者不可执行），因为每种操作都有两种选择，设 $k$ 为不确定的操作数量（及替换前面或后面都可以的操作），那么最后结果为 $2^k \bmod 998244353$ 。

综上所述，时间复杂度为 $O(Q^2)$。

### 代码如下
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
#define rep(i, l, r) for(int i = l; i <= r; ++ i)
#define per(i, r, l) for(int i = r; i >= l; -- i)
const int mod = 998244353, N = 5001;
int Q, a[N], b[N], ans = 1;
main()
{
    scanf("%lld %lld", &Q, &Q);
    rep(i, 1, Q) scanf("%lld %lld", &a[i], &b[i]);
    rep(i, 1, Q)
    {
		int l = 1, r = 1;
        rep(j, 1, i - 1)
			if(b[j] > b[i]) 
            {
                if(a[j] <= a[i]) l = 0;
				if(a[j] >= a[i]) r = 0;
			}
        rep(j, i + 1, Q)
			if(b[j] < b[i])
            {
                if(a[j] <= a[i]) l = 0;
				if(a[j] >= a[i]) r = 0;
            }
        ans = ans * (l + r) % mod;
	}
    printf("%lld", ans);
}
```

---

## 作者：Red_river (赞：0)

### 题目大意
这道题的题意就是说给你一个 $n$ 和 $m$ 接着有 $m$ 个询问，假设分别为 $x_i$ 和 $y_i$ 来代表，那么让你求满足任意一组询问以下条件的方案数。


- 在 $x_i$ 的左边的所有值满足没有严格大于 $y_i$ 的任何数，并将前面包括自己的数都填为 $y_i$。
- 在 $x_i$ 的右边的所有值满足没有严格大于 $y_i$ 的任何数，并将后面包括自己的数都填为 $y_i$。

### 题意分析
首先这道题我们其实可以每次枚举一个操作，然后再枚举之前的操作。最终当他不管怎么填都填不了时，我们就可以直接输出零了，否则继续。具体可以参考代码及注释理解。
### CODE

```cpp
#include<bits/stdc++.h>
#define wk(x) write(x),putchar(' ')
#define wh(x) write(x),putchar('\n')
#define ll long long
#define mod 998244353
#define N 200005
#define NO printf("No\n")
#define YES printf("Yes\n")
using namespace std;
int n,m,k,jk,ans,sum,num,cnt,tot;
int dis[N],vis[N],wis[N],f[N];

inline void read(int &x){
	x=0;int ff=1;char ty;
	ty=getchar();
	while(!(ty>='0'&&ty<='9'))
	{
		if(ty=='-') ff=-1;
		ty=getchar();
	}
	while(ty>='0'&&ty<='9')
		x=(x<<3)+(x<<1)+ty-'0',ty=getchar();
	x*=ff;return;
}

inline void write(int x){
	if(x<0){
		x=-x;putchar('-');
	}if(x>=10) write(x/10);
	putchar('0'+x%10);
	return;
}

signed main()
{
	read(n),read(m);int x=0,y=0;
	for(int i=1;i<=m;i++) read(dis[i]),read(vis[i]);
	long long ans=1;
	for(int i=1;i<=m;i++)
	{
		x=y=1;
		for(int j=1;j<i;j++)
			if(vis[j]>vis[i]){
				if(dis[j]>=dis[i]) y=0;
				if(dis[j]<=dis[i]) x=0;
			}
		for(int j=i+1;j<=m;j++)
			if(vis[j]<vis[i]){
				if(dis[j]>=dis[i]) y=0;
				if(dis[j]<=dis[i]) x=0;
			}//以上是枚举方案。
		if(x+y==0){
			wh(0);//直接输出无解。
			return 0;
		}
		ans=ans*(x+y)%mod;//统计答案。
	}
	cout<<ans;//输出。
	return 0;
}
```

---

## 作者：JXR_Kalcium (赞：0)

## 题目大意

你有一个长度为 $N$ 的序列 $S$，一开始的时候 $S$ 里的所有元素都为 $0$，然后有两个长度为 $Q$ 的序列 $P,V$，你将对 $S$ 进行 $Q$ 次操作，每次第 $i$ 个操作有两种小操作，第一种是将 $S_1,S_2,\cdots,S_{P_i}$ 均替换为 $V_i$，如果 $S_1,S_2,\cdots,S_{P_i}$ 的序列中存在一个元素 $x$ 使得 $x>V_i$，则终止操作；第二种是将 $S_{P_i},S_{P_{i+1}},\cdots,S_N$ 均替换为 $V_i$，如果 $S_{P_i},S_{P_{i+1}},\cdots,S_N$ 的序列中存在一个元素 $x$ 使得 $x>V_i$，则终止操作，问做完这 $Q$ 次操作后有多少种小操作的方案，答案对 $998244353$ 取模。

## 解题思路

可以想到，对于第 $i$ 次操作，如果对于它以前的操作 $1\le j<i$ 有 $V_i\ge V_j$，那么说明当前这个操作不会终止（因为要保证以前的要比现在的小），否则又分为两种情况，如果 $P_i\le P_j$，那么假如我们这一次做第一种小操作，那么 $S_1,S_2,\cdots,S_{P_i}$ 以前肯定都被赋值为 $V_j$，而现在 $V_i<V_j$，所以肯定会终止第一种小操作；接着，如果 $P_i\ge P_j$，那么假如我们这一次做第二种小操作，那么 $S_{P_i},S_{P_{i+1}},\cdots,S_N$ 以前肯定都被赋值为 $V_j$，而现在 $V_i<V_j$，所以肯定会终止第二种小操作。然后，对于它后面的操作 $i<j\le Q$ 也是一样，如果存在 $V_i\le V_j$，那么说明当前这个操作不会终止，否则跟上面两个小操作的处理一样。

综上，每次操作先去假设两种小操作可行，然后按照上面的方式去更新两种小操作是否可行，最后根据乘法原理让可行的小操作数与答案相乘即可。

## AC 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define endl putchar(10)
#define spc putchar(32)
using namespace std;

inline ll read()
{
    ll x=0,f=1; char c=getchar();

    while(c<48 || c>57)
    {
        if(c=='-') f=-1;
        c=getchar();
    }

    while(c>47 && c<58)
    x=(x<<1)+(x<<3)+c-48, c=getchar();
    return x*f;
}

inline void write(ll x)
{
    static ll sta[41]; ll top=0;
    if(x<0) putchar('-'), x=-x;
    do sta[top++]=x%10, x/=10; while(x);
    while(top) putchar(sta[--top]+48);
}

const ll mod=998244353;
ll n,q,p[5001],v[5001],a,b,ans=1;

int main()
{
    n=read(); q=read();
    for(int i=1; i<=q; ++i) p[i]=read(), v[i]=read();

    for(int i=1; i<=q; ++i)
    {
        a=1; b=1;

        for(int j=1; j<i; ++j)
        {
            if(v[i]<v[j])
            {
                if(p[i]<=p[j]) a=0;
                if(p[i]>=p[j]) b=0;
            }
        }

        for(int j=i+1; j<=q; ++j)
        {
            if(v[i]>v[j])
            {
                if(p[i]<=p[j]) a=0;
                if(p[i]>=p[j]) b=0;
            }
        }

        if(!a && !b) write(0),exit(0);
		ans=ans*(a+b)%mod;
    }

    write(ans);
    return 0;
}
```

---

