# Beautiful Array

## 题目描述

You are given an array of integers $ a_1, a_2, \ldots, a_n $ and an integer $ k $ . You need to make it beautiful with the least amount of operations.

Before applying operations, you can shuffle the array elements as you like. For one operation, you can do the following:

- Choose an index $ 1 \leq i \leq n $ ,
- Make $ a_i = a_i + k $ .

The array $ b_1, b_2, \ldots, b_n $ is beautiful if $ b_i = b_{n - i + 1} $ for all $ 1 \leq i \leq n $ .

Find the minimum number of operations needed to make the array beautiful, or report that it is impossible.

## 说明/提示

In the first set of input data, the array is already beautiful.

In the second set of input data, you can shuffle the array before the operations and perform the operation with index $ i = 1 $ for $ 83966524 $ times.

In the third set of input data, you can shuffle the array $ a $ and make it equal to $ [2, 3, 1] $ . Then apply the operation with index $ i = 3 $ to get the array $ [2, 3, 2] $ , which is beautiful.

In the eighth set of input data, there is no set of operations and no way to shuffle the elements to make the array beautiful.

In the ninth set of input data, the array is already beautiful.

## 样例 #1

### 输入

```
11
1 1000000000
1
2 1
624323799 708290323
3 1
3 2 1
4 1
7 1 5 3
5 1
11 2 15 7 10
7 1
1 8 2 16 8 16 31
13 1
2 1 1 3 3 11 12 22 45 777 777 1500 74
10 2
1 2 1 2 1 2 1 2 1 2
11 2
1 2 1 2 1 2 1 2 1 2 1
13 3
2 3 9 14 17 10 22 20 18 30 1 4 28
5 1
2 3 5 3 5```

### 输出

```
0
83966524
1
4
6
1
48
-1
0
14
0```

# 题解

## 作者：yshpdyt (赞：13)

## 题意
一个序列，初始时可以任意改变所有元素的位置，每次操作可以使某一位置上的数加 $k$，同一组数据 $k$ 恒定不变。求最小操作次数让序列变得回文。

## Sol

感觉比艾弗难啊！

考虑无法改变所有元素的位置，判断是简单的，即必须满足，$\forall i\in [1,n]  $，$a_i\equiv a_{n-i+1}\pmod k $，只有这样才可以通过有限次操作使得两位置上的数相同，此时答案只有一种可能，比较好求不多说了。

现在可以变位置，首先抛弃操作次数最小化的限制，找有解条件。根据刚才的结论，只有 $\bmod k$ 余数相同的数可以匹配，不妨按照余数开桶进行分类处理。

$n$ 是偶数的情况是简单的，即对于每种可能的余数，桶内必须有偶数个元素，否则总会存在一种余数无法匹配。

尝试扩展到 $n$ 为奇数的情况，注意到一个奇回文串中间的元素可以不与其它元素匹配，这会导致某个余数的桶内元素是奇数，并且理应只有一个桶是如此。

于是判断无解的思路就很清楚了，按照 $a_i \bmod k$  分组统计个数，$n$ 为偶数桶的大小全部为偶数，$n$ 为奇数有且仅有一个桶的大小为奇数，否则无解。这两种情况都可以规约到最多只有一个桶的大小为奇数。

然后考虑最小操作次数，注意到不同余数之间的操作相互独立，可以尝试转化问题为：给定一个序列，让序列中的数两两匹配，如果长度是奇数可以让任意元素不匹配，最小化每组元素差的绝对值之和。

通过排序后大的减小的去掉绝对值，仍然分奇偶考虑。

偶数情况是简单的，因为所有元素都必须参与匹配，尝试贪心，即让每组元素的差尽可能小，也就是让每个元素尽可能匹配与之接近的元素，不难发现其实就是排序后按顺序两两配对。

再尝试扩展到奇数的情况，一个很常用的套路是，如果题目描述中存在对任意位置进行恰好一次操作等字眼，通常考虑可以枚举对哪一个字符进行操作。

在转化后的题意中，即选择一个位置，对左右两边分别进行匹配，使答案最小，由于去掉一个位置后，左右两边都是偶数，便成为了刚才的操作。

但这样还不太够，要考虑修改问题，不妨记 $xl$ 与 $xr$ 表示左右两边当前的最小取值，枚举的位置每向右移，$xr$ 要减去一组，$xl$ 要加上一组，这样就可以在线性的时间内求出奇数情况的答案。

最后对于不同余数，答案累加即可。

 $k$ 的范围是 $[1,10^9]$，所以余数的桶要离散化或者 `map` 处理。

时间复杂度 $O(n\log n)$。

## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 200005
#define endl "\n" 
#define fi first
#define se second
using namespace std;
const ll mod=1e9+7;
const ll inf=1e18;
const double eps=1e-6;
ll n,m,a[N],b[N],c[N],k;
bool vis[N];
map<ll,vector<ll> >mp;
set<ll>v;
void sol(){
    mp.clear(),v.clear();
    cin>>n>>k;
    for(int i=1;i<=n;i++)cin>>a[i];
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++){
        mp[a[i]%k].push_back(a[i]);
        v.insert(a[i]%k);
    }
    ll cnt=0,res=0;
    for(auto y:v){
        ll mx=inf;
        if(mp[y].size()&1){
            cnt++;
            if(cnt>=2){
                cout<<-1<<endl;
                return ;
            }
            ll xl=0,xr=0;
            for(int i=2;i<mp[y].size();i+=2){ 
                xr+=(mp[y][i]-mp[y][i-1])/k;
            }
            mx=min(mx,xr+xl);
            for(int i=2;i<mp[y].size();i+=2){
                xr-=(mp[y][i]-mp[y][i-1])/k;
                xl+=(mp[y][i-1]-mp[y][i-2])/k;
                mx=min(mx,xr+xl);
            }
            res+=mx;
            continue;
        }
        for(int i=1;i<mp[y].size();i+=2)res+=(mp[y][i]-mp[y][i-1])/k;
    }
    cout<<res<<endl;
}
int main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    ll ttt;
    cin>>ttt;
    while(ttt--)sol();
    return 0;
}
```

---

## 作者：shicj (赞：4)

# CF1986E Beautiful Array 题解
## Part1. 题目概述
你有一个数组，其**顺序可以随意打乱**。

你可以在其中任选一个数增加 $k$，这记为一次操作。

求最小的操作次数以使原数组为**回文串**。

若不可能，输出 $-1$。

## Part2. 思路
1. 首先看到只能增加 $k$，说明无论怎么操作，每个数**除以 $k$ 的余数不变**。

2. 要求得到**回文串**且**顺序可以随意打乱**，也就是说只要满足最终的数组只有**不大于一个数出现的次数为奇数**（这个数拿一个放中间，其他的左右两边对称放）。

3. 再回到1，**除以 $k$ 的余数不变**，那么可以对除以 $k$ 的每一个余数分组，每一组都可以通过加 $k$ 使得数字相等，比如这组样例的分组：
	```
	13 3
	2 3 9 14 17 10 22 20 18 30 1 4 28
	```
	| 余数为 $0$ | 余数为 $1$ | 余数为 $2$ |
	| :----------- | :----------- | :----------- |
	| $3,9,18,30$ | $10,22,1,4,28$ | $2,14,17,20$ |
4. 如何判断是否可行呢？只需要统计所有组中有几组的**元素个数**为奇数（如上面的分组中余数为 $1$ 组就是奇数个数，必须把这个组中的某个元素放到新序列的**中心**位置），如果个数大于 $1$，就一定是不可行的（不可能把多个元素放到中心）。
5. 接下来开始构造最优解。可以很清楚地发现，要在每一组中构造出相等的元素对（一个放前面，一个放后面），比如上余数为 $1$ 组可以这样构造：
	$$(2,14),(17,20)$$
	只要：
   $$(2+3\times4,14),(17+3\times1,20)$$
   进行了 $4+1=5$ 次操作。
   
   如果是奇数个元素的组，只需要取出一个元素放在中心后，变成偶数个元素的组即可。


6. 如何使解最优呢？可以先尝试把每一个组内排个序：

	| 余数为 $0$ | 余数为 $1$ | 余数为 $2$ |
	| :----------- | :----------- | :----------- |
	| $3,9,18,30$ | $1,4,10,22,28$ | $2,14,17,20$ |
    
   这时候要分类讨论一下了：
	- 一组中有偶数个元素。
    
    	从小到大，每次取两个，一定最优。（否则如果跨过中间的元素找，一定会需要更多操作，你可以自己模拟一下）。
        
   - 一组中有奇数个元素。
   
   		很快想到朴素方法：枚举要去除的元素，求出去除每个元素下的最优，时间复杂度 $O(n^2)$。
        
      这显然会超时，但大致思路是可行的，求出下一个解时很多计算是和上一个重复的，这就有了优化的方法。下图七个数的情况：
      | 不取 | 第一组 | 第二组 | 第三组 | 
		| :----------- | :----------- | :----------- | :----------- |
		| $1$ | $(2,3)$ | $(4,5)$ | $(6,7)$ |
		| $2$ | $\color{red}(1,3)$ | $(4,5)$ | $(6,7)$ | 
		| $3$ | $\color{red}(1,2)$ | $(4,5)$ | $(6,7)$ | 
		| $4$ | $(1,2)$ | $\color{red}(3,5)$ | $(6,7)$ | 
		| $5$ | $(1,2)$ | $\color{red}(3,4)$ | $(6,7)$ | 
		| $6$ | $(1,2)$ | $(3,4)$ | $\color{red}(5,7)$ | 
		| $7$ | $(1,2)$ | $(3,4)$ | $\color{red}(5,6)$ |
        
        红色的就是变化的部分，这样就解出了（分奇偶讨论一下）。
        $$f(a_{i+1})= \begin{cases}f(a_i)-\dfrac{(a_{i+2}-a_{i+1})}{k}+\dfrac{(a_{i+2}-a_i)}{k},\quad &&i \equiv 1 \pmod 2\\f(a_i)-\dfrac{(a_{i+1}-a_{i-1})}{k}+\dfrac{(a_{i}-a_{i-1})}{k},\quad&&i \equiv 0 \pmod 2\end{cases} $$
        问题解决！

## Part3. Code
注意数据范围，存余数等可以开映射解决，也可以离散化。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100001];
int mod[100001];
int k;
map<int,int>mds;
map<int,int>vis;
vector<int>modn;
map<int,vector<int> >md;
void solve(){
	cin>>n>>k;
	mds.clear();
	md.clear();
	for(int i=1;i<=n;i++){
		cin>>a[i];
		mod[i]=a[i]%k;
		mds[mod[i]]+=1;
		md[mod[i]].push_back(a[i]);
	}
	vis.clear();
	modn.clear();
	int	ss=0;
	for(int i=1;i<=n;i++){
		if(vis[mod[i]]==0){
			modn.push_back(mod[i]);
			if(mds[mod[i]]%2)ss++;
			vis[mod[i]]=1;
		}
	}
	if(ss>=2){
		cout<<-1<<endl;
		return;
	}
	int sum=0;
	for(auto i:modn){
		sort(md[i].begin(),md[i].end());
		if(md[i].size()%2){
			int ss=0,s=0x3f3f3f3f;
			for(int j=1;j+1<md[i].size();j+=2){
				ss+=(md[i][j+1]-md[i][j])/k;
			}
			s=ss;
			for(int j=0;j+1<md[i].size();j++){
				if(j%2){
					ss=ss-(md[i][j+1]-md[i][j-1])/k+(md[i][j]-md[i][j-1])/k;
				}
				else{
					ss=ss-(md[i][j+2]-md[i][j+1])/k+(md[i][j+2]-md[i][j])/k;
				}
				s=min(s,ss);
			}
			sum+=s;
		}
		else{
			for(int j=0;j+1<md[i].size();j+=2){
				sum+=(md[i][j+1]-md[i][j])/k;
			}
		}
	}
	cout<<sum<<endl;
}
int main(){
	int t;
	cin>>t;
	while(t--)solve();
	return 0;
}
```

