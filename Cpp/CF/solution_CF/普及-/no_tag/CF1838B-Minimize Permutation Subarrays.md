# Minimize Permutation Subarrays

## 题目描述

You are given a permutation $ p $ of size $ n $ . You want to minimize the number of subarrays of $ p $ that are permutations. In order to do so, you must perform the following operation exactly once:

- Select integers $ i $ , $ j $ , where $ 1 \le i, j \le n $ , then
- Swap $ p_i $ and $ p_j $ .

For example, if $ p = [5, 1, 4, 2, 3] $ and we choose $ i = 2 $ , $ j = 3 $ , the resulting array will be $ [5, 4, 1, 2, 3] $ . If instead we choose $ i = j = 5 $ , the resulting array will be $ [5, 1, 4, 2, 3] $ .

Which choice of $ i $ and $ j $ will minimize the number of subarrays that are permutations?

A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

An array $ a $ is a subarray of an array $ b $ if $ a $ can be obtained from $ b $ by the deletion of several (possibly, zero or all) elements from the beginning and several (possibly, zero or all) elements from the end.

## 说明/提示

For the first test case, there are four possible arrays after the swap:

- If we swap $ p_1 $ and $ p_2 $ , we get the array $ [2, 1, 3] $ , which has 3 subarrays that are permutations ( $ [1] $ , $ [2, 1] $ , $ [2, 1, 3] $ ).
- If we swap $ p_1 $ and $ p_3 $ , we get the array $ [3, 2, 1] $ , which has 3 subarrays that are permutations ( $ [1] $ , $ [2, 1] $ , $ [3, 2, 1] $ ).
- If we swap $ p_2 $ and $ p_3 $ , we get the array $ [1, 3, 2] $ , which has 2 subarrays that are permutations ( $ [1] $ , $ [1, 3, 2] $ ).
- If we swap any element with itself, we get the array $ [1, 2, 3] $ , which has 3 subarrays that are permutations ( $ [1] $ , $ [1, 2] $ , $ [1, 2, 3] $ ).

 So the best swap to make is positions $ 2 $ and $ 3 $ .For the third sample case, after we swap elements at positions $ 2 $ and $ 5 $ , the resulting array is $ [1, 4, 2, 5, 3] $ . The only subarrays that are permutations are $ [1] $ and $ [1, 4, 2, 5, 3] $ . We can show that this is minimal.

## 样例 #1

### 输入

```
8
3
1 2 3
3
1 3 2
5
1 3 2 5 4
6
4 5 6 1 2 3
9
8 7 6 3 2 1 4 5 9
10
7 10 5 1 9 8 3 2 6 4
10
8 5 10 9 2 1 3 4 6 7
10
2 3 5 7 10 1 8 6 4 9```

### 输出

```
2 3
1 1
5 2
1 4
9 5
8 8
6 10
5 4```

# 题解

## 作者：ACtheQ (赞：5)

### 思路

本题由于 $1$ 和 $2$ 对答案的影响是次数最多的，所以考虑把他们俩隔开。

这时候就用最大多数把他们俩隔开就行。

这个数显然为 $n$。

分别用三个变量 $x,y,z$ 统计 $1,2,n$ 在数组的位置。

我么可以用 $l$ 表示 $1,2$ 的左位置，即 $\min(x,y)$。

我么可以用 $r$ 表示 $1,2$ 的右位置，即 $\max(x,y)$。

如果 $l < z < r$ 那么什么也不用做。

