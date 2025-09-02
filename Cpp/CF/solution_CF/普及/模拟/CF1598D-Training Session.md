# Training Session

## 题目描述

Monocarp is the coach of the Berland State University programming teams. He decided to compose a problemset for a training session for his teams.

Monocarp has $ n $ problems that none of his students have seen yet. The $ i $ -th problem has a topic $ a_i $ (an integer from $ 1 $ to $ n $ ) and a difficulty $ b_i $ (an integer from $ 1 $ to $ n $ ). All problems are different, that is, there are no two tasks that have the same topic and difficulty at the same time.

Monocarp decided to select exactly $ 3 $ problems from $ n $ problems for the problemset. The problems should satisfy at least one of two conditions (possibly, both):

- the topics of all three selected problems are different;
- the difficulties of all three selected problems are different.

Your task is to determine the number of ways to select three problems for the problemset.

## 说明/提示

In the first example, you can take the following sets of three problems:

- problems $ 1 $ , $ 2 $ , $ 4 $ ;
- problems $ 1 $ , $ 3 $ , $ 4 $ ;
- problems $ 2 $ , $ 3 $ , $ 4 $ .

Thus, the number of ways is equal to three.

## 样例 #1

### 输入

```
2
4
2 4
3 4
2 1
1 3
5
1 5
2 4
3 3
4 2
5 1```

### 输出

```
3
10```

# 题解

## 作者：Wuyanru (赞：9)

翻译：现有 $ n $ 道题，每道题有一个主题 $ a_i $ 和一个难度 $ b_i $。现在要从其中选出三道题，使得他们满足以下条件的**任意一条**：

1.  这三道题的主题互不相同；

2.  这三道题的难度互不相同。

求出合法的方案数，题目保证不存在两道题，使得他们主题与难度都一样。

由于上述两个条件之间是或的关系，也就是说一个合法的选择方案只需要满足任意一个条件就可以，这样很不好想，我们考虑算出不合法的方案总数，在用总方案数减去就可以了。

总数很好算：从 $ n $ 个数中选出三个数，共有 $ C_n^3 $ 种方案，也就是 $ \dfrac{n\left(n-1\right)\left(n-2\right)}{6} $ 种。

根据题意，我们可以知道不满足的方案必然**同时满足**以下两个条件：

1.  三道题中有至少两道题主体一致；

2.  三道题中有至少两道题难度一致。

由于题目中已经告诉我们，不存在两道题主题与难度都相等，所以两个条件转化为：

1.  三道题中有两道题主体一致；

2.  三道题中有两道题难度一致。

~~虽然感觉没有什么变化，但是下面这两条显然更清晰。~~

现在，我们不妨将一道题看作二维平面上的一个点，其中第 $ i $ 道题的坐标为 $ \left(a_i,b_i\right) $。

再次转化不合法方案的条件：

1.  三个点中有两个点横坐标一致；

2.  三个点中有两个点纵坐标一致。

通俗一点说，这三个点在二维平面上组成了一个 L 形（当然，这个 L 形也有可能是旋转过的）。

那么，我们不妨枚举这个 L 形上拐弯处那个点，这样就可以求出不合法的方案数了。

AC 代码：

```
#include<bits/stdc++.h>
using namespace std;
inline int read()//我爱快读
{
	int s=0,w=1;
	char ch;
	while((ch=getchar())>'9'||ch<'0')
		if(ch=='-')
			w=-1;
	while(ch>='0'&&ch<='9')
	{
		s=s*10+ch-'0';
		ch=getchar();
	}
	return s*w;
}
int numa[200001];//numa[i]表示横坐标为i的点的个数
int numb[200001];//numb[i]表示纵坐标为i的点的个数
int a[200001];//点的横坐标/题目主题
int b[200001];//点的纵坐标/题目难度
int n;
signed main()
{
	int t=read();
	while(t--)
	{
		long long ans=0;
		n=read();
		for(int i=1;i<=n;i++)
			numa[i]=numb[i]=0;//多组数据记得清空
		ans=(long long)n*(n-1)*(n-2)/6;//n是int类型，注意相乘要开long long
		for(int i=1;i<=n;i++)
		{
			a[i]=read(),numa[a[i]]++;
			b[i]=read(),numb[b[i]]++;
		}
		for(int i=1;i<=n;i++)
			ans-=(long long)(numa[a[i]]-1)*(numb[b[i]]-1);//减去的1是拐弯点自己
		printf("%lld\n",ans);
	}
	return 0;
}
```
感谢观看！

---

## 作者：lgx57 (赞：2)

~~做题时难得看到的一道水题。~~