---

## 作者：TTpandaS (赞：3)

对于最后的序列，一定满足 $a_i \equiv a_{n-i+1} \pmod k$。因此首先将序列按 $a_i \bmod k$ 的值分成几段，依次考虑每一个段。

如果长度为奇数的段数量大于 $1$，那么无解。

对于长度为偶数的段，按照 $a_i$ 排序后将相邻两个匹配最优。

对于长度为奇数的段，需要空出一个位置不匹配，令 $f_{i,0/1}$ 表示前 $i$ 个数，已经存在/还不存在有位置不匹配的最小花费，那么 $f_{i,0}=f_{i-2,0}+\dfrac{a_i-a_{i-1}}{k} , f_{i,1}=\min{f_{i-2,1}+\dfrac{a_i-a_{i-1}}{k},f_{i-1,0}}$。特判区间长度为 $1$ 的情况后，初始化 $f_{1,0}=f_{1,1}=0,f_{2,0}=\dfrac{a_2-a_1}{k}$，其余设为 $\infty$。答案统计 $\min{f_{len,1},f_{len-1,0}}$。

---

## 作者：Targanzqq (赞：3)

### 思路：
如果两个数 $a,b$ (假设 $a>b$）可以通过分别加任意次 $k$ 使它们相等，那么则有 $a\bmod k= b\bmod k$，对答案的贡献为 $(a-b)/k$。

首先我们可以统计一下序列中除以 $k$ 可以产生的余数并离散化（因为一共 $10^5$ 个数，能产生的余数集不超过 $10^5$）并放到一个 map 中，然后对于每个数根据其除以 $k$ 的余数映射放到集合里（目的是最小化上面的式子）。接下来分类讨论。

如果序列长度是**偶数**：
> 首先如果有一组长度为奇数，那么意味着有一个数无法进行配对，从而无法构造。我们对于每一组，排序后去相邻的数进行排序（我使用了 multiset，会自动排序，且支持重复插入）。排序后每遇到两个数统计一次答案。

如果序列长度是**奇数**：
>如果有两组及以上长度为奇数，那么无法构造。否则对于长度为偶数的组，执行以上操作，否则对当前组求前后缀和（及从最前面和最后面开始按照上面的操作进行统计并对前面开始的求前缀和，后面开始的求后缀和），并枚举一个作为回文串中心的点（即不加入计算的点），对所有这样的点前面的数的前缀和以及后面的数的后缀和求最小值，并令结果加上这个最小值。

这样我们就完成了这道题，时间复杂度 $O(n \log n)$。

### 源代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
 
int T,n,k,a[100005],b[100005],b2[100005],f[100005][2],cnt;
multiset<int> t[100005];
map<int,int> mp;//映射余数
 
void lsh(){//离散化，进行映射
	for(int i=1;i<=n;i++){
		b2[i]=b[i];
	}
	sort(b2+1,b2+n+1);
	cnt=1;mp[b2[1]]=1;
	for(int i=2;i<=n;i++){
		if(b2[i]!=b2[i-1])cnt++;
		mp[b2[i]]=cnt;
	}
	for(int i=1;i<=n;i++){
		t[mp[b[i]]].insert(a[i]);
	}
}
 
signed main(){
	ios::sync_with_stdio(false);
	cin>>T;
	while(T--){
		cin>>n>>k;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			b[i]=a[i]%k;
		}
		lsh();
		int flag=1+n%2,res=0,maxn=0,mod1;
		for(int i=1;i<=cnt;i++){//统计没有答案或长度为偶数的序列
			int lst=0,now=0;
			if(t[i].size()%2==1&&flag==2){
				flag--;mod1=i;continue;
			}
			for(auto j:t[i]){
				now++;if(now%2==0)res+=(j-lst)/k;lst=j;
			}
			if(now%2==1)flag--;
			if(!flag){res=-1;goto nxt;}
		}
		nxt:
		if(!flag||n%2==0)cout<<res;
		else{//重新统计长度为奇数的序列
			int ans=res;
			int now=0,lst=0;
			for(auto j:t[mod1]){
				now++;if(now%2==0){f[now][0]=f[now-2][0]+(j-lst)/k;}
				if(now%1==0&&now>=3){f[now][1]=(j-lst)/k;} 
				lst=j;
			}
			for(int j=t[mod1].size()-2;j>=3;j--){f[j][1]+=f[j+2][1];}
			res=min(f[3][1],f[t[mod1].size()-1][0]);
			for(int i=3;i+2<=t[mod1].size();i+=2){
				res=min(res,f[i-1][0]+f[i+2][1]);
			}
			cout<<ans+res;
		}
		cout<<endl;
		for(int i=1;i<=n;i++){
			t[mp[b[i]]].clear();
			mp[b[i]]=0;
			f[i][0]=0;f[i][1]=0;
		}
	}
}
```

---

## 作者：ZhaoV1 (赞：2)

解析：

首先，如果两个数能够通过加减 $k$ 来得到，那么他们两个数对 $k$ 的除余结果应当相等，那么我们可以先将每个数都按照 $a_{i}÷k$ 的结果来分类，并将其顺序处理。
```cpp
	//用了结构体来存值
	for(int i=1;i<=n;i++){//输入
		cin >> a[i].val;
		a[i].div = a[i].val % k;
	}
	sort(a+1,a+1+n,cmp);
