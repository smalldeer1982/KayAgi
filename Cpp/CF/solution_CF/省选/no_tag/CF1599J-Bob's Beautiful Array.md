# Bob's Beautiful Array

## 题目描述

Bob really likes playing with arrays of numbers. That's why for his birthday, his friends bought him a really interesting machine – an array beautifier.

The array beautifier takes an array $ A $ consisting of $ N $ integers, and it outputs a new array $ B $ of length N that it constructed based on the array given to it. The array beautifier constructs the new array in the following way: it takes two numbers at different indices from the original array and writes their sum to the end of the new array. It does this step $ N $ times - resulting in an output array of length $ N $ . During this process, the machine can take the same index multiple times in different steps.

Bob was very excited about the gift that his friends gave him, so he put his favorite array in the machine. However, when the machine finished, Bob was not happy with the resulting array. He misses his favorite array very much, and hopes to get it back.

Given the array that the machine outputted, help Bob find an array that could be the original array that he put in the machine. Sometimes the machine makes mistakes, so it is possible that no appropriate input array exists for the array it has outputted. In such case, let Bob know that his array is forever lost.

## 样例 #1

### 输入

```
2
5 5```

### 输出

```
YES
2 3```

## 样例 #2

### 输入

```
3
1 2 3```

### 输出

```
YES
0 1 2```

## 样例 #3

### 输入

```
3
2 4 5```

### 输出

```
NO```

## 样例 #4

### 输入

```
4
1 3 5 7```

### 输出

```
YES
6 -3 4 1```

# 题解

## 作者：lnxxqz (赞：4)

以下称题目中给出的序列为“原序列”。

首先有一个显而易见的结论，若原序列存在相同的数，那么直接可以得出：相同的数其中一个变成 $0$，剩下的数不变就是一种答案。

我们发现，对于原序列 $a$ 我们只需要找出其任意一个子序列 $t$ 对应的答案序列即可。找到之后不在 $t$ 内的其他数 $a_i$ 可由 $t$ 内的任意一个数 $x$ 和额外的一个数 $a_i-x$ 得出。

对于一个长度为 $3$ 的序列 $[A,B,C]$，令答案序列中存在一个数 $X$，如果表示出 $A,B$ 那么可以计算出另两个数为 $A-X,B-A+X$，这也就是说要是能表示出 $C$ 就需要满足 $X+(B-A+X)=C$ 即 $X=\frac{A-B+C}{2}$。这就说明若 $A,B,C$ 之和为偶数就可以表示出一个合法的答案序列。

这就有两种可能：均为偶数或者二奇一偶。

当原序列中存在偶数时：
- $N\geq4$ 时总存在解，因为总能满足以上条件之一，只要找到三个偶数或者两个奇数一个偶数就能表示出答案。
- $N\leq3$ 时只需要暴力判断，以及确定是否存在相同的数即可。

否则，我们现在的序列中全部是奇数。

这时我们尝试去寻找一个可能的子序列，长度为奇数的子序列不可能成为目标，因为类似上面长度为 $3$ 的序列，他需要元素之和为偶数，奇数个奇数之和为奇数，所以不可能。

于是我们假设有一个长度为 $2s$ 的序列 $[a_1,a_2,a_3,\cdots,a_{2s}]$，类比上面的做法，令答案序列中存在数 $X$，可以表示出其他数为

$$a_1-X,a_2-a_1+X,a_3-a_2+a_1-X,\cdots,(a_{2s-1}-a_{2s-2}\cdots +a_1-X)$$

需要满足 $X+(a_{2s-1}-a_{2s-2}\cdots +a_1-X)=a_{2s}$，$X$ 被消掉了，得出 

$$\sum_{i=1}^{s} a_{2i-1} = \sum_{i=1}^{s} a_{2i}$$

也就是说我们需要在原序列中找出任意两个不完全相同的集合，满足大小和元素和均相等（若有重复元素就同时删去）。

我们发现，对于大小为 $S$ 的子序列，选法有 $C_N^S$ 种，取值的个数最多有 $10^6 \times S$ 种，在 $S \geq 28$ 时，后者小于前者，根据鸽巢原理，一定会出现取值相同的子序列，于是可以得出做法：

- $N \geq 28$，直接 $dfs$ 每一种大小为 $28$ 的集合，寻找取值相同的集合。
- $N < 28$，暴力状压枚举每种选法，查看是否存在大小和元素和均相同的集合。

