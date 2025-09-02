# [ABC350C] Sort

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc350/tasks/abc350_c

$ (1,2,\ldots,N) $ の並び替えである数列 $ A=(A_1,\ldots,A_N) $ が与えられます。  
 次の操作を $ 0 $ 回以上 $ N-1 $ 回以下行うことで、$ A $ を $ (1,2,\ldots,N) $ にしてください。

- 操作：$ 1\leq\ i\ <\ j\ \leq\ N $ を満たす整数の組 $ (i,j) $ を自由に選ぶ。$ A $ の $ i $ 番目と $ j $ 番目の要素を入れ替える。
 
なお、制約の条件下で必ず $ A $ を $ (1,2,\ldots,N) $ にできることが証明できます。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ (A_1,\ldots,A_N) $ は $ (1,2,\ldots,N) $ の並び替えである
- 入力は全て整数である
 
### Sample Explanation 1

操作により数列は次のように変化します。 - 最初 $ A=(3,4,1,2,5) $ である。 - $ 1 $ 回目の操作で $ 1 $ 番目の要素と $ 3 $ 番目の要素を入れ替える。$ A=(1,4,3,2,5) $ になる。 - $ 2 $ 回目の操作で $ 2 $ 番目の要素と $ 4 $ 番目の要素を入れ替える。$ A=(1,2,3,4,5) $ になる。 この他、次のような出力でも正解とみなされます。 ``` 4 2 3 3 4 1 2 2 3 ```

## 样例 #1

### 输入

```
5
3 4 1 2 5```

### 输出

```
2
1 3
2 4```

## 样例 #2

### 输入

```
4
1 2 3 4```

### 输出

```
0```

## 样例 #3

### 输入

```
3
3 1 2```

### 输出

```
2
1 2
2 3```

# 题解

## 作者：lutaoquan2012 (赞：5)

## 题意：
给你一个长度为 $n$ 的数组，保证这里面的数字都是不重复的并且 $1\le a_i\le n$。

现在在我们通过把数组上的两个位置交换，让这个数组有序。

## 思路：
我们看到这道题 $n$ 的范围很大，肯定不能 $O(n^2)$，所以我们尝试 $O(n)$。

我们记录一个 $a$ 数组，代表这个数 $i$ 在给定数组的 $a_i$ 这个位置。

在记录一个 $b$ 数组，代表在给定数组中第 $i$ 个数是 $b_i$。

```
3
3 1 2
a: 2 3 1
b: 3 1 2
```

最后我们希望通过调整，把 $a_i$ 的值改为 $i$，把 $b_i$ 调整为 $i$。

我们可以遍历一遍 $1$ 到 $n$，看看这个 $a_i$ 是不是 $i$，如果不是的话，我们调整现在数组上 $i$ 和 $a_i$ 这两个位置。

## 代码：
```cpp
//
// Created by 55062 on 2024/4/20.
//
#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
ll n,ans,x[200010],y[200010],xx,a[200010],b[200010];
int main() {
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>xx;
        a[xx]=i;
        b[i]=xx;
    }
    for(int i=1;i<=n;i++){
        if(a[i]!=i){
            x[++ans]=i;
            y[ans]=a[i];
            ll xx=b[i];
            swap(b[a[i]],b[i]);
            swap(a[xx],a[i]);
        }
    }cout<<ans<<endl;
    for(int i=1;i<=ans;i++)cout<<x[i]<<" "<<y[i]<<endl;
    return 0;
}
```

---

## 作者：qhr2023 (赞：2)

## 思路

一道模拟？

用 $a_i$ 表示下标 $i$ 的数，$now_i$ 表示数 $i$ 现在的下标置。遍历 $a$，当下标 $i$ 和数 $a_i$ 不对应时，将 $i$ 和 $now_i$ 在 $a$ 中完成交换，并统计答案，更新 $now$ 数组，这样复杂度就是线性了，具体实现请看代码。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n, a[N], now[N], x[N], y[N], ans; 
int main(){
	cin >> n;
	for(int i=1; i<=n; i++) 
		cin >> a[i], now[a[i]]=i; // 预处理now
	for(int i=1; i<=n; i++)   
		if(a[i]!=i){
			int j=now[i];
			x[++ans]=i, y[ans]=j;
			swap(a[i], a[j]);
			now[i]=i, now[a[j]]=j;
		}
	cout << ans << '\n';
	for(int i=1; i<=ans; i++)
		cout << x[i] << ' ' << y[i] << '\n';
	return 0; 
}
```

---

## 作者：unordered_yao (赞：1)

## 思路

这道题很像插入排序，如果你用插入排序记录方案做这道题，可能会爆栈。这是因为递归次数太多，加之数组 $S$ 太大。

那我们应该怎么做这道题呢？题目要求输入的序列只有 $1$ 至 $N$ 这些数。我们可以准备一个期望序列，也就是这个序列的升序序列，令这个升序序列为 $h$，第 $i$ 项表示数字 $i$，将这个序列的 $h_i$ 与 $S_i$ 对应起来。

如果 $h_i$ 小于 $S_i$，我们就将 $h_i$ 的值所在的数组 $S$ 的位置与 $S_i$ 替换。那 $h_i$ 的值要循环 $S$ 数组找一遍？那肯定不行，会超出时间限制。因为数字最大到 $N$，也就是最大到 $2\times 10^5$，我们只需要开个桶，输入的时候记录以下坐标即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10,M = 2e6+10;
int s[N],h[N],id[N];
struct node{
	int l,r;
}a[N];
int w;
int main(){
    int n;
	cin >> n;
	for(int i=0;i<n;i++){
		cin >> s[i];
		id[s[i]] = i;
		h[i] = i+1;
	}
	//for(int i=1;i<=n;i++) cout << id[i] << ' ';
	for(int i=0;i<n;i++){
		if(s[i]!=h[i]){
			a[w++] = {i,id[h[i]]};
			int t = s[i],r = h[i];
			swap(s[i],s[id[h[i]]]);
			swap(id[t],id[h[i]]);
		}
	}
	cout << w << '\n';
	for(int i=0;i<w;i++){
		cout << a[i].l+1 << ' ' << a[i].r+1 << '\n';
	}
    return 0;
}
```