```

其次，由于两个完全相等的数放在回文位置可以使操作次数为 $0$，也就是最优，所以我们在做核心计算之前先把相同的数字消消乐一下。
```cpp
	for(int i=1;i<=n;i++){//消掉相同的值
		if(i+1<=n && a[i].val == a[i+1].val){
			i++;
		}else a[++na] = a[i];
	}
```

接下来，我们判断该数组是否能成为 Beautiful Array。此处我另外拿 $record$ 数组来存了一遍，数量为 $cnt$。
```cpp
	for(int i=1;i<=na;i++){
		if(i == na){
			if(odd){
				record[++cnt] = a[i];
				break;		
			}else{
				cout << -1 << '\n';
				return;
			}
		}
		if(i+1 <= na && a[i].div == a[i+1].div){
			record[++cnt] = a[i];
			record[++cnt] = a[i+1];
			i++;
			continue;
		}
		if(i+1 <= na && a[i].div != a[i+1].div){//落单
			if(odd){
				odd = false;
				record[++cnt] = a[i];	
			}else{
				cout << -1 << '\n';
				return;
			}
		}
	}
```

最后，用奇数偶数个数来区分计算方式：

**偶数**的情况：$val$ 最接近的两个数就是最优解，那么只要依次选择最近的两个数进行回文操作即可。\
**奇数**的情况：我们遍历一次来确定相同 $div$ 的奇数个数区间的位置。此后枚举当中每一个下标，换句话说，如果枚举下标为 $i$，表示将下标为 $i$ 的数当作奇数回文序列的中间数，也就是不需要处理的数字，紧接着我们将该数之前的操作总次数和该数之后的操作总次数相加，取最小值即可。\
注意，在处理奇数情况的时候最好用前缀和（或后缀和）来处理操作次数，以防超时。
```cpp
	if(cnt & 1) odd = true;
	if(odd){//奇数的情况：
		int index_begin = 0;
		int index_end = 0;
		int sum = 1;
		// 找到奇数个数区间index_begin ~ index_end
		for(int i=1;i<=cnt;i++){
			sum++;
			if(i == 1 || record[i].div != record[i-1].div){
				sum = 1;
				index_begin = i;
			}
			if(i == cnt || record[i].div != record[i+1].div){
				if(sum&1){
					index_end = i;
					break;
				}
			}
		}
		// 求res：
		for(int i=1;i<=cnt;i++){//做前缀和1
			if(i&1 && i <= cnt){
				s1[i] = s1[i-1] + abs(record[i].val - record[i+1].val) / k;
			}else s1[i] = s1[i-1];
		}
		for(int i=1;i<=cnt;i++){//做前缀和2
			if(!(i&1) && i <= cnt){
				s2[i] = s2[i-1] + abs(record[i].val - record[i+1].val) / k;
			}else s2[i] = s2[i-1];
		}
		int Min = 1e15+5;
		for(int i=index_begin;i<=index_end;i++){//枚举，配合使用两个前缀和
			Min = min(Min,s1[i-1]+s2[cnt]-s2[i]);
		}
		res = Min;
	}else{//偶数的情况：
		for(int i=1;i<=cnt;i+=2){
			res += abs(record[i].val - record[i+1].val) / k;
		}
	}