可以用哈希表来实现。
```cpp
using namespace std;
# include<bits/stdc++.h>
# include<bits/extc++.h>
int N;
constexpr int maxn(1002);
int a[maxn];
void work1(){
	if(N==2){
		if(a[1]==a[2]){
			printf("YES\n0 %d\n",a[1]);
			return;
		}else{
			printf("NO\n");
			return;
		}
	}
	if(N==3){
		if(a[1]==a[2]){
			printf("YES\n0 %d %d\n",a[2],a[3]);
			return;
		}else if(a[2]==a[3]){
			printf("YES\n0 %d %d\n",a[1],a[3]);
			return;
		}
	}
	std::vector<int>o,j;
	for(int i=1;i<=N;i++) if(a[i]%2==0) o.push_back(i);else j.push_back(i);
	if(N==3&&j.size()<2){
		puts("NO");
		return;
	}
	int A,B,C;
	if(o.size()>=3){
		A=o[0],B=o[1],C=o[2];
	}else A=o[0],B=j[0],C=j[1];
	int X=(a[A]-a[B]+a[C])>>1;
	puts("YES");
	printf("%d %d %d ",X,a[A]-X,a[B]-a[A]+X);
	for(int i=1;i<=N;i++){
		if(i==A||i==B||i==C) continue;
		printf("%d ",a[i]-X);
	}
}
struct aqua{
	std::vector<int>v;
	aqua(){};
	aqua(std::vector<int>t){v=t;}
};
void print(std::vector<int>A,std::vector<int>B){
	static bool visa[maxn],visb[maxn];
	for(auto x:A) visa[x]=1;
	for(auto x:B) visb[x]=1;
	A.clear(),B.clear();
	for(int i=1;i<=N;i++){
		if(visa[i]^visb[i]){
			if(visa[i]) A.push_back(i);
			else B.push_back(i);
		}
	}
	int X=0;
	puts("YES");
	for(int i=0;i<A.size();i++){
		printf("%d ",X);
		X=a[A[i]]-X;
		printf("%d ",X);
		X=a[B[i]]-X;
	}
	for(int i=1;i<=N;i++){
		if(visa[i]^visb[i]) continue;
		printf("%d ",a[i]);
	}
}
void work2(){
	__gnu_pbds::gp_hash_table<int,int>h[30];
	for(int i=1;i<1<<N;i++){
		int g=__builtin_popcount(i);
		int s=0;
		for(int j=1;j<=N;j++){
			if((i>>(j-1))&1) s+=a[j];
		}
		if(h[g][s]){
			int x=i,y=h[g][s];
			std::vector<int>a,b;
			for(int j=1;j<=N;j++){
				if((x>>(j-1))&1) a.push_back(j);
				if((y>>(j-1))&1) b.push_back(j);
			}
			print(a,b);
			return;
		}
		h[g][s]=i;
	}
	puts("NO");
}
std::vector<int>xl;
__gnu_pbds::gp_hash_table<int,aqua>hs;
void dfs(int d,int now,int z){
	if(d==28){
		if(!hs[z].v.empty()){
			print(hs[z].v,xl);
			exit(0);
		}
		hs[z]=aqua(xl);
		return;
	}
	for(int i=now;i<=N;i++)
		xl[d]=i,dfs(d+1,i+1,z+a[i]);
}
void work3(){
	xl.resize(28);
	dfs(0,1,0);
	puts("NO");
}
int main(){
	std::cin>>N;
	bool fg=0;
	for(int i=1;i<=N;i++) scanf("%d",&a[i]),fg|=a[i]%2==0;
	std::sort(a+1,a+N+1);
	if(fg){
		work1();
		return 0;
	}
	if(N<=28) work2();
	else work3();
   return 0;
}
```


---

## 作者：Demeanor_Roy (赞：2)

- 好题。

---

如果 $a_i + a_j$ 可以构成 $b$ 中某个元素，我们就将 $i$ 和 $j$ 连一条边。显然这样会构成一棵基环树。

不难发现本质上我们就是要找到一个合法的环。

### case1

当环长为 $2$，即 $a$ 中有俩个数相同时，构造是简单的。

### case2

注意到环长为 $3$ 时的一个特殊构造，即：假设 $a+b=w_1,a+c=w_2,b+c=w_3$，此时令 $d=\dfrac{w_1+w_2+w_3}{2}$，我们有：$c=d-w_1,b=d-w_2,a=d-w_3$。不难发现我们的构造**只要求** $d$ 是一个偶数，也就是说只要 $w_1,w_2,w_3$ 中奇数个数为偶数就能应用此构造。

### case3

考察什么时候不能使用上面两种构造，发现此时序列要么全是奇数，要么两偶一奇，而后者已然无解，我们只用考虑前者。

**结论：$a$ 中全是奇数时环长为偶数**

这是因为奇数只能由一奇一偶相加得到，故必须连成偶环。