![](https://cdn.luogu.com.cn/upload/image_hosting/j1oddubc.png)

如果 $z < l < r$ 那么将 $l$ 和 $z$ 调换。

![](https://cdn.luogu.com.cn/upload/image_hosting/7p4gw9gr.png)

如果 $l < r < z$ 那么将 $z$ 和 $r$ 调换。

![](https://cdn.luogu.com.cn/upload/image_hosting/ffpvfdl4.png)

```c++
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
    	int n;
    	cin>>n;
    	int x,y,z;
    	for(int i=1;i<=n;i++)
    	{
    		int k;
    		cin>>k;
    		if(k==1) x=i;
    		if(k==2) y=i;
    		if(k==n) z=i;
		}
		if(x>y) swap(x,y);
		if(z>y) cout<<y<<" "<<z<<endl;
		else if(z<x) cout<<z<<" "<<x<<endl;
		else cout<<x<<" "<<x<<endl;
	}
    return 0;
}
```

---

## 作者：MrPython (赞：3)

## 题意
本题要求从数组中任选两个数交换一次，使得数组中所有子段中排列的数量最少。

其中，排列指长度为 $s$ 的数组包含 $1,2,3,\dots,s$ 所有元素。

## 解析
首先，$1$ 本身就是一个排列，原数组本身也是一个排列，这都是无法改变的。

那么，对于剩下的排列，其中必须包含 $2$。我们只需要让 $1$ 和 $2$ 之间的距离尽可能的远就可以了。夸张一下，$1$ 在最左端，$2$ 在最右端，那么所有的子串（除了 $\left[1\right]$ 和原数组本身）都会因为少 $1$ 或少 $2$ 而导致无法组成排列。

可惜题目指允许交换一次，这种情况不一定能实现，但我们仍然可以往这条路上想。

除了 $\left[1\right]$ 以外的排列，都必须包含 $1$ 和 $2$，同时不能包含比该数组长度大的数。因此，我们将一个大数 $k$ 放在 $1$ 和 $2$ 中间，这样一个子串若同时包含 $1$ 和 $2$，就也包含这个 $k$ 了。这种时候，除非该串的长度大于等于 $k$，否则它都不是一个排列。

我们直接拿原数组中最大的数 $n$。这样，只需要使得 $1,2,n$ 三者之间的相对位置符合 $n$ 在 $1$ 和 $2$ 中间即可。在这种情况下，只有 $\left[1\right]$ 与原数组能组成排列，将排列数控制在了最小的 $2$。

至于根据相对位置交换，可以暴力解决。若原来的数组就符合这个条件，随便找两个数跟自己交换就能保持这个样子不变。

## 源码
```cpp
#include<bits/stdc++.h>
using namespace std;
using ui=unsigned int;
int main(void){
    ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
    size_t T;
    cin>>T;
    while (T--){
        size_t n;
        cin>>n;
        vector<ui> a(n);
        size_t onepos,twopos,npos;
        for (size_t i=0;i<n;i++) 
            cin>>a[i],
            a[i]==1?onepos=i+1  //记录1, 2, n的位置，用三目压行
            :a[i]==2?twopos=i+1
            :a[i]==n?npos=i+1
            :0;
        if (onepos < twopos && twopos < npos) cout<<twopos<<' '<<npos;
        if (onepos < npos && npos < twopos)   cout<<1<<' '<<1;
        if (twopos < onepos && onepos < npos) cout<<onepos<<' '<<npos;
        if (twopos < npos && npos < onepos) cout<<1<<' '<<1;
        if (npos < onepos && onepos < twopos) cout<<onepos<<' '<<npos;
        if (npos < twopos && twopos < onepos) cout<<twopos<<' '<<npos;
        cout.put('\n');
    }
    return 0;
}
```

---

## 作者：Kedit2007 (赞：2)

### 题意

给定一个长度为 $n$ 的排列，任选两个元素（可以相同）并交换，使得其所有子段中排列（长度不一定为 $n$）的个数最少。

### 思路

首先，我们发现至少有两个排列，分别包含 $[1]$ 和 $[1, 2, ..., n]$，那么我们需要想办法构造一种方法，使得所有子段里面包含的排列只有这两种。

首先，如果一个排列不是 $[1]$，那么它肯定含有 $2$，而如果一个排列不形如 $[1, 2, ..., n]$，那么它肯定不含有 $n$。那么我们只需要让任何一个长度不为 $1$ 或 $n$ 的子段要么不包含 $2$，要么 $2$ 和 $n$ 都包含即可。

要做到这一点，我们只需要保证 $n$ 处于 $1$ 和 $2$ 之间。所以我们只需要找到 $1, 2, n$ 这三个数，并判断是否符合要求，若符合要求，直接随便进行一个原地的操作，如果不符合要求，调换两个元素使之符合要求即可。

### 伪代码参考

```cpp
int n = read();
int pos1, pos2, posn;
for (int i = 1; i <= n; i++)
{
  int t = read();
  if (t == 1) pos1 = i;
  if (t == 2) pos2 = i;
  if (t == n) posn = i;
}

if (pos1 > pos2) swap(pos1, pos2); // 交换一下方便操作

if (posn > pos2) cout << pos2 << ' ' << posn; // 形如 2 1 n, 1 2 n
else if (posn < pos1) cout << posn << ' ' << pos1; // 形如 n 1 2, n 2 1
else cout << "1 1";
```

---

## 作者：luguangxing (赞：2)

这道题是一道思维题，思路主要见下。

## 思路：
- 这道题主要是把 $1$ 和 $2$ 分开。要把他们分开就在他们中间夹一个数。夹的是这个列中最大的一个数，夹完后满足条件的只有 $1$ 和整体了，举个例子：如果这个数是 $9$ 夹在 $1$,$2$ 之间那么除了上面的那 $2$ 种，其他就都不满足了，证明一下因为这个数是列中最大的数，那么想要凑齐一个满足要求的数列就必须要这个数，那么也就只有两种情况了，这样就使得满足条件的列最少。

- 还有 $1$ 种情况就是不用调换了，因为已经满足了最大数在 $1$ $2$ 之间的情况了像这样只要输出两个一样的数就行了，但输出的数要比列中的总个数少。

### 样例解释：

- 解释：$1$ $2$ $3$ 输出是 $2$ $3$ 这个就是把最大的数列在 $1$ $2$ 之间，排完后是 $1$ $3$ $2$ 这就验证了思路。

- 解释：$1$ $3$ $2$ 输出是 $1$ $1$ 这种就对应上面思路已经满足了。

## 结论：

好通过上面的思路我们就能得出这样一个结论：要把最大数夹在 $1$ $2$ 之间。

### 代码展示：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t,n,a,d1,d2,dn;
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a;
			if(a==1) d1=i;// 1 的位置 
			if(a==2) d2=i;// 2 的位置 
			if(a==n) dn=i;// 最大值 的位置 
		}
		if(dn>d1&&dn>d2){//最大值 在 1 2 的右边 
			if(d1>d2){
				cout<<d1<<" "<<dn<<endl;// 2 1 最大值的情况 
			}
			else{
				cout<<d2<<" "<<dn<<endl;// 1 2 最大值的情况 
			}
		}else if(dn<d1&&dn<d2){//最大值 在 1 2 的左边 
			if(d1<d2){
				cout<<d1<<" "<<dn<<endl;// 1 2 最大值的情况 
			}else{
				cout<<d2<<" "<<dn<<endl;// 2 1 最大值的情况 
			}
		}else{
			cout<<2<<" "<<2<<endl;//最大值已在 1 2 之间
		} 
	} 
	return 0;
}
```

---

## 作者：QingDeng_Star (赞：1)

题目翻译很清楚了，不讲。
## 思路
可以从样例中得出我们要让 $1$ 和 $2$ 相隔的越远越好，而且要在 $1$ 和 $2$ 之间放一个本序列中最大的一个数，分情况讨论即可。

## AC Code


```cpp
#include<bits/stdc++.h>//万能头不用说了吧 
using namespace std;
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
    	int n,a,b,c;
    	cin>>n;
    	for(int i=1;i<=n;i++)
    	{
    		int m; 
    		cin>>m;//输入 
    		if(m==1) 
				a=i;
    		if(m==2) 
				b=i;
    		if(m==n) 
				c=i;
			//进行分类 
		}
		if(a>b) 
			swap(a,b);
		if(c>b) 
			cout<<b<<" "<<c<<endl;
		else if(c<a) 
			cout<<c<<" "<<a<<endl;
		else 
			cout<<a<<" "<<a<<endl;
		//判断输出 
	}
    return 0;
}//完结散花！ 
```

---

## 作者：__hjwucj__ (赞：0)

# 题解：CF1838B Minimize Permutation Subarrays

[题目传送门](/problem/CF1838B)

## 思路

构造题。

因为 $1$ 和 $2$ 的影响是最大的，所以考虑隔开他们。

这个时候就用 $n$ 把他们隔开就行了。

用变量 $a,b,c$ 来表示 $1,2,n$ 的位置。

- 如果 $a<c<b$，啥也不用干。
- 如果 $c<a<b$，将 $a,b$ 调换。
- 如果 $a<b<c$ 那么将 $c$ 和 $b$ 调换。

## 代码

详见[提交记录。](https://mirror.codeforces.com/problemset/submission/1838/278383791)

---

## 作者：xujingyu (赞：0)

## 题意

有 $n$ 个数组成的排列，若有一个串长度为 $p$ 且包含 $1$ 到 $p$ 中所有数，他们就会~~搞在一起~~，这是我们所不希望的。所以，要交换两个数的位置，使得搞在一起的数的组数尽量少。

题目中排列，据度娘所述再又我转述就是一个数的全排列，即样例三中的前三个数 $1,3,2$ 就是排列。

## 解法

根据排列定义，易得一定有俩排列存在，分别是 $[1]$ 和 $[p_1,p_2,\dots,p_n]$。

那么，第一眼，把 $1$ 支走不就行了……

所以我一开始的做法是把 $1$ 和 $2$ 分开，即可，但是被上述 $1,3,2$ 这个样例就哈克了……

所以~~我是废物~~，要把 $2$ 支的越远越好。

多远？~~我也不知道~~那就弄到最右边吧。

这时又被哈克了：

```
5
4 5 1 3 2
```

那咋整啊，最右边也可能跟 $1$ 搞上。

~~再给我两分钟，让我把这题想一想……~~

那就把 $n$ 弄到 $1$ 和 $2$ 之间他俩就不能搞了，因为他俩想在一起组成排列就一定要包含 $n$，包含 $n$ 就一定要包含全部排列，而本来就一定有这个排列。

所以，把 $n$ 弄到 $1$ 和 $2$ 中间，如果他们之间没有位置，就根据情况交换 $1$ 和 $n$ 或 $2$ 和 $n$ 啦……

不过我比较懒，直接当 $1$ 和 $2$ 之间没有位置算了。

具体，设 $x$ 数所对应的下标是 $a_x$。

* 若 $n$ 在 $1$ 和 $2$ 左边，就交换 $a_n$ 和 $\min(a_1,a_2)$；
* 若 $n$ 在 $1$ 和 $2$ 右边，就交换 $a_n$ 和 $\max(a_1,a_2)$；
* 如果本来就在中间，就不用换了，输出两个一样的数，自己跟自己交换位置肯定还是那个排列啦。


```cpp
#include <bits/stdc++.h>
using namespace std;

