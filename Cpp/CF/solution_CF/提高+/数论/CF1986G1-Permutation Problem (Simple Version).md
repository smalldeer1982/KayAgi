# Permutation Problem (Simple Version)

## 题目描述

This is a simple version of the problem. The only difference is that in this version $ n \leq 10^5 $ and the sum of $ n $ for all sets of input data does not exceed $ 10^5 $ .

You are given a permutation $ p $ of length $ n $ . Calculate the number of index pairs $ 1 \leq i < j \leq n $ such that $ p_i \cdot p_j $ is divisible by $ i \cdot j $ without remainder.

A permutation is a sequence of $ n $ integers, where each integer from $ 1 $ to $ n $ occurs exactly once. For example, $ [1] $ , $ [3,5,2,1,4] $ , $ [1,3,2] $ are permutations, while $ [2,3,2] $ , $ [4,3,1] $ , $ [0] $ are not.

## 说明/提示

In the first set of input data, there are no index pairs, as the size of the permutation is $ 1 $ .

In the second set of input data, there is one index pair $ (1, 2) $ and it is valid.

In the third set of input data, the index pair $ (1, 2) $ is valid.

In the fourth set of input data, the index pairs $ (1, 2) $ , $ (1, 5) $ , and $ (2, 5) $ are valid.

## 样例 #1

### 输入

```
6
1
1
2
1 2
3
2 3 1
5
2 4 1 3 5
12
8 9 7 12 1 10 6 3 2 4 11 5
15
1 2 4 6 8 10 12 14 3 9 15 5 7 11 13```

### 输出

```
0
1
1
3
9
3```

# 题解

## 作者：TTpandaS (赞：11)

令 $x_i=i,y_i=p_i$，那么符合要求的 $i,j$ 满足 $x_i  x_j  \mid y_i y_j$。

将 $x_i$ 和 $y_i$ 都除以 $\gcd$，那么对条件 $x_i  x_j  \mid y_i y_j$ 不会产生影响， $x_i$ 和 $y_i$ 都将互质，那么只需要判断 $x_i  \mid y_j \wedge x_j \mid y_i$ 即可。

然后枚举 $i$，寻找 $j<i$ 的满足条件的 $j$ 的数量。

对于 $x_i> \sqrt n $ 的情况，直接枚举 $y_j$。在之前用一个 vector 记录每个 $y_j$ 对应了哪些 $x_j$，然后枚举判断即可。

对于 $x_i< \sqrt n $ 的情况，直接枚举 $x_j$，即找 $y_i$ 的因数，先质因数分解，在搜索即可。得到每一个因数后，在之前再用一个 vector 记录每个 $x_j$ 对应了哪些 $y_j$，然后枚举判断即可。

时间复杂度看上去是 $O(n^2)$ 的，但实际上是 $O(\text{稳过})$，倒数第二劣解。

---

## 作者：lfxxx (赞：4)

考虑对于每个 $\frac{p_i}{i}$ 约分后变为 $\frac{a}{b}$，对于两组 $\frac{a_1}{b_1},\frac{a_2}{b_2}$ 相乘后为整数等价于 $b_1|a_2,b_2|a_1$，因为 $a_1,b_1$ 与 $a_2,b_2$ 都是互质数对。

考虑同时处理 $b_1$ 相同的所有 $a_1$，我们枚举 $b_1$ 的所有倍数作为 $a_2$，假若不约分由于 $a_2$ 是排列，因此每对 $a_2,b_2$ 对被枚举的次数之和是 $O(n \log n)$，但是注意到约分后因数数量减少，因此每对 $a_2,b_2$ 被枚举的次数之和最多还是 $O(n \log n)$，将对应的 $b_2$ 加到桶中后，考虑枚举 $b_1$ 对应的所有 $a_1$ 的因数 $b_2$，不约分枚举总量是 $O(n \log n)$，而约分后因数数量减少因此枚举总量还是不超过 $O(n \log n)$，枚举时直接在桶中查询一下存在的 $b_2$ 的数量即可。