```

记得开 long long。
```cpp
	#define int long long
```

---

## 作者：2huk (赞：1)

> - 给定长度为 $n$ 的数组 $a_i$ 和一个整数 $k$。你可以重新排列 $a$ 使得将 $a$ 成回文串的所需操作次数最少。定义一次操作为将任意 $a_i \gets a_i + k$。
> - $n \le 10^5$，$k, a_i \le 10^9$。

考虑若只有两个数 $x, y$，每次可以选择一个数将其加 $k$，最少需要几步。

不难发现 $x, y$ 加上无论多少倍的 $k$ 后，在模 $k$ 意义下的值一定是不变的。所以若最开始 $x \not\equiv y \pmod y$ 那么无解。

否则，若 $x \equiv y \pmod k$，此时最优方案一定是把 $x, y$ 中的较小值累加到较大值。即最少需 $\dfrac{|x-y|}k$ 步。

考虑 $n$ 个数的情况。若 $n$ 为偶数，那么我们相当于从中选出 $\dfrac n2$ 对数，然后按照上面操作每对数。否则，若 $n$ 为奇数，那么首先要选出一个数放在中间位置，剩下的 $n - 1$ 个数按照偶数的操作。

先考虑偶数。我们可以统计出每个在模 $k$ 意义下相同的数构成的集合，用 vector 存储。此时就可以对于每个 vector 单独考虑两两组对的情况（因为不同 vector 中的数模 $k$ 一定不同，根据前文所述一定不合法）。即：

> 给定一个数组 $b_i$。将这些数两两配对，使两个数的差的绝对值之和最小。

注意这里我们没有考虑 $\dfrac 1k$ 的影响。因为我们只需要将这个公因式最后乘即可。

令 $m = |b|$。显然 $m$ 为奇数时一定无解。否则一定是将 $b$ 排序后相邻两个组成一对，即答案 $\sum (-1)^ib_i$。

若 $n$ 为奇数，那么我们需要找到一个长度为奇数的 vector，然后选择其中的一个放在 $a$ 的最中间，然后剩下的按照偶数的处理。注意这里如果存在两个及以上长度为奇数的 vector 那么无解。现在的问题是：

> 给定一个长为奇数的数组 $b_i$。删除一个数后，将这些数两两配对，使两个数的差的绝对值之和最小。

若删除的数是 $b_i$，那么此时的答案应为 $\sum_{j=1}^i (-1)^jb_j + \sum_{j=i+1}^n (-1)^{j+1}b_j = \sum_{j=1}^i (-1)^jb_j - \sum_{j=i+1}^n (-1)^jb_j$。预处理前后缀即可。
```cpp
int n, a[N], k;
map<int, int> cnt;
map<int, vector<int> > mp;
int b[N];
int pre[N], suf[N];

int calc(vector<int> v) {
	sort(v.begin(), v.end());
	
	int n = 0;
	for (int t : v) {
		b[ ++ n] = t;
	}
	
	for (int i = 1; i <= n; ++ i ) {
		pre[i] = pre[i - 1] + b[i] * (i % 2 ? 1 : -1);
	}
	
	suf[n + 1] = 0;
	for (int i = n; ~i; -- i ) {
		suf[i] = suf[i + 1] + b[i] * (i % 2 ? 1 : -1);
	}
	
	int res = min(suf[2], -pre[n - 1]);
	for (int i = 2; i < n; ++ i ) {
		res = min(res, - pre[i - 1] + suf[i + 1]);
	}
	
	return res;
}