int t,n,p[200001],one,two,last;

signed main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		for(int i = 1;i <= n;i++)
		{
			scanf("%d",&p[i]);
			if(p[i] == 1) one = i;//存下标
			if(p[i] == 2) two = i;
			if(p[i] == n) last = i;
		}
		if((one < last && last < two) || (two < last && last < one)) printf("1 1\n");//中间
		else if(last < one && last < two) printf("%d %d\n",last,min(one,two));
        //在左边,判断条件二选一即可,这里这么写是为了好看
		else printf("%d %d\n",max(one,two),last);
        //在右边
	}
	return 0;
}
```

---

## 作者：我梦见一片焦土 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF1838B)

---

# 思路：
首先，不管怎么交换，$1$ 和原数组这两个排列组合一定会存在，只选1和全选，那么我们的目的就是让其他的组合尽可能不出现。

我们来看最容易出现的排列组合是 $[1,2]$，所以 $1$ 和 $2$ 只要不挨在一起，就不会出现 $[1,2]$。

对于长度为 $k$，$n \gt k \gt 2 k$ 的排列组合，它的子序列一定要包含 $1$ 和 $2$，且 $1,2$ 之间不能包含比 $k$ 大的数字，所以如果我们将最大的 $n$ 放在 $1,2$ 之间，那么一定无法形成长度为 $k$ 的排列组合。

答案就很简单了，找到 $1,2,n$ 的位置，判断他们的位置，把 $n$ 放到 $1$ 和 $2$ 之间。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10;
const int INF=0x3f3f3f3f;
int T,n,one,two,mx;
signed main(){
    cin>>T; 
    while(T--){
        cin>>n;
        for(int i=1,a;i<=n;i++){
            cin>>a;
            if(a==1){
                one=i;
            }else if(a==2){
                two=i;
            }else if(a==n){
                mx=i;
            }
        }
        if(mx>one&&mx>two){
            cout<<mx<<' '<<max(one,two)<<endl;
        }else if(mx<one&&mx<two){
            cout<<mx<<' '<<min(one,two)<<endl;
        }else{
            cout<<"1 1"<<endl;
        }
    }
    return 0;
}
```
完结撒花~