---

## 作者：Harrylzh (赞：1)

## 题意

给定一个 $1$ 到 $n$ 的排列，交换其中两个数不超过 $n-1$ 次，使得数组有序。

## 思路

第 $i$ 次把 $i$ 移到第 $i$ 个位置上，这样前 $i$ 个数有序，后面的数又可以组成一个此问题，直到数组有序。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n;
long long a[1000000+5];
long long gs[1000000+5];//第i个数的位置
long long ansx[1000000+5];
long long ansy[1000000+5];
long long cur=0;
int main()
{
	scanf("%lld",&n);
	for(long long i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		gs[a[i]]=i;
	}
	for(long long i=1;i<=n;i++)
	{
		if(gs[i]!=i)
		{
			++cur;
			ansx[cur]=min(gs[i],i);
			ansy[cur]=max(gs[i],i);//储存答案
			long long t=a[i];
			swap(a[gs[i]],a[i]);//交换
			gs[t]=gs[i];
			gs[i]=i;//更新位置
		}
	}
	printf("%lld\n",cur);
	for(long long i=1;i<=cur;i++)
	{
		printf("%lld %lld\n",ansx[i],ansy[i]);
	}
	return 0;
}
```

---

## 作者：maokaiyu (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc350_c)
## 思路
由于题目限制了交换次数，但我们关注到 $a_i$ 各不相同且小于等于 $n$。所以只需要对每一位遍历，如果 $a_i$ 不是 $i$，就将 $a_i$ 与值为 $i$ 的位置交换，否则就不交换，至多交换 $n - 1$ 次。
## 做法
用 $pos_i$ 表示值为 $i$ 的元素所在的位置，之后交换就好。
## AC Code
```cpp
#include<bits/stdc++.h>
#define pb push_back
#define SZ(x) (int)x.size()
#define fi first
#define se second
#define all(x) x.begin(),x.end()
#define be(x) x.begin()
#define en(x) x.end()
using namespace std;
typedef long long LL;
typedef int I;
I n,a[200010],k,pos[200010];
pair<I,I>r[200010];
I main(){
	scanf("%d",&n);
	for(I i = 1;i <= n;i++){
		scanf("%d",&a[i]);
		pos[a[i]] = i;//记录元素位置 
	}
	for(I i = 1;i <= n;i++){
		if(a[i] == i){//不需要交换 
			continue;
		}else{
			I x = pos[i],y = pos[a[i]];//原来的位置 
			r[++k].fi = i,r[k].se = pos[i];//需要交换的位置 
			pos[a[i]] = pos[i],pos[i] = i;//交换 
			swap(a[x],a[y]);//交换位置 
		}
	}
	printf("%d\n",k);
	for(I i = 1;i <= k;i++){
		printf("%d %d\n",r[i].fi,r[i].se);
	}
	return 0;
}
```

---

## 作者：OIer_Tan (赞：0)

[题目传送门](https://luogu.com.cn/problem/AT_abc350_c)

我是菜狗，为什么赛时切不了逆序对，自闭了。

## 题意

给你 $1\sim N$ 的排列 $A=(A_1,\ldots,A_N)$。
通过在 $0$ 和 $N-1$ 之间执行以下操作 (包括首尾两次)，将 $A$ 变换成 $(1,2,\ldots,N)$：

- 操作：选择任意一对整数 $(i,j)$，使得 $1\leq i < j \leq N$。在 $A$ 的第 $i$ 位置和第 $j$ 位置交换元素。

可以证明，在给定的约束条件下，总是可以将 $A$ 变换成 $(1,2,\ldots,N)$。

## 思路

可以用归并排序或者树状数组来做，但是有更快的方法。

由于 $A$ 一定为 $1\sim N$ 的排列，所以可以使用下面的方法：

- 在 $i=1,2,...,N$ 中，如果 $A_i\ne i$，交换 $A_i$ 和 $A_{A_i}$。

由于 $A_i$ 在每次交换后都会移动到正确的位置，所以可以证明最多只需 $N-1$ 次交换就能完成。

这样，总时间复杂度为 $O(N)$。

## 代码

```cpp
#include<bits/stdc++.h>

using namespace std ;

typedef long long ll ;
typedef unsigned long long ull ;
typedef long double ld ;

const ll N = 2e5 + 5 ;

ll n , a [N] ;

vector <pair<ll,ll>> ans ;

int main ()
{
	cin >> n ;
	for ( ll i = 1 ; i <= n ; i ++ )
	{
		cin >> a [i] ;
	}
	for ( ll i = 1 ; i <= n ; i ++ )
	{
		while ( i != a [i] )
		{
			ans.emplace_back ( make_pair ( min ( i , a [i] ) , max ( i , a [i] ) ) ) ;
			swap ( a [i] , a [a [i]] ) ;
		}
	}
	cout << ans.size () << endl ;
	for ( auto x : ans )
	{
		cout << x.first << " " << x.second << endl ;
	}
	return 0 ;
}
```

---