int solve() {
	cin >> n >> k;
	
	cnt.clear();
	mp.clear();
	
	for (int i = 1; i <= n; ++ i ) {
		cin >> a[i];
		int t = a[i] % k;
		++ cnt[t];
		mp[t].push_back(a[i]);
	}
	
	int t = -1;
	for (auto x : cnt) {
		if (x.second & 1) {
			if (~t) return -1;
			t = x.first;
		}
	}
	
	int res = 0;
	if (~t) {
		auto v = mp[t];
		res = calc(v) / k;
	}
	
	for (auto e : cnt) {
		int x = e.first, y = e.second;
		
		if (x == t) continue;
		
		auto t = mp[x];
		sort(t.begin(), t.end());
		
		for (int i = 0, j = 1; j < y; i += 2, j += 2) res += (t[j] - t[i]) / k;
	}
	
	return res;
}
```

---

## 作者：junee (赞：1)

# CF1986E 题解

## 题目大意

给你一个长度为 $n$ 的数组。初始时，你可以任意改变顺序。每次操作将使某个数加 $k$，求出最小操作数 $m$ 使的数组可以形成回文串。

## 题目分析

经过观察发现对于一个初始的串，将两个相同的数对应是最优的，所以我们就将相同的数两两消去。

而对于两个数，如果他们对 $k$ 取模不相等，无论进行多少次操作都无法相等，所以可以将其按照余数分类，再进行操作。

当字符串长度 $n$ 为奇数时，可以将一个数放在中间。当同时存在两种余数的个数为奇数时一定无法满足。

当字符串长度 $n$ 为偶数时，当存在某种余数的个数为奇数时一定无法满足。

对于余数个数为偶数的类别，按照从小到大，依次两两配对最优，比较容易理解，操作次数即为两个数商的差值。

对于余数个数为奇数的类别，我们枚举删掉每个数后的操作次数，取最小值即可，用一个简单的动态规划即可解决，应该比较好想的。

## Code
```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<map>
#include<vector> 
using namespace std;
const int N=1e5+10;
int T,a[N],b[N];
map<int,int>mp;
vector<int> vec[N];
int len,n,k,tot,ans;
int f[N];
void clear(){
	for(int i=1;i<=N;i++)vec[i].clear();
	mp.clear();
	memset(a,0,sizeof a);
	memset(b,0,sizeof b);
	memset(f,0,sizeof f);
	n=tot=ans=0;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--){
		clear();
		cin>>len>>k;
		for(int i=1;i<=len;i++)cin>>a[i];
		sort(a+1,a+1+len);
		int cnt=1;
		for(int i=1;i<=len;i++){
			if(a[i]==a[i+1])cnt++;
			else{
				if(cnt%2)b[++n]=a[i];
				cnt=1;
			}
		}
		for(int i=1;i<=n;i++){
			if(mp.find(b[i]%k)==mp.end())mp[b[i]%k]=++tot;
		}
		for(int i=1;i<=n;i++){
			vec[mp[b[i]%k]].push_back(b[i]/k);
		}
		int odd=0;
		for(int i=1;i<=tot;i++){
			if(vec[i].size()%2==1)odd++;
		}
		if(odd>=2||(odd==1&&n%2==0)){
			cout<<-1<<'\n';
		}
		else{
			int pos=0,minn=0;
			for(int i=1;i<=tot;i++){
				if(vec[i].size()%2==1){
					pos=i;
				}
				else for(int j=0;j<vec[i].size();j+=2)ans+=vec[i][j+1]-vec[i][j];
			}
			if(pos){
				for(int i=1;i<vec[pos].size();i+=2){
					f[0]+=vec[pos][i+1]-vec[pos][i];
				}
				for(int i=1;i<vec[pos].size();i++){
					if((i+1)%2==1){
						f[i]=f[i-1]-vec[pos][i]+vec[pos][i-1];
					}
					else{
						f[i]=f[i-1]+vec[pos][i]-vec[pos][i-1];
					}
				}
				minn=0x3f3f3f3f;
				for(int i=0;i<vec[pos].size();i++)minn=min(minn,f[i]);
			}
			cout<<ans+minn<<'\n';
		}
	}
	return 0;
}