首先，我们容易知道，从 $n$ 个中任选 $3$ 个的方法数为：
$$ C_{n}^{3}= \frac{n(n-1)(n-2)}{6}$$

然后再考虑题目要求。要求满足 $a_{i}$ 或 $b_{i}$ 至少有一个两两不同，只需要在所有的方案数中，去除 $a_{i}$ 与 $b_{i}$ 都相同的情况即可。

于是可以开两个桶 $mapa,mapb$。分别存下每个数出现的次数。最后枚举 $1\sim n$ 去除相同情况。

另外，注意**开 long long**！

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
void fio(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
}
const int N=2e5+5;
map<int,int> mapa;
map<int,int> mapb;
int a[N],b[N];
signed main(){
	fio();
	int t;
	cin>>t;
	while (t--){
		int n;
		cin>>n;
		mapa.clear();
		mapb.clear();//多测要清空。
		int ans=n*(n-1)*(n-2)/6;//总方案数
		for (int i=1;i<=n;i++){
			cin>>a[i]>>b[i];
			mapa[a[i]]++;
			mapb[b[i]]++;
		}
		for (int i=1;i<=n;i++){
			ans-=(mapa[a[i]]-1)*(mapb[b[i]]-1);//去除 a[i] 与 b[i] 都相同的情况。
		}
		cout<<ans<<endl;
	}
	return 0;
}

```

---

## 作者：heyZZZ (赞：1)

题目翻译：

给定 $n$ 个互不相同二元组，现在要从其中选出三个二元组，使得这三个二元组的的前一项互不相同或后一项互不相同。求有几种方案。

思路：

正难则反，先算总数：有 $\Large\frac{n \times (n-1) \times (n-2)}{6}$ 种情况。

不满足的情况是没有一个二元组与另一个二元组元素两两不相同（同一个元素）。

也就是就是一个二元组与另一个二元组元素至少一个相同（也是同一个元素）。

考虑用桶记录，$x_i$ 代表 $a_i$ 的出现个数，$y_i$ 代表 $b_i$ 的出现个数。

第一组固定，第二组有 $x_{a_i}-1$ 种，第三组有 $y_{b_i}-1$ 种。

一共有 $(x_{a_i}-1) \times (y_{b_i}-1)$。

代码楼上楼下都已经写的很明白了，我就不在赘述了。

---

## 作者：zhangqiuyanAFOon2024 (赞：1)

### 思路
超级大水题。
 
读题，我们要求符合条件的个数。

显然，这道题可以用总数减去不符合的数量。

不符合的也就是没有一个二元组与另一个二元组元素两两不相同。

换句话说，就是一个二元组与另一个二元组元素至少一个相同。

我们假设第一组固定，为 $a_i,b_i$。

那么我们假设第二组与第一组的 $a_i$ 相同，那么第二组有 $sa_{a_i}-1$ 种取法。

同理，第三组有 $sb_{b_i}-1$ 种。

即共有 $(sb_{b_i}-1)\times(sa_{a_i}-1)$ 种。

减去即可。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int a[N],b[N],sa[N],sb[N];
void solve(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) sa[i]=sb[i]=0;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>b[i];
		sa[a[i]]++,sb[b[i]]++;
	}
	int ans=n*(n-1)*(n-2)/6;//总数
	for(int i=1;i<=n;i++) ans-=(sa[a[i]]-1)*(sb[b[i]]-1);//减
	cout<<ans<<endl;
}
signed main(){	
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int T;
	cin>>T;
	while(T--) solve();
	return 0;
}
```

完结撒花！

---

## 作者：luan341502 (赞：1)

难得的瞬秒题。

首先可以发现总共有 $C^{3}_{n}$ 种选法。

对于每个二元组 $(a_i,b_i)$，我们考虑哪些是不能选入答案的。

对于一个二元组 $(a_j,b_j)$，若 $a_i=a_j$ 或 $b_i=b_j$ 一定不能被选入。

此时问题已经变得很简单，由于二元组互不相同，直接统计除 $i$ 外的所有 $a_i$，$b_i$ 数量，再根据乘法原理相乘即可。

**注意开 long long。**

```cpp
#include<bits/stdc++.h>
using namespace std;
int tt;
int n,a[200005],b[200005];
int ta[200005],tb[200005];
void solve(){
	cin>>n;
	for(int i=1;i<=n;i++) ta[i]=tb[i]=0;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>b[i];
		ta[a[i]]++,tb[b[i]]++;
	}
	long long ans=1ll*n*(n-1)*(n-2)/6;
	for(int i=1;i<=n;i++) ans-=1ll*(ta[a[i]]-1)*(tb[b[i]]-1);
	cout<<ans<<"\n";
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>tt;while(tt--) solve();
	return 0;
}
```