**结论：对于偶环，我们可以钦定其中一个元素为 $0$。**

这是因为我们可以通过给奇数位置加一，偶数位置减一的方式调整一个合法方案满足该条件。

于是此时问题转化为：找到 $a$ 中两个大小相等的不交子集，使它们子集和相等。

根据鸽巢原理，因为 ${27 \choose 13} >13 \times 10^6$，故当 $n \geq 27$ 时一定有解，我们暴力枚举前 $\min(n,27)$ 个数的合法子集即可。如果想做到更快，可以考虑折半搜索。

---

## 作者：yxzy4615 (赞：2)

## 题意简述
给定序列 $a_1,a_2,\dots,a_n$，求是否存在长度为 $n$ 的序列 $b_1,b_2,\dots,b_n$，使得 $\forall k\in[1,n],\exists i,j\in[1,n],i \neq j,b_i+b_j=a_k$，若存在则构造方案。

## 思路分析

首先，我们考虑如何转化题意，毕竟原题意的对应形式很不舒服，完全没法使用“钦定”。

对于一个长为 $n$ 的序列 $A$ ，如果让你使用长为 $n+1$ 的 $B$ 去满足上述条件十分简单。我们任意钦定一个数，剩下的在已经求出的数中任选其一，用对应值相减即可。然后如果把序列 $B$ 的值作为点权，发现你可以构建一颗树，满足边权为两点点权和，且与序列 $A$ 的值一一对应。

所以我们可以考虑，构建一个基环树森林，又因为在上述条件下，第一个数的选择不影响成立情况，于是我们只要构造一颗基环树即可。

接下来就是对于环长进行讨论：

如果环长为奇数，那么对于环上的值是可解的，如果边权为奇数，两点奇偶性不同，所以环上奇数个数必为偶数，那必定存在偶数边，即序列 $A$ 中存在偶数且奇数个数 $\geq 2$ 或者存在三个以上的偶数，由于基环树形态是自定义的，所以我们就可以仅使用长为 $3$ 的环即可。

如果环长为偶数，记环长为 $L$ ，边权为 $c_1,c_2,\dots,c_L$，那么必定存在

$$ \sum^{L/2}_{i=1}c_{2i-1}=\sum^{L/2}_{i=1}c_{2i}$$

也就是在序列 $A$ 中选择两个大小相同的不交子集，使得两个子集的元素和相等。而 $C_{27}^{13}=20058300>13\times 10^6 $，$C_{26}^{13}=10,400,600<13\times 10^6$ ，也就是说，对于任意 $27$ 个数，一定存在一组合法的环，而 $26$ 个数则不一定存在。

所以我们可以只考虑解决数据范围为 $n\leq 27$ 的问题。

暴力做法时间复杂度为 $C_n^{\lfloor\frac{n}{2}\rfloor}$，可以接受。实现可以使用状态压缩或哈希表。