---

## 作者：HsNu1ly7_ (赞：0)

## 思路

让排列数量最小的方案显然与数字 $1$ 和 $2$ 的位置有关。所以我们要让 $1$ 和 $2$ 的距离尽量大。

如果最大的数字的下标大于数字 $1$ 的下标且小于数字 $2$ 的下标那么就什么都不做，否则最大的数字的下标小于数字 $1$ 的下标，就将其交换，最大数字的下标大于数字 $2$ 的下标时同理。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std ;

void solve (){
	int n ;
	int arr[200010] = {} ;
	int idx1 , idx2 ;
	int idxn ;
	int l , r ;
	int ansl , ansr ;

	cin >> n ;

	for ( int i = 1 ;i  <= n; i++ ){
		cin >> arr[i] ;
		if ( arr[i] == 1 ) idx1 = i ;
		if ( arr[i] == 2 ) idx2 = i ;
		if ( arr[i] == n ) idxn = i ;
	}

	l = min ( idx1 , idx2 ) ;
	r = max ( idx1 , idx2 ) ;

	if ( idx1 > idx2 ) swap ( idx1 , idx2 ) ;

	if ( idxn > idx2 ){
		ansl = idx2  ;
		ansr = idxn ;
	}else if ( idxn < idx1 ){
		ansl = idxn ;
		ansr = idx1 ;
	}else{
		ansl = 1 ;
		ansr = 1 ;
	}

	cout << ansl << " " << ansr << '\n' ;
	return ;
}