```

---

## 作者：ben090302 (赞：0)

奇怪题。

题意就是要求在任意顺序下，进行若干次单点 $+k$ 操作使得该序列变成回文的最小操作数。

显然可以注意到如果两个数一开始 $\bmod k$ 不同余那么他俩不可能通过加 $k$ 变得一样。所以考虑按照 $\bmod k$ 的余数分个组。

考虑无解的判断。

假设一个组的大小为奇数，那么就说明必定有一个数无法与其他数配对。

如果数组长度为偶数那么我们不容许哪怕一个这种组存在，若存在则无解。

如果奇数，我们可以允许一个存在，因为可以让它放在正中间和自己配对。

在统一块内，我们可以发现一定要用最大减去次大然后次次大减去次次次大这样的方式去配对——这样最优，证明考虑画图理解，手摸一组数据就知道了。

考虑统计答案。首先对原数组按 $\bmod k$ 的余数为第一关键字，大小为第二关键字从小到大排序。这样原数组就会形成一个个块。

统计答案，若 $n$ 为偶数，则每个块扫一遍即可。

奇数的情况，偶数块同上，奇数块我们记录一个 $sum$ 数组作为前缀和。

每个点在块内的贡献应该是正负一来回排列的，考虑删去第 $i$ 个数，他的结果就会是 $sum_{w}-sum_i-sum_{i-1}$ 其中 $w$ 为这个块的末尾。

注意到巨大的值域范围，我们开个 `map` 就好了

code:

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T;
int n,k;
int a[200005];
bool cmp(int x,int y){
    return (x%k==y%k?x<y:x%k<y%k);
}
map<int,vector<int> >ton;
vector<int> P;  
int sum[200005];
void work(){
    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>a[i];
    P.clear();
    for(int i=1;i<=n;i++) ton[a[i]%k].clear(); 
    sort(a+1,a+n+1,cmp);
    int cnt,nm,col=a[1]%k;
    cnt=0,nm=0;
    for(int i=1;i<=n;i++){
        ton[a[i]%k].push_back(i);
        if(col==a[i]%k){
            nm++;
        }
        else{cnt+=(nm%2==1);nm=1;col=a[i]%k;}
    }
    // for(int i=0)
    if(n%2==0 and cnt!=0){
        cout<<"-1\n";
        return ;
    }
    if(n%2==1 and cnt>1){
        cout<<"-1\n";
        return ;
    }
    int ans=0;
    if(n%2==0){
        for(int i=1;i<=n;i+=2){
            ans+=a[i+1]-a[i];
        }
        cout<<ans/k<<"\n";
    }
    else{
        for(int i=1;i<=n;i++){
           if(i==1 or (i!=1 and a[i]%k!=a[i-1]%k)) P.push_back(a[i]%k);           
        } 
        for(int v:P){
            if(ton[v].size()%2==0){
                for(int i=0;i<ton[v].size();i+=2){
                    ans+=abs(a[ton[v][i+1]]-a[ton[v][i]]);
                }
            }
            else{
                int zz=INT_MAX;
                int tot=1;
                for(int i=ton[v].size()-1;i>=0;i--){
                    sum[i]=tot*a[ton[v][i]];
                    tot*=-1;
                } 
                for(int i=1;i<ton[v].size();i++){
                    sum[i]+=sum[i-1];
                }
                for(int i=0;i<ton[v].size();i++){
                    if(i==0) zz=min(zz,sum[ton[v].size()-1]-sum[i]);
                    else zz=min(zz,sum[ton[v].size()-1]-sum[i-1]-sum[i]);
                }
                ans+=zz; 
            }
        }
        cout<<ans/k<<"\n";
    } 
}

signed main(){
    cin>>T;
    while(T--){
        work();
    }
}
```

---

## 作者：Daniel_yao (赞：0)

# Solve

考虑假设两数 $x,y$ 能在加 $k$ 的操作后相同，则 $x-y\equiv 0\pmod{k}$，可以推得 $x\equiv y\pmod{k}$。可以想到按 $a_i \bmod k$ 排序，同时比较 $a_i$ 的值，保证 $a_i$ 升序。

定义“一组”的概念为 $a_i\bmod k$ 相同的 $a_i$ 组成的升序序列。

对于一组来说，相邻两项凑一起算贡献肯定最优，自然推出了组长为偶数的情况，便是两两配对贡献。

考虑奇数组的情况：先枚举中间点 $a_{mid}$，此数对答案无贡献，然后从左至右两两配对贡献。这里因为要枚举中间点，所以暴力的时间复杂度为 $O(n^2)$。可以考虑答案连续的贡献情况，每次抵消上一次的贡献，并将本次的贡献加上，每次取最小即可。（注意答案贡献的正负情况，自行推理）。

分 $n$ 为偶数和奇数的情况来做：

- 当 $n$ 为偶数时，若出现奇数组则无解，否则分组算贡献累加即可。

- 当 $n$ 为奇数时，若出现两组以上的奇数组则无解，否则分组算贡献累加，奇数组单独处理。

总时间复杂度：$O(n\log n)$。

# Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define For(i,l,r) for(int i=l;i<=r;++i)
#define FOR(i,r,l) for(int i=r;i>=l;--i)
#define inf 1e11

using namespace std;

const int N = 2e5 + 10;

int T, n, k, a[N];

