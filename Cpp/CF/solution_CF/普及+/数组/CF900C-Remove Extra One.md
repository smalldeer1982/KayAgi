# Remove Extra One

## 题目描述

You are given a permutation $ p $ of length $ n $ . Remove one element from permutation to make the number of records the maximum possible.

We remind that in a sequence of numbers $ a_{1},a_{2},...,a_{k} $ the element $ a_{i} $ is a record if for every integer $ j $ ( $ 1<=j&lt;i $ ) the following holds: $ a_{j}&lt;a_{i} $ .

## 说明/提示

In the first example the only element can be removed.

## 样例 #1

### 输入

```
1
1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5
5 1 2 3 4
```

### 输出

```
5
```

# 题解

## 作者：LJ07 (赞：6)

## 题目描述
[题目传送门](https://www.luogu.com.cn/problem/CF900C)

## 思路简述
可以发现：

1.  如果一个数前面有不止一个数大于它，那么无论去掉那个数，它都无法成为 record。
1.  如果一个数前面所有数都小于它，那么无论去掉那个数，它都一定是 record。
1. 如果一个数前面有且仅有一个数大于它，那么当且仅当去掉大于它的那个数，它才能成为 record。
1. 如果一个数是 record，那么去掉它，recond 总数减 $1$。(废话)

### 解法一
那么我们就很容易的想到使用两个树状数组，一个维护小于某个数的数的个数，一个维护小于某个数的数的和。从前往后枚举使用上面发现的结论求解出去掉每个数据所对 record 总数的影响。(意会即可)

时间复杂度 $O(nlogn)$。

### 解法二
但是事实上没必要这么复杂。

我们可以从前往后枚举，顺便维护当前的最大值和次大值，然后进行一下的分类讨论：

+ 若仅有最大值比当前数大，那么就是情况 $3$。
+ 若最大值和次大值都比当前数大，那么就是情况 $1$。
+ 若最大值也小于它，那么就是情况 $2$ 和 $4$。

接下来的做法与解法一大同小异。

时间复杂度 $O(n)$

## 丑陋の代码
具体实现参见代码

[click here](https://www.luogu.com.cn/paste/evev2psf)

---

## 作者：Ghosty_Neutrino (赞：1)

## 题意
给你一段长度为 $n$ 的 $a_i$ 排列，然后定义一个 $a_i$ 为 record 当且仅当对于所有的 $j$ 小于 $i$,都有 $a_j<a_i$。

你可以从这段排列中去除一个数，问去除哪个数会使得剩下的序列的 record 数最大，当答案不唯一时，输出最小的数。
## 分析
我们可以定义两个数组 $r$ 和 $x$，$r_i=1$ 当且 $a_i$ 是一个 record，否则 $r_i=0$，而 $x_i$ 表示去掉 $a_i$ 后能增加多少个 record 数。

$r$ 数组，对于 $x_i$，我们可以不用直接求,而是可以通过遍历原序列对于每一个 $a_j$ 来间接求得，这个用到了要使一个数 $a_i$ 成为 record，那么序列中在其前面的比 $a_i$ 大的数只能有一个。

举个栗子：给出序列 $5,1,2,4,3$，我们可以通过遍历序列，在遍历到 $1,2,4$ 时分别给 $x_0$ 加一，这样就能得到 $x_0=3$ 了，而遍历到 $3$ 的时候由于 $4$ 和 $5$ 都比 $3$ 大，因此无法对 $x_0$ 进行操作。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+100;
int ax[maxn],r[maxn],x[maxn],n;
int main(){
   cin>>n;
   for(int i=0;i<n;i++)cin>>ax[i];
   if(n==1){
       cout<<ax[0];
       return 0;
   }
   if(n==2){
       cout<<min(ax[0],ax[1]);
       return 0;
   }
   int max1=0,max2;
   r[0]=0;
   for(int i=0;i<n;i++){
       if(i!=0){
          if(ax[i]>max1)
            r[i]=1;
          else
            r[i]=0;
       }
       max1=max(max1,ax[i]);
       x[i]=-r[i];
   }
   int index1,index2;
   max1=0,max2=0;
   if(ax[0]>ax[1]){
       max1=ax[0];
       index1=0;
       max2=ax[1];
       index2=1;
   }
   else{
       max1=ax[1];
       index1=1;
       max2=ax[0];
       index2=0;
   }
   for(int i=2;i<n;i++){
      if(ax[i]>max2&&ax[i]<max1)
        x[index1]++;
      if(ax[i]>max1){
          max2=max1;
          index2=index1;
          max1=ax[i];
          index1=i;
      }
      else if(ax[i]>max2){
          max2=ax[i];
          index2=i;
      }
   }
   int cnt=x[0],ans=ax[0],index=0;
   if(ax[1]>ax[0]){
       cnt=x[1];
       ans=ax[1];
       index=1;
   }
   for(int i=2;i<n;i++){
       if(x[i]>cnt){
           ans=ax[i];
           cnt=x[i];
           index=i;
       }
       else if(x[i]==cnt){
           if(ax[i]<ans){
               ans=ax[i];
               index=i;
           }
       }
   }
   if(index==1){
       if(ax[0]<ax[1]&&x[0]-1==x[1])
         ans=ax[0];
   }
   cout<<ans<<endl;
   return 0;
}
```

---

## 作者：Robin_kool (赞：1)

PS:已经改了中文句号&逗号（）。

考虑计算删除每个 $a_i$ 产生的贡献(互相独立）。

对任意一个 $a_i(1\leq i\leq n)$，都有以下几种情况：

$1$、$a_i$ 本身不操作的情况下就能产生贡献 $1$，因此删除他会让收益 $-1$。

$2$、$a_i$ 前面只有一个比他大的数，记作 $a_j(j\leq i)$，显然删除 $a_j$ 会让收益 $+1$。


以上说的都是能删除某数使得总收益变化的情况。

于是按照题意模拟。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
ll n, a[N], v[N], big, small, maxn = -0x3f3f3f3f, ans;
inline ll read(){
	ll x = 0, m = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') m = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * m;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		write(-x);
		return;
	}
	if(x >= 10) write(x / 10);
	putchar(x % 10 + '0');
}
signed main(){
	//freopen("CF900C.in", "r", stdin);
	//freopen("CF900C.out", "w", stdout);
    n = read();
    for(int i = 1; i <= n; ++ i) a[i] = read();
    for(int i = 1; i <= n; ++ i){
    	if(a[i] > a[big]){
    		-- v[i];
    		small = big, big = i;
		}else if(a[i] > a[small]){
			++ v[big];
			small = i;
		}
	}
	for(int i = 1; i <= n; ++ i){
		if(v[i] > maxn){
			maxn = v[i];
			ans = i;
		}
	}
	write(a[ans]);
	return 0;
}

```

然鹅挂分了。

原因是翻译出锅，最后要输出总收益相等情况下 $a_i$ 最小的数。

显然只需要更改取最大值部分。


```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
ll n, a[N], v[N], big, small, maxn = -0x3f3f3f3f, ans;//注意maxn赋极小值，因为收益可能是负数
inline ll read(){
	ll x = 0, m = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') m = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * m;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		write(-x);
		return;
	}
	if(x >= 10) write(x / 10);
	putchar(x % 10 + '0');
}
signed main(){
	//freopen("CF900C.in", "r", stdin);
	//freopen("CF900C.out", "w", stdout);
    n = read();
    for(int i = 1; i <= n; ++ i) a[i] = read();
    //big表示当前1-(i-1)范围的最大值，small表示次大值
    for(int i = 1; i <= n; ++ i){
    	if(a[i] > a[big]){//如果满足情况1
    		-- v[i];
    		small = big, big = i;//更新最大值和次大值
		}else if(a[i] > a[small]){//如果满足情况2
			++ v[big];
			small = i;//只需要更新次大值
		}
	}
	for(int i = 1; i <= n; ++ i){
		if(v[i] > maxn){
			maxn = v[i];
			ans = i;
		}else if(v[i] == maxn){
			if(a[i] < a[ans]){
				maxn = v[i];
				ans = i;
			}
		}
	}
	write(a[ans]);
	return 0;
}

```

就没了。

---

## 作者：Raymondzll (赞：1)

## CF900C Remove Extra One

考虑每个数删掉后对答案的影响。

如果这个数已经是 ```record``` ，删掉后可以确定答案会先减 $1$。

如果一个数前面只有一个数大于他，那么删掉前面那个数后答案会加 $1$。

没错，就没了。

操作的时候记录最大值和次大值，可以看代码。

```
#include <bits/stdc++.h>
using namespace std;
int n;
int a[100010];
int delta[100010];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	int x=0,y=0;//x=second largest,y=largest
	for(int i=1;i<=n;i++){
		if(a[i]>a[y]){//record now
			x=y;y=i;
			delta[i]--;
		}else if(a[i]>a[x]){//depends on y
			delta[y]++;
			x=i;
		}
	}
	int id=0;delta[0]=-1000000;
	for(int i=1;i<=n;i++){
		if(delta[i]>delta[id]||(delta[i]==delta[id]&&a[i]<a[id]))id=i;
	}
	cout<<a[id];
	return 0;
}

```

---

## 作者：ZLCT (赞：0)

# CF900C Remove Extra One
## 题目翻译
给定一个长度为 $n$ 的排列 $a$，求删除一个元素使这个排列的 record 最多。定义一个 record 为对于一个 $a_i$ 满足所有 $j<i$ 都有 $a_j<a_i$。如果有多组解，输出最小的那一个。
### 树状数组？NO！
~~对于这道题 luogu 标签的树状数组解法，简直就是莴苣炒莴苣——多此一举（多吃一苣）~~\
秉持存在即合理的原则，我们来解释一下这种做法。\
首先对于每个位置 $i$，我们可以分成下面几种情况：
1. 前面所有数字都满足 $a_j<a_i$。
   这种情况无论前后如何删除都不会对它产生影响，只有把这个点删除会产生 $sum_{record}-1$ 的影响。于是这种只需要在 $i$ 位置记录一个 $-1$ 的影响即可。
2. 如果前面有两个或以上大于它，那么这一位无论如何都不会对答案进行贡献，那么就不需要任何操作。
3. 如果前面只有一个数大于它，那么只要把那一个数删除就会对这一位有 $1$ 的贡献，于是假设那一个数为 $a_j$ 只需要在 $j$ 处记录一个 $1$ 的贡献。

最后答案只需要枚举一遍看哪一个数删除的贡献最大。\
（代码就不放了，实在没有人会选择这个）
### 数组？YES！
其实我们观察一下上面树状数组的过程，其实没有任何一步是数组做不了的。所以我们只需要把上面的过程用数组模拟一遍即可。\
具体实现方面，可以存 $2$ 个 `pair` 来维护最大值和次大值及其对应的位置。因为 $p$ 是排列，所以每个元素互不相同，因此直接以最大值和次大值作为下标。\
至于维护最大值和次大值，可以用一个 set 维护，看似多了一个 $\log$ 的复杂度，实际上每次 `set` 的大小大于 $2$ 时就可以把最小值删除，因此复杂度是 $\log_2(2)=1$ 的极小常数，跑的飞起。这样可以少一些分类讨论，使代码更加清晰。
### code
```cpp
#include<bits/stdc++.h>
using namespace std;
set<int>s;
int n,a[112345],ans[112345],maxx=-114514;
int main(){
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>a[i];
    }
    for(int i=1;i<=n;++i){
        if(i>1){
            if(a[i]>*s.rbegin()){
                ans[a[i]]--;
            }else if(s.size()==1||a[i]>*s.begin()){
                ans[*s.rbegin()]++;
            }
        }else{
            ans[a[i]]--;
        }
        s.insert(a[i]);
        if(i>2)s.erase(s.begin());
    }
    for(int i=1;i<=n;++i){
        maxx=max(maxx,ans[i]);
    }
    for(int i=1;i<=n;++i){
        if(ans[i]==maxx){
            cout<<i<<'\n';
            return 0;
        }
    }
}
```

---

## 作者：Nicrobot (赞：0)

提供一种严格 $O(n)$ 的做法。

题目等价于删除一个数使得前缀最大值个数最多。

考虑对于位置 $pos$，对于所有 $<pos$ 的位置，其前缀最大值不变，可以简单处理；对于 $>pos$ 位置 $i$，满足以下两种条件之一：

- $p_i$ 本身是前缀最大值。
- $p_i$ 是前缀次大值，且 **$pos$ 是 $1\sim i$ 的最大值**。

第一种是好统计的。

第二种显然对于每个前缀次大值都只存在一个 $pos$，对每个点维护一个计数器，将对应位置 $+1$ 即可统计。

可以做到严格 $O(n)$。

[AC 提交记录](https://codeforces.com/contest/900/submission/230921694)

---

## 作者：xwh_hh (赞：0)

题解来喽！  
我们发现，对于一个数 $a_i$，如果它前面有 $2$ 个以上比它大的元素，那么它无论如何都不可能成为 record。如果它前面有且仅有 $1$ 个大于它的元素，当且仅当删除比它大的那个元素，它才能成为 record。如果上述都不满足，它本来就是 record。我们用一个数组记录：

- 如果它本来就是 record，记录 $0$。
- 如果它无论如何都不可能成为 record，记录 $-1$。
- 否则，记录比它大、在它前的那个元素位置。  

这样，我们再用一个桶，就可以清楚地知道删每个元素会有多少个 record 了。  
上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a[100005];//数组值 
int b[100005];//它前面唯一一个比它大的，如果没有，存 0，如果有多个，存 -1
int record;
int c[100005];//删一个数，有多少个数可以 变成 record 
int p,q;//当前最大、次大 （编号） 
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",a+i);
	} 
	for(int i=1;i<=n;i++){//打擂台求前面元素最大、次大 
		if(a[p]<a[i]){
			q=p;
			p=i;
			b[i]=0; 
		}else if(a[q]<a[i]){
			q=i;
			b[i]=p;
		}else b[i]=-1;
	}
	for(int i=1;i<=n;i++){//桶 
		if(b[i]==0){
			record++;
		}else if(b[i]!=-1) c[b[i]]++;
	}
	int ans=1;
	for(int i=2;i<=n;i++){
		if(record+c[ans]-(b[ans]==0?1:0)<record+c[i]-(b[i]==0?1:0)) ans=i;//注意，如果a[i]本来就是record，要-1 
		else if(record+c[ans]-(b[ans]==0?1:0)==record+c[i]-(b[i]==0?1:0)&&a[ans]>a[i]) ans=i;
	}
	cout<<a[ans];
	return 0;
}

```

---