signed main (){
	ios::sync_with_stdio(0) ;
	cin.tie(0) ;
	cout.tie(0) ;
	int _ ;
	cin >> _ ;
	while ( _-- ){
		solve () ;
	}
	return 0 ;
}
```

---

## 作者：P_VICVIC_R (赞：0)

~~简单思考题~~

---

## 题意简述

给你一个序列，让你交换其中的两个元素，使得该序列的**子段**中的**排列**最少。

## 思路

首先最小的排列 $[1]$ 和最大的排列 $[1,2,3,4\dots n]$ 是一定存在的。（注：下文我管这俩货叫“必然存在排列”，其余叫“非必然存在排列”。）

我们发现：

1. 除了最小的排列 $[1]$，其余的任意排列都有数字 $2$。

2. 除了最大的排列 $[1,2,3,4\dots n]$，其余的任意排列都没有有数字 $n$。

那么我们将数字 $n$ 卡在数字 $1$ 和数字 $2$ 之间，所有想构成**非必然存在排列**的**子段**，从 $1$ 到 $2$ 时就一定会经过不该存在的 $n$。换句话说，该序列将不存任何的**非必然存在排列**。

所以找一下 $1,2,n$ 三个值的位置，保证 $n$ 在 $1,2$ 之间就行了。

对于已经满足的，除了 $1,2,n$ 三个值的位置，随便换就行。

## 简单的代码主要部分

```
for(int i=1;i<=n;i++){
	int x; cin>>x;
	P1=(x==1?i:P1);
	P2=(x==2?i:P2);
	Pn=(x==n?i:Pn);
}
if(Pn>max(P1,P2))
	cout<<max(P1,P2)<<" "<<Pn;