---

## 作者：pengyule (赞：1)

**标签** 补集思想，组合计数

**解法** 考虑问题的对立面，就是选出来的三组是这样的格式：选出来的 $(a_1,b_1),(a_2,b_2),(a_3,b_3)$ 恰好有一组 $a$ 相同、一组 $b$ 相同。这个怎么求？一个形象的思考方式是将每一个二元组 $(a_i,b_i)$ 看做 $n+n$ 的二分图中由左边的 $a_i$ 节点连向右边的 $b_i$ 节点的一条无向边，则所求的就是所有长度为 $3$ 的链的条数。为方便叙述，我们记这三条边为 $(e_1\Leftrightarrow  e_2\Leftrightarrow e_3)$，我们考虑枚举中间的 $e_2:u_0\leftrightarrow v_0$，由乘法原理， $(e_1\Leftrightarrow  e_2\Leftrightarrow e_3)$ 有 $(d_{u_0}-1)(d_{v_0}-1)$ 种选择，其中 $d_p$ 表示点 $p$ 的度。由加法原理，答案即为所有 $e_2$ 的答案之和。综上，答案为
$$
C_n^3-\sum_{i=1}^n (d_{a_i}-1)(d_{b_i}-1)
$$

**代码** [剪贴板](https://paste.ubuntu.com/p/sJbqWBzptp/)

---

## 作者：LinkZelda (赞：1)

- **题意**：

多组询问，每次给定 $n$ 个二元组 $(a_i,b_i)$，保证任意两个二元组的 $a_i$ 或者 $b_i$ 至少一个不同。求从这 $n$ 个二元组中选三个满足 $a_i$ 或者 $b_i$ 至少一个两两不同的方案数。

$\sum n\leq 2\cdot 10^5,a_i,b_i\leq n$。

- **做法**：

考虑容斥，总方案数为 $n\choose3$，转化为求选三个二元组满足 $a_i,b_i$ 均存在相等的方案数。

先思考一下选的过程：我们选定一个二元组 $i$ 之后，必定会在 $a_i$ 相等的这些二元组中再选一个，我们把第二个选定的二元组称为 $j$。那么第三个选定的二元组 $k$ 必定满足 $b_i=b_k$ 或者 $b_j=b_k$。

考虑优化，注意到值域很小，我们对每个 $a_i$ 开一个 `vector`，将二元组按 $a_i$ 分组，同时对每个 $b_i$ 开一个桶，统计对于每个 $b_i$ 统计二元组个数。一个二元组被选定的次数显然为所在的 `vector` 的大小减 $1$，对答案的贡献是这个二元组的 $b_i$ 对应的出现次数减 $1$，枚举 $a_i$ 计算即可。

时间复杂度为 $O(n)$。

- [代码](https://www.luogu.com.cn/paste/kpeukbtr)

---

## 作者：maruize (赞：1)


想到按 topic difficulty 分为左右两部分，二元组作为边，然后是一个二分图。

要求拎出三条边，他们在左侧**或**右侧不共点，求方案数。

---

先想到 左侧或右侧不共点数 = 左侧不共点数 + 右侧不共点数 - 都不共点数 。

然后发现很难做。

---

直接做看起来更难，然后想到取补集方法：

总数 - 不合法 。

但我赛时感觉这样也很不好做。不合法的大概是左侧选两个点，右侧选两个点，把它们串起来。

可是有四个点啊……

枚举边的话也是三条啊……

大概是这样

![图](https://cdn.luogu.com.cn/upload/image_hosting/odeh3gam.png)

---

经过旁边的人一指点才发现可以枚举中间的边（绿边），然后两侧的边的方案数就是中间边连接的两个点的度 -1 再乘起来。

然而我一直在想枚举两侧的边（红边）再确定另外两条边。

_code:_

```cpp
void work(){
	LL n;
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld%lld",a+i,b+i);
		visa[a[i]]++,visb[b[i]]++;//deg度数
	}LL ans=0;
	for(int i=1;i<=n;i++)ans+=(visa[a[i]]-1)*(visb[b[i]]-1);
	ans=n*(n-1)*(n-2)/6 //C(n,3)
        -ans;
	printf("%lld\n",ans);
	for(int i=1;i<=n;i++)visa[i]=visb[i]=0;//clear
}
```

---

## 作者：nytyq (赞：0)

## 前言

~~难得一见的瞬秒题。~~

## 分析

依照题意选择 $3$ 个二元组，总情况为：
$$
\displaystyle C_{n}^2=\frac{n(n-1)(n-2)}{6}
$$

考虑到题目中要求：满足 $a_i$ 和 $b_i$ 中至少一个和其他选择两两不相同。则进行反面思考，即总情况减去相同的 $a_i$ 和 $b_i$ 即可。

可以考虑用 ```map``` 进行判断相同操作，存下来每个数的出现次数。

考虑到一个二元组 $(a_i,b_i)$ 已经固定，则在下一组 $(a_j,b_j)$ 中，如果有 $a_i=a_j$，则一共有 $Map_{a_i}-1$ 种情况，同理有如果 $b_i=b_j$ 的情况，则一共有 $Map_{b_i}-1$ 种情况，相乘即可求出减去的数量。

## ACcode

```cpp
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=2e5+10;
ll a[N];
ll b[N];

ll n;

map<ll,ll> A,B;

void solve(){
	A.clear(),B.clear();//多测不清空，爆零两行泪
	cin>>n;
	for(ll i=1;i<=n;i++){
		cin>>a[i]>>b[i];A[a[i]]++;B[b[i]]++;
	}
	ll ans=n*(n-1ll)*(n-2ll)/6ll;
	for(ll i=1;i<=n;i++){
		ans-=(A[a[i]]-1)*(B[b[i]]-1);
	}
	cout<<ans<<endl;
}

int main(){
	ios::sync_with_stdio(0);
	int t;
	cin>>t;
	while(t--) solve();

	return 0;
}
```

---

## 作者：Domain_expansion (赞：0)

### 思路  
发现可以用另一个思路：全部选法减不符合选法。  
全部的选法即：
$$\frac{n(n-1)(n-2)}{6}$$
而不符合的选法也就是两个二元组至少一个元素均相同。  
建数组 $va_{a_i}$ 存 $a_i$ 出现的次数，$vb_{b_i}$ 存 $b_i$ 出现的次数。  
根据乘法原理，对于某个二元组 $(a_i,b_i)$。   
有 $(va_{a_i}-1)\times(vb_{b_i}-1)$ 种不符合的选法。  
所以答案是：
$$
\frac{n(n-1)(n-2)}{6}-\sum_{i = 1}^{n} (va_{a_i}-1)(vb_{b_i}-1)
$$

### AC 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long //开 long long 
int a[200010],b[200010],va[200010],vb[200010];
void run(){ 
	int n;
	cin>>n;
	int ans=n*(n-1)*(n-2)/6; //全部的选法 
	for(int i=1;i<=n;i++) va[i]=vb[i]=0; 
	for(int i=1;i<=n;i++){ 
		cin>>a[i]>>b[i];
		va[a[i]]++;
		vb[b[i]]++;
	}
	for(int i=1;i<=n;i++){
		ans-=(va[a[i]]-1)*(vb[b[i]]-1); //遍历并减去不符合的 
	}
	cout<<ans<<endl; //剩下的就是符合的了 
}
signed main(){
	int t;
	cin>>t;
	while(t--) run();
	return 0;
}
```
完结撒花。

---

## 作者：Echo_Long (赞：0)

### [Training Session](https://www.luogu.com.cn/problem/CF1598D)

计数题。

首先考虑正向计数，发现答案为满足 $a$ 三个不相同和满足 $b$ 三个不相同的方案数的加和，还要减去同时满足 $a$ 三个不相同和 $b$ 三个不相同的方案数量，比较麻烦。

正难则反，我们用总数减掉不合法的情况。

显然总操作次数为 $C_n^3=\frac {n\times(n-1)\times(n-2)}6$。

因为没有两个相等的点对，那么不合法的情况一定是当前这个点对和一个相同的 $a$ 和一个相同的 $b$ 组成。

因为如果是三个相同的 $a$，那么三个 $b$ 一定是互不相同的，三个相同的 $b$ 同理。

那么乘法计数一下即可。

```c++
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define inl inline
#define getchar() cin.get()
#define int long long
const int N = 2e5 + 5;
const int mod = 1e9 + 7;

int read()
{
	int f = 1 , x = 0;
	char ch = getchar();
	while ( !isdigit(ch) ) { if ( ch == '-' ) f = -1; ch = getchar(); }
	while ( isdigit(ch) ) { x = ( x << 1 ) + ( x << 3 ) + ( ch ^ 48 ); ch = getchar(); }
	return x * f;
}

int n , a[N] , b[N] , ans;

map<int,int> mpa , mpb;

signed main ()
{
	ios::sync_with_stdio(false);
	cin.tie(0) , cout.tie(0);
    int T = read();
    while ( T -- )
    {
        n = read() , ans = n * ( n - 1 ) * ( n - 2 ) / 6;
        mpa.clear() , mpb.clear();
        for ( int i = 1 ; i <= n ; i ++ ) a[i] = read() , b[i] = read() , mpa[a[i]] ++ , mpb[b[i]] ++;
        for ( int i = 1 ; i <= n ; i ++ ) ans -= ( mpa[a[i]] - 1 ) * ( mpb[b[i]] - 1 );
        cout << ans << endl;
    }
}
```



---

## 作者：XL4453 (赞：0)

今日血压：有且仅有一个数组开小了。要不是 CF 有数组越界提醒，我可能这辈子都看不出这个错误。

---
### 解题思路：

简单数数题。~~就这我还 WA 了两发。~~

正难则反，考虑先算出所有可能的取值然后再减去不可行的方案数。

由于不存在完全相同的二元组，一组方案不可行是三个中有一组 $a$ 相同的同时有一组 $b$ 相同的充分必要条件，那么算出后者即可。

由于要选出的是三个二元组，如果不满足条件就一定意味着有一个二元组的 $a$ 与其中一个相等，同时，$b$ 与另一个相等。那么就考虑每一次枚举这个感觉在中心的二元组，然后用初始化的各个元素的数量计算出可行的方案数。

可以发现，这样的计算由于不存在完全相同的二元组，所以一定没有重复，而且可能的情况也只有这一种，所以一定不存在漏解。


---
### 代码：

```cpp
#include<cstdio>
using namespace std;
#define int long long
int T,n,a[200005],b[200005],cnta[200005],cntb[20005],ans;
signed main(){
	scanf("%I64d",&T);
	while(T--){
		scanf("%I64d",&n);
		ans=0;
		for(int i=1;i<=n;i++)
		cnta[i]=cntb[i]=0;
		for(int i=1;i<=n;i++){
			scanf("%I64d%I64d",&a[i],&b[i]);
			cnta[a[i]]++;
			cntb[b[i]]++;
		}
		ans=n*(n-1)*(n-2)/6;
//一开始看错题，以为是所有的都不能一样，然后就有了下面的容斥
//		for(int i=1;i<=n;i++){
//			ans-=cnta[i]*(cnta[i]-1)/2*(n-cnta[i]);
//			ans-=cntb[i]*(cntb[i]-1)/2*(n-cntb[i]);
//		}
		for(int i=1;i<=n;i++){
			ans-=(cnta[a[i]]-1)*(cntb[b[i]]-1);
		}
		printf("%I64d\n",ans);
	}
	return 0;
}
```


---

## 作者：Farkas_W (赞：0)

$$\text{题目大意}$$

$\quad$有 $n$ 组数，每组数包含一个 $a_i,b_i$($a_i,b_i \leq n$)，从 $n$ 组数中选择 $3$ 组数，满足 $a$ 全不同或 $b$ 全不同，问有多少种方案数？

$$\text{思路}$$

$\quad$考虑容斥原理，首先总共的方案数为 
$$C_n^3=\frac{n\times (n-1)\times (n-2)}{6}$$

$\quad$题目中还有一个条件是没有两组数的 $a$ 和 $b$ 完全相同，所以最多 $a$ 不同或 $b$ 不同。考虑不符合题目要求的情况，即满足既有 $a$ 相同，又有 $b$ 相同的三组数的方案数。

$\quad$对于第 $i$ 组数，与 $a_i$ 相同的数的个数为 $num1$ ，与 $b_i$ 相同的数的个数为 $num2$，设 $j，k$ 满足 $a_j=a_i,b_k=b_i$，由题可得 $b_j\neq b_k,a_j\neq a_k$，即不会重复计数，显然除了 $i$ 本身以外所有的 $j$ 和 $k$ 可以自由组合，所以可得：
$$ans=C_n^3-\displaystyle\sum_{i=1}^{n}(num1[a_i]-1)\times(num2[b_i]-1)$$

$\quad$多组数据，记得清空数组，并且要开 long long。

```cpp
const int N=2e5+5;
int T,n,num1[N],num2[N],a[N],b[N],ans;
il int num(int x){return x*(x-1)*(x-2)/6;}
signed main()
{
	T=read();
	while(T--){
		n=read();ans=0;
		for(re i=1;i<=n;i++)
		{
			a[i]=read();b[i]=read();
			num1[a[i]]++;num2[b[i]]++;
		}
		for(re i=1;i<=n;i++)ans+=(num1[a[i]]-1)*(num2[b[i]]-1);
		for(re i=1;i<=n;i++)num1[a[i]]=0,num2[b[i]]=0;
		print(num(n)-ans);putchar('\n');
	}
	return 0;
}
```


---