## $\text{code:}$

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1010,M=N*N;
int n,a[N],pd,m,sz,b[N];
unordered_map<int,long long>mp;
long long ansx,ansy;
void dfs(int x,int pr,long long U,int s){
    if(x==sz+1){
        if(mp.count(s)) ansx=mp[s],ansy=U;
        else mp[s]=U;
        return ;
    }
    for(int i=pr+1;i<=m;i++){
        dfs(x+1,i,U|(1ll<<(i-1)),s+a[i]);
        if(ansx||ansy) return;
    }
}
int main(){
    cin>>n;pd=0;
    for(int i=1;i<=n;i++) cin>>a[i],pd+=(a[i]&1);
    sort(a+1,a+1+n);pd=n-pd;
    if(pd){
        int A,B,C,S,X;A=B=C=0;
        if(pd<=2){
            for(int i=1;i<=n;i++){
                if(a[i]&1) (!B?B:C)=i;
                else A=i;
            }
            if(!C) return puts("NO"),0;
        }
        else{
            for(int i=1;i<=n;i++){
                if(a[i]&1) continue;
                if(!A) A=i;
                else (!B?B:C)=i;
            }
        }
        puts("YES");S=a[A]+a[B]+a[C];X=S/2-a[A];
        for(int i=1;i<=n;i++){
            if(i==A||i==B||i==C) printf("%d ",S/2-a[i]);
            else printf("%d ",a[i]-X);
        }return 0;
    }
    m=min(n,27),sz=m/2;
    dfs(1,0,0,0);
    if(ansx||ansy){
        long long c=ansx&ansy;int L=0;
        ansx^=c,ansy^=c;c=ansx|ansy;
        for(int i=1;i<=m;i++) if(ansx&(1ll<<(i-1))) b[++L]=a[i];
        for(int i=1;i<=m;i++) if(ansy&(1ll<<(i-1))) b[++L]=a[i];
        puts("YES");
        for(int i=1;i<=m;i++) if(!(c&(1<<(i-1)))) printf("%d ",a[i]);
        for(int i=m+1;i<=n;i++) printf("%d ",a[i]);
        for(int i=1,j=L/2+1,x=0,y=0;j<=L;i++,j++){
            if(i==1) x=0,y=b[j]-x;
            else x=b[i]-y,y=b[j]-x;
            printf("%d %d ",x,y);
        }
    }
    else puts("NO");
    return 0;
}
```


---

## 作者：BreakPlus (赞：1)

+ 考虑对于 $a_1+a_2, a_2+a_3, \cdots, a_{n-1}+a_n$ 凑成 $b$ 中的 $n-1$ 个数。将 $b$ 重排，令 $a_i+a_{i+1} = b_i$。

+ 但 $b_n$ 还没有出现过，所以我们要找出两数之和为 $b_n$。

+ 将 $a$ 序列用 $b$ 来表示：$a_1, b_1-a_1, b_2-b_1+a_1,b_3-b_2+b_1-a_1, \cdots$。

----

+ 考虑奇偶不同的 $i,j$，如 $i=1,j=4$，相加 $a_i,a_j$，得到 $b_3-b_2+b_1$。若它俩是我们找的数，则 $b_3-b_2+b_1-b_n=0$。推广发现，我们需要在 $b$ 中找两个不交的大小相等的集合，使得两个集合的元素和相等.


+ 我们发现当 $n \ge 27$，${27 \choose 13} > 13 \times 10^6$，意味着我们必然能找到两个集合，那么 $n>27$ 时只管前 $27$ 个数就行了。

+ 但是直接枚举 $\mathcal{O}(n2^n)$ 不能允许。此时我们惊奇的发现，只要枚举大小为 $\lfloor \dfrac{n}{2} \rfloor$的集合，所有集合其实都能被枚举到，因为我们有一个去重的过程，大小 $\le \lfloor \dfrac{n}{2} \rfloor$ 的都能被枚举到。

+ 那么我们枚举的子集数就与值域同阶了。

-----

+ 考虑奇偶相同的 $i,j$，如 $i=2,j=4$，相加 $a_i,a_j$，得到 $b_3-b_2+2b_1-2a_1=b_n$。

+ 由于此时带有 $a_1$ 项，我们一定可以将 $a_1$ 解出来。但是为了保证 $a_1$ 是整数，我们还需要保证 $b_3+b_2+b_n \equiv 0 \pmod 2$。

+ 我们不再推广问题，尝试直接找出三个数相加后 $\text{mod} \ 2$ 为 $0$。事实上，只要找出奇数个数相加后 $\text{mod} \ 2$ 为 $0$ 也符合要求。

+ 当 $n=3$ 时，没有选择，直接判断。

+ 当 $n\ge 4$ 时，若没有偶数，那么选奇数个数相加必然为奇数，无解；若偶数的数量达到三个，那么可以选三个偶数；若 $0$ 和 $1$ 各有两个，可以选择一个偶数，两个奇数。


------

综上，我们完成了所有的讨论。作为一个 *2600 不一定难度够格，但是值得一做。


---

## 作者：Mashu77 (赞：0)

简单分析，如果 
$b$
 中有两个元素相同则肯定可以，如果存在三个数 
$x
,
y
,
z$
 满足 
$x
+
y
−
z$
 是偶数则肯定可以。于是接下来只考虑所有数都是奇数的情况。

每个 
$a_
i$
 对应一个点，$b_
i$
 对应一条边，则构成一个基环树。对于不在环上的部分，如果不是一条链，则将一个叶子接到另一个叶子下面，显然答案依然存在。于是形态变成了一个环接一条链。也就是一条链加一条连接一个端点的边。

设 
$a_1=x$，则 
$a_2=b_1−x,a_3=b_2−
b_1+x,a_4=
b_
3
−
b_
2
+
b_
1
−
x,…$
注意此时 
b
 并非输入的顺序。此时仅 
$b_
n$
 未满足。根据上述的分析，$b
_n$
 由 
$a_
1$
 与一个 
$a_
i$
 相加得到。由于所有 
$b$
 都是奇数，显然 
$i$
 需要为偶数。则问题转化为在 
$b$
 中找到两个长度相等，和相等的子序列。

由鸽巢原理，$(
\dfrac{n}
{n
/
2}
)>
10^
6
×
n^
2$
 时一定存在。所以 
$n>
27$
 时在前 
$27$
 个中找即可。设 
$m=
\min
(
n
,
27
)$，复杂度 
$O
(
m
2^
m
)$。

---