总时间复杂度 $O(n \log n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 5e5+114;
vector<int> d[maxn];
long long ans;
int cnt[maxn];
int n,p[maxn];
vector<int> A[maxn];//A[i] b=i 的所有 a
vector<int> B[maxn];//B[i] a=i 的所有 b;
void work(){
    ans=0;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>p[i];
        int a=p[i]/__gcd(p[i],i),b=i/__gcd(p[i],i);
        A[b].push_back(a);
        B[a].push_back(b);
        if(b==1) ans--;//自己不能与自己贡献
    }
    for(int b=1;b<=n;b++){
        // a/b x/y
        for(int x=b;x<=n;x+=b){
            for(int y:B[x]) cnt[y]++;
        }
        for(int a:A[b]){
            for(int D:d[a]) ans+=cnt[D];
        }
        for(int x=b;x<=n;x+=b){
            for(int y:B[x]) cnt[y]--;
        }
    }
    cout<<(ans/2)<<'\n';
    for(int i=1;i<=n;i++) A[i].clear(),B[i].clear();
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    for(int i=1;i<=500000;i++){
        for(int j=i;j<=500000;j+=i) d[j].push_back(i);
    }
    int T;
    cin>>T;
    while(T--) work();
    return 0;
}
```

---

## 作者：_Cheems (赞：4)

同 hard versation 的做法。

直接统计是困难的，考虑简化条件，令 $p_i,i$ 除以它们的最大公因数，分别得到 $a_i,b_i$，这样的好处是 $a,b$ 互质。因此，$\frac{a_ia_j}{b_ib_j}$ 为整数当且仅当 $b_j\mid a_i$ 且 $b_i\mid a_j$。

记 $d(n)$ 为 $n$ 的因数个数。显然 $\sum d(b_i)=\sum d(p_i)=O(n\ln n)$，由于 $a_i\mid p_i$，所以也有 $\sum d(a_i)=O(n\ln n)$。利用这一点统计答案。

具体而言，枚举值域。枚举数对 $b\mid a$，然后用桶 $buc$ 统计 $a_j=a$ 的 $b_j$ 个数；最后对 $b_i=b$ 的 $a_i$ 大力枚举其因数 $d$，贡献就是 $buc_d$。 

上述过程可以视为两部分，由先前的讨论，每一部分的复杂度都是 $O(n\ln n)$ 的，所以总复杂度 $O(n\ln n)$。注意下循环顺序不然复杂度会退化。
#### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 5e5 + 5;
int T, n, a[N], b[N], buc[N];
long long ans;
vector<int> x[N], y[N], ys[N]; 

signed main(){
	cin >> T;
	while(T--){
		scanf("%d", &n);
		ans = 0;
		for(int i = 1; i <= n; ++i) x[i].clear(), y[i].clear(), ys[i].clear();
		for(int i = 1; i <= n; ++i){
			scanf("%d", &a[i]), b[i] = i;
			int d = __gcd(a[i], b[i]);	a[i] /= d, b[i] /= d;		
			x[b[i]].push_back(a[i]), y[a[i]].push_back(b[i]); 
			if(a[i] % b[i] == 0) --ans;
		}
		for(int i = 1; i <= n; ++i)
			for(int j = i; j <= n; j += i) ys[j].push_back(i); //预处理因数 
		for(int i = 1; i <= n; ++i){
			for(int j = i; j <= n; j += i)
					for(auto _s : y[j]) ++buc[_s];
			for(auto s : x[i])	
				for(auto _s : ys[s]) ans += buc[_s];
			for(int j = i; j <= n; j += i)
				for(auto _s : y[j]) --buc[_s];
		}
		printf("%lld\n", ans / 2);
	}
	return 0;
}
```

---

## 作者：Targanzqq (赞：2)

### 思路：
如果这个题我们暴力统计，那么时间复杂度是 $O(n^2)$ 的，其中包含着很多无法产生贡献的情况。我们知道，优化时间复杂度相当于尽可能少地枚举到这些情况，所以我们要从条件本身找可以减少枚举数量的性质。

当 $ij\mid p_ip_j$ 时，设 $g_i=\gcd(i,p_i)$，$g_j=\gcd(j,p_j)$，则有 $\frac{ij}{g_ig_j}\mid \frac{p_ip_j}{g_ig_j}$。设 $\frac{i}{g_i}=a_i$，$\frac{j}{g_j}=a_j$，$\frac{p_i}{g_i}=b_i$，$\frac{p_j}{g_j}=b_j$，则有 $a_ia_j\mid b_ib_j$。

而因为 $a_i$ 与 $b_i$ 互质，$a_j$ 与 $b_j$ 互质，所以 $b_i\mid a_j$，$b_j\mid a_i$。我们可以凭借这个性质来进行优化。

我们开一个 map，它的编号表示分母，索引表示分子。我们称**一组**为一个相对应的分母和分子。我们每次枚举到一个 $i$ 时，我们要让答案加上同时满足分母是 $a_i$ 的倍数且分子是 $b_i$ 的约数的组的贡献。这样我们可以从**索引**里找 $a_i$ 的倍数。而我们想找 $b_i$ 的约数的贡献，则需要枚举 $b_i$ 的约数，从**编号**里面去找。

如何让 $a_i$ 的倍数的贡献加到索引为 $a_i$ 且满足条件的组中？我们可以在修改的时候进行操作。对于所有**我们要找的情况**里，假设其中一组是 $k$，那么我们让所有索引为 $b_k$ 的**约数**的组的权值加上 $1$，这样我们后面找到的 $a_i$ 的倍数的贡献就一定包含在索引为 $a_i$ 且满足条件的组中了。

**多测别忘了清空**，清空的话就把上面赋过值的部分重新赋为 $0$ 即可，尽量把原过程在进行一边（也有可能有其他好方法但我不知道）。

源代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

int t,n,p[100005];
map<int,int> mp[100005]; 
vector<int> fr[100005];

void solve(){
	int ans=0;
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j+=i){
			fr[j].push_back(i);
		}
	}
	for(int i=1;i<=n;i++){
		int g=__gcd(i,p[i]);
		int i2=i/g,c=p[i]/g;//这里的i2就是分子，c就是分母
		for(int j:fr[c]){
			ans+=mp[j][i2];//加上编号是分母的约数的组的贡献
		}
		for(int j:fr[c]){
			mp[i2][j]++;//让索引为当前数的约数的组+1，这样后面满足条件的组一定也包括ai倍数的贡献
		}
	}
	for(int i=1;i<=n;i++){
		int g=__gcd(i,p[i]);
		int i2=i/g,c=p[i]/g;
		for(auto j:fr[c]){
			mp[i2][j]=0;
		}
	} 
	for(int i=1;i<=n;i++){
		fr[i].clear();
	}//别忘了清空
	cout<<ans<<endl;
} 

signed main(){
	ios::sync_with_stdio(false);
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>p[i];
		}
		solve();
	}
}

```

---

