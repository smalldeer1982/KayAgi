# [ABC093D] Worst Case

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc093/tasks/arc094_b

高橋君を含めた $ 10^{10^{10}} $ 人の参加者が $ 2 $ 回のプログラミングコンテストに参加しました。 各コンテストでは全員に $ 1 $ 位から $ 10^{10^{10}} $ 位までの相異なる順位がつきました。

参加者のスコアとは、$ 2 $ 回のコンテストでの順位を掛け合わせた値です。

次のクエリ $ Q $ 個に答えてください。

- $ i $ 個目のクエリでは、$ 2 $ つの正の整数 $ A_i,B_i $ が与えられる。高橋君が $ 1 $ 回目のコンテストで $ A_i $ 位、$ 2 $ 回目のコンテストで $ B_i $ 位を取ったと仮定して、高橋君よりスコアの小さい参加者の人数の最大値を求めよ。

## 说明/提示

### 制約

- $ 1\ \leq\ Q\ \leq\ 100 $
- $ 1\leq\ A_i,B_i\leq\ 10^9(1\leq\ i\leq\ Q) $
- 入力はすべて整数である

### Sample Explanation 1

$ 1 $ 回目のコンテストで $ x $ 位を、$ 2 $ 回目のコンテストで $ y $ 位を取った参加者を $ (x,y) $ で表すことにします。 $ 1 $ つめのクエリでは、高橋君よりスコアの小さい参加者として $ (2,1) $ が考えられます。$ 2 $ 人以上のスコアが高橋君のスコアより小さくなることはないため、$ 1 $ を出力します。

## 样例 #1

### 输入

```
8
1 4
10 5
3 3
4 11
8 9
22 40
8 36
314159265 358979323```

### 输出

```
1
12
4
11
14
57
31
671644785```

# 题解

## 作者：loveJY (赞：5)

用手画画几个pair就能找到一点点规律

我们选择的人的组合一定是如下样子:

$(1,AB),(AB,1)$

$(2,AB/2),(AB/2,2)$

$(3,AB/3),(AB/3,3)$

....

其中所有除法都是下取整,总共AB开根号对pair

也就是说,我们一个粗略的答案上界是$2*\sqrt {AB}$

然鹅,首先你会发现其中一定有一个是原来的人(A,B),答案-1

然后如果说这个AB是完全平方数的话,我们还会多算两遍,答案-2

同时如果说虽然不是完全平方数,但是开根后得到的数字x和$\lfloor \frac AB x \rfloor$是一个数的话,我们直接乘2也会算重

eg:50 -> 7*7<50

满足上述三点后精细实现一下即可

时间复杂度$O(T)$

code:
```cpp

#include<bits/stdc++.h>
#define int long long
using namespace std;
int t, A, B;

signed  main() {
	scanf("%lld", &t);
	while(t-- > 0) {
		scanf("%lld%lld", &A, &B);
		int u = sqrt(1ll * A * B);
		int v = A * B / u;
		if(u * v == A * B && v > u)--v;
		if(A > B)swap(A, B);
		int ans = 0;
		if(u == A && v == B)
			ans--;
		else if(u * v == A * B)
			ans -= 2;
		else if(v == u)
			ans--;
		ans += u * 2 - 1;
		printf("%lld\n", ans);
	}
	return 0;
}


```

---

## 作者：Krimson (赞：4)

鬼题……  