else if(min(P1,P2)>Pn)
	cout<<min(P1,P2)<<" "<<Pn;
else
	cout<<"1 1";//省事直接换两个相同的点（相当于没换）
```

---

## 作者：aeiouaoeiu (赞：0)

首先发现至少有两个排列：$[1,1]$ 和 $1$ 至 $n$ 的排列。剩下的排列必然包含 $2$，所以我们可以在 $1$ 和 $2$ 之间放一个 $n$，使其只能得到上述两个排列，分讨即可。
```cpp
#include<bits/stdc++.h>
#define pb push_back
#define mp make_pair
using namespace std;
typedef long long ll;
const int maxn=300007;
const ll inf=1145141919810ll,p=998244353;
ll n,a[maxn],i1,i2,i3;
int main(void){
	ios::sync_with_stdio(false);
	cin.tie(0);
	ll T=1;
	cin>>T;
	for(int tcs=1;tcs<=T;tcs++){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			if(a[i]==1) i1=i;
			else if(a[i]==2) i2=i;
			else if(a[i]==n) i3=i;
		}
		if(i1<i2){
			if(i2<i3) cout<<i2<<" "<<i3<<"\n";
			else if(i3<i1) cout<<i1<<" "<<i3<<"\n";
			else cout<<"1 1\n";  //表示不用调换
		}else{
			if(i3<i2) cout<<i2<<" "<<i3<<"\n";
			else if(i1<i3) cout<<i1<<" "<<i3<<"\n";
			else cout<<"1 1\n";
		}
	}
	return 0;
}
```

---

## 作者：FinderHT (赞：0)

### 题意简述：

给你一个长度为 $n$ 的数组，交换数组中的任意两个元素，让最后数组中产生的子数组中含有的排列数量最小。

### 思路分析：

我们设 $x_i$ 为 $i$ 在数组中的位置。不难发现，只选 $1$ 或选全部的数可以使排列数更小，我们只要找到 $1 , 2 , n$ 的位置$x_1 , x_2 , x_n$，然后把 $x_n$ 插入到 $x_1$ 和 $x_2$ 之间即可。证明：$x_n$ 在 $x_1$ 和 $x_2$ 之间，则唯一的排列子数组是 $[x_1,x_1]$ 和 $[1,n]$，这两个子数组将始终是排列，因此排列数是最小的。

为了实现这一点，我们要考虑 $3$ 种情况：

1. 如果 $x_n$ 位于 $x_1$ 和 $x_2$ 之间，将 $x_1$ 和 $x_2$ 互换。
2. 如果 $x_n < x_1 , x_2$，将 $x_n$ 与 $x_1 , x_2$中较小的那个交换。
3. 如果 $x_n > x_1 , x_2$，将 $x_n$ 与$x_1 , x_2$中较大的那个交换。

### Code：

```cpp
#include<bits/stdc++.h>
#define gt getchar
#define pt putchar
#define ll long long
#define ull unsigned long long
using namespace std;
const int MAXN=2e5+5;
int x[MAXN];
inline void solve(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int a;
		scanf("%d",&a);
		x[a]=i;//储存
	}
	if(x[n]<min(x[1],x[2]))//情况2
		printf("%d %d\n",x[n],min(x[1],x[2]));
	else if(x[n]>max(x[1],x[2]))//情况3
		printf("%d %d\n",x[n],max(x[1],x[2]));
	else{//情况1
		printf("%d %d\n",x[1],x[2]);
	}

}
signed main(){
	int T;
	scanf("%d",&T);
	while(T--)
		solve();
	return 0;
}
```

# The End！

---