void solve() {
  int ans = 0;
  cin >> n >> k;
  For(i,1,n) cin >> a[i];
  sort(a + 1, a + n + 1, [](int x, int y){return (x % k == y % k ? x < y : x % k < y % k);});
  // For(i,1,n) cerr << a[i] << ' ';
  // cerr << '\n';
  if(n & 1) {
    int r = 1, l = 1, sum = 0, f = 0, Min = inf;
    vector<int> v;
    int cnt = 1;
    For(i,1,n) {
      if(a[i] % k == a[i+1] % k && i < n) cnt++, v.push_back(a[i]);
      else {
        if(cnt & 1) {
          v.push_back(a[i]);
          f++; r = i, l = r - v.size() + 1;
        } 
        else vector<int>().swap(v);
        cnt = 1;
      }
    }
    for (int i = 1; i <= l-1; i += 2) ans += a[i+1] - a[i];
    for (int i = r+1; i <= n; i += 2) ans += a[i+1] - a[i];
    For(i,l,r) sum += (((i-l+1) & 1) ? 1 : -1) * a[i];
    Min = min(Min, sum - a[l]);
    For(i,l+1,r) {
      if(!((i-l+1) & 1)) {
        sum -= a[i-1] * 2;
        sum += a[i] * 2;
      }
      Min = min(Min, sum - a[i]);
    }
    if(f > 1) {
      cout << "-1\n";
      return ;
    }
    cout << (ans + Min) / k << '\n';
  } else {
    int cnt = 1;
    For(i,1,n) {
      if(a[i] % k == a[i+1] % k && i < n) {
        cnt++;
      } 
      else {
        if(cnt & 1) {
          cout << "-1\n";
          return ;
        }
        cnt = 1;
      }
    }
    for (int i = 1; i <= n; i += 2) {
      ans += a[i+1] - a[i];
    }
    cout << ans / k << '\n';
  }
  return ;
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> T;
  while(T--) solve();
  return 0;
}
```

---

## 作者：Wei_Han (赞：0)

能够发现，假如我们已经固定了两个数，令其中一个通过多次操作等于另一个，那么此时他们俩同增是无意义的，因为可以互相消掉。也就是，此时两个数可以变为相等的条件为 $a-b \equiv 0 \pmod {k}$，即 $a \equiv b \pmod {k}$，这对数对答案的影响就是 $\left \lfloor \frac{a-b}{k}\right \rfloor$。

那么我们可以根据余数将 $a_i$ 进行分组，每一组中的数两两配对。此时会发现根据 $n$ 的奇偶性，有不同情况。

当 $n$ 为奇数，那么有且仅有一组数的个数为奇数。当 $n$ 为偶数，那么每一组数的个数都为偶数，可以依次作为判断无解情况的标志。

考虑计算一组内数的贡献，显然，要使每一对 $\left \lfloor \frac{a-b}{k}\right \rfloor$ 最小，让排序后两个相邻的数配对最好，但这是在一组内能够全部配对的情况，也就是当数的个数为偶数时。

进一步，假如当前组内有奇数个数，那么显然需要排除掉一个数，那么我们就可以枚举这一个数，之后处理它前后的贡献总和，取最小值即可，前后的贡献总和用前后缀和按照奇偶性计算即可。注意后缀和需要考虑到减去这一个数之后的位置关系。

时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f3f3f3f3f
#define pr printf("\n")
#define pp printf(" ")
#define pii pair<ll,ll>
#define mem(aa,bb) memset(aa,bb,sizeof(aa))
#define fo(a,i,b) for(ll i = a ; i <= b ; ++ i )
#define Fo(a,i,b) for(ll i = a ; i >= b ; -- i )
#define bug (x>=1&&x<=n&&y>=1&&y<=m) 
using namespace std;
typedef long long ll;
typedef __int128 i128;
typedef double db;
const int N=1e6+5,M=1e7+5;
const db eps=1e-7;
inline void read(ll &opp){ll x=0,t=1;char ch;ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-'){t=-1;}ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}opp=x*t;return; }
inline void wr(ll x){if(x<0){putchar('-');x=-x;}if(x>9){wr(x/10);}putchar(x%10+'0');}
ll t,n,a[N],pre[N],k,fac[N];
struct node{ll x,y,fl;}b[N];
map<ll,ll> mp,mp1;
map<ll,pii > g,g1;
inline bool cmp(node x,node y){if(x.y==y.y) return x.x>y.x;return x.y<y.y;}
signed main(){
	read(t);
	while(t--){
		mp=mp1,g=g1;
		read(n);read(k);fo(1,i,n) read(a[i]),b[i].x=a[i]/k,b[i].y=a[i]%k;
		sort(b+1,b+1+n,cmp);
		ll sum=0,las=0;g[b[1].y].first=1;
		fo(1,i,n){if(b[i].y!=b[i-1].y&&i!=1) g[b[i-1].y].second=i-1,g[b[i].y].first=i,sum+=(las&1),mp[b[i-1].y]=(las&1),las=0;las++;}sum+=las&1;mp[b[n].y]=las&1;g[b[n].y].second=n; 
		if(n&1&&sum!=1){wr(-1);pr;continue;} 
		if(!(n&1)&&sum!=0){wr(-1);pr;continue;}
		sum=0;
		fo(1,i,n){
			if(b[i].y==b[i-1].y&&i!=1) continue;
			ll l=g[b[i].y].first,r=g[b[i].y].second;
			if(!mp[b[i].y]) fo(l,j,r) sum+=(((j-l+1)&1)?1:-1)*b[j].x;
			else{
				ll minn=INF;
				pre[l]=b[l].x;fo(l+1,j,r) pre[j]=pre[j-1]+(((j-l+1)&1)?1:-1)*b[j].x;
				fac[r]=-b[r].x;Fo(r-1,j,l) fac[j]=fac[j+1]+(!((j-l+1)&1)?1:-1)*b[j].x;
				fo(l,j,r) if(((j-l+1)&1)) minn=min(minn,(j-1<l?0ll:pre[j-1])+(j+1>r?0ll:fac[j+1]));
				sum+=minn;
			}
		}
		wr(sum);pr;
	}
	return 0;
}
``````

---