因为感觉另一篇题解不太正经（感觉是歪打正着刚好发现了规律？），便打算发一篇有证明的题解。  
前置知识:[霍耳定理](https://baike.baidu.com/item/%E9%9C%8D%E5%B0%94%E5%AE%9A%E7%90%86/3993873?fr=aladdin)  



------------

首先需要建立一个模型，有两排点，都是$[1,\infty]$，设第一排点为$a$,第二排点为$b$。  
将$a_i$向所有$a_ib_j<AB$的点$b_j$连一条边，原题目等价于在这张图上跑最大匹配。  
假设现在匹配的点在点集$S$中，要使其存在完美匹配的条件是$\forall i\in S,|S|\leq\lfloor\frac{AB-1}{i}\rfloor$  
可以发现，只要$i$是$S$中的最大值满足的时候，就一定满足了，即$S$一定是一个前缀的时候最优。  
假设这个前缀为$k$，那么有
$$
\begin{aligned}
&\forall i\leq k,k-i+1\leq\lfloor\frac{AB-1}{i}\rfloor\\
&ki-i^2+i<AB\\
&k<\frac{AB}{i}+i-1\\
\end{aligned}
$$  
这个是初中生都会的基本不等式，一般来说把$i= \sqrt{AB}$代入，可以得到  $k<2\sqrt{AB}-1$    
然而，$i$是一个正整数，这就比较麻烦了，大力分讨？  
这可是$OI$，为啥要干这种事情？  
直接暴力枚举$i\in[\sqrt{AB}-10,\sqrt{AB}+10]$的区间。  
由上得到了一种检验一个前缀$k$是否合法的方法，于是可以去二分这个$k$。  
同时，又因为$A$和$B$不能被计算在其中，最终答案也要把这个去掉。  
检验的时候要记得$k-i+1$中也要去掉$A$，$B$，$i$也不能代入$A,B$   


 _Code_ 
------------
```cpp
#include<bits/stdc++.h>
using namespace std;
#define il inline
#define ri register int
#define ll long long
#define ui unsigned int
il ll read(){
    bool f=true;ll x=0;
    register char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') f=false;ch=getchar();}
    while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    if(f) return x;
    return ~(--x);
}
il int read(char *s){
    int len=0;
    register char ch=getchar();
    while(ch==' '||ch=='\n') ch=getchar();
    while(ch!=' '&&ch!='\n'&&ch!=EOF) s[++len]=ch,ch=getchar();
    return len;
}
il void write(const ll &x){if(x>9) write(x/10);putchar(x%10+'0');}
il void print(const ll &x) {x<0?putchar('-'),write(~(x-1)):write(x);putchar('\n');}
il ll max(const ll &a,const ll &b){return a>b?a:b;}
il ll min(const ll &a,const ll &b){return a<b?a:b;}
ll a,b;
/*
xy>ik-i*i+i
*/
bool check(ll x,ll y,__int128 k){
    for(ll i=max(sqrt(x*y)-120,1);i<=min(sqrt(x*y)+120,k);++i){
        ll res=1;
        if(k>=y&&i<=y) res--;
        if(k>=x&&i<=x) res--;
        if(i==x||i==y) continue;
        if(x*y<=i*k-i*i+i*res) return false;
    }
    return true;
}
int main(){
    for(ri t=read();t;--t){
        a=read(),b=read();
        if(a>b) swap(a,b);
        ll l=1,r=1e18,m,ans;
        while(l<=r){
            m=(l+r)>>1;
            if(check(a,b,m)) ans=m,l=m+1;
            else r=m-1;
        }
        ll p=0;
        if(ans>=b) --p;
        if(ans>=a) --p;
        if(p!+0&&a==b) ++p;
        print(ans+p);
    }
    return 0;
}
```


---

## 作者：serene_analysis (赞：3)

若能有 $n$ 个人排名在你之前则一定能有 $n-1$ 个人排名在你之前，因此答案具有可二分性。

二分答案，则问题转为判定是否能有 $mid$ 个人排名在你之前。根据简单的贪心，这 $mid$ 个人的两项排名一定是除 $a,b$ 外最小的 $mid$ 个，否则将一个人的某项排名换得更小答案不会更劣。再明确一个结论，对于其中任意一个人，他的两项排名（这里的排名是指他在这 $mid$ 个人中的排名）之和为 $mid+1$，否则设 $x$ 的两项排名都小于 $y$ 的两项排名，任意交换二者的某项排名都能使此二者的贡献变优。设 $a \lt b$，则会出现三种情况，我们稍后来处理具体的计算：

+ $mid \lt a$，此时两项中 $mid$ 个人的排名分布都是 $[1,mid]$。
+ $a \leq mid \lt b$，此时第一项中排名分布是 $[1,a-1] \cup [a+1,mid+1]$，第二项仍然是 $[1,mid]$，根据我们的结论，排名的对应关系应该是 $[1,a-1]$ 对应 $[mid-a+2,mid]$ 和 $[a+1,mid+1]$ 对应 $[1,mid-a+1]$。
+ $mid \gt b$，此时二者被分为了 $[1,a-1] \cup [a+1,mid+1]$ 和 $[1,b-1] \cup [b+1,mid+1]$。再根据 $mid-a$ 和 $b-1$ 的大小关系分类讨论一下即可。

至于计算，注意到两个对应的区间大小是相同的，那么根据 $(a+1)(b-1)-ab=b-a-1$，则两项排名之积最大的那个人要么两项排名分别为左边区间的右端点和右边区间的左端点，要么两项排名相等或相差 $1$，根据上面的结论可以很简单地求出答案。

二分的判定就是判断一下这 $mid$ 个人中两项排名之积最大的是否大于 $a \times b$ 即可。

讲起来麻烦，实际上画个图很简单（我的代码中就有字符画），具体实现时可以利用一下两个区间大小相同的性质，用两个端点和区间长度中好算的两个去推另一个。

最后提醒一下，答案最大是 $2 \times 10^9 -2$ 左右。

```cpp
#include<algorithm>
#include<cstdio>
#include<vector>
typedef long long ll;
int q;
ll gans(ll l,ll r,ll inc){
	if(r<l+inc)return r*(l+inc);
	else{
		ll all=l+r+inc;
		if(all&1)return all/2*(all/2+1);
		else return all/2*all/2;
	}
}
bool can(ll gave,ll a,ll b){
	ll nmx=-1145141919810;
	if(gave<a)nmx=gans(1,gave,0);
	else if(gave>=b){
		gave++;
		if(gave-a>b-1)nmx=std::max({gans(1,b-1,gave-b+1),
			gans(a+1,gave-b+1,b-a),gans(1,a-1,gave-a+1)});
		else if(gave-a==b-1)nmx=std::max(
			gans(1,b-1,gave-b+1),gans(1,a-1,gave-a+1));
		else nmx=std::max({gans(1,gave-a,a),gans(gave-b+1,a-1,b-a),gans(1,gave-b,b)});
	}
	else nmx=std::max(gans(1,a-1,gave-a+1),gans(1,gave-a+1,a));
	return nmx<a*b;
}
signed main(){
//	freopen("test.in","r",stdin);
//	freopen("mine.out","w",stdout);
	scanf("%d",&q);
	for(int wc=1;wc<=q;wc++){
		ll a,b;
		scanf("%lld%lld",&a,&b);
		ll ef_lef=0,ef_rig=4e9;
		ll ef_ans=-1;
		if(a>b)std::swap(a,b);
		while(ef_lef<=ef_rig){
			ll ef_mid=(ef_lef+ef_rig)>>1;
			if(can(ef_mid,a,b))ef_ans=ef_mid,ef_lef=ef_mid+1;
			else ef_rig=ef_mid-1;
		}
		printf("%lld\n",ef_ans);
	}
	return 0;
}
/*
1
1000000000 1000000000
*/
/*
3 6 10
..#.......
.....#....
3 6 8
..#.....
.....#..
3 6 7
..#....
.....#.
3 6 4
..#..
....
*/
```

---

