# [ABC072D] Derangement

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc072/tasks/arc082_b

$ 1,2,..,N $ からなる順列 $ p_1,p_2,..,p_N $ が与えられます。 次の操作を何回か ($ 0 $回でもよい) 行うことが出来ます。

操作: 順列で**隣り合う**二つの数を選んでスワップする。

何回か操作を行って、任意の $ 1\ <\ =i\ <\ =N $ に対して $ p_i\ ≠\ i $ となるようにしたいです。 必要な操作の最小回数を求めてください。

## 说明/提示

### 制約

- $ 2\ <\ =N\ <\ =10^5 $
- $ p_1,p_2,..,p_N $ は $ 1,2,..,N $ の順列である。

### Sample Explanation 1

$ 1 $ と $ 4 $ を入れ替え、その後 $ 1 $ と $ 3 $ を入れ替えることで $ p $ は $ 4,3,1,5,2 $ となり、これは条件を満たします。 これが最小回数なので、答えは $ 2 $ となります。

### Sample Explanation 2

$ 1 $ と $ 2 $ を入れ替えれば条件を満たします。

### Sample Explanation 3

初めから条件を満たしています。

## 样例 #1

### 输入

```
5
1 4 3 5 2```

### 输出

```
2```

## 样例 #2

### 输入

```
2
1 2```

### 输出

```
1```

## 样例 #3

### 输入

```
2
2 1```

### 输出

```
0```

## 样例 #4

### 输入

```
9
1 2 4 9 5 8 7 3 6```

### 输出

```
3```

# 题解

## 作者：makerlife (赞：2)

[洛谷题目传送门](https://www.luogu.com.cn/problem/AT3525) | [AT 原题传送门](https://atcoder.jp/contests/abc072/tasks/arc082_b)

## 思路

分析题目可以很简单地得到，如果满足 $p_i=i$ 的条件，那么**交换 $p_i$ 和 $p_{i+1}$ 后得到的结果一定是最优解。**

我们要做的只是从前到后遍历一遍 $p$ 数组，如果 $p_i=i$ 就交换 $p_i$ 和 $p_{i+1}$，同时 $ans$ 累加。

看到楼下有大佬说当 $i=n$ 是需要特判，但其实完全不需要，只要数组开的够大，也不会在交换 $p_n$ 和 $p_{n+1}$ 时发生越界情况。~~但为了严谨也可以特判。~~

## 完整代码

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
int n,p[100010];
int ans=0;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&p[i]);
	}
	for(int i=1;i<=n;i++)
	{
		if(p[i]==i)
		{
			ans++;//答案数量增加
			swap(p[i],p[i+1]);//交换p[i]和p[i+1]
		}
	}
	printf("%d\n",ans);
	return 0;
}

```


---

## 作者：Krimson (赞：2)

似乎用不着这么麻烦?  
只需要从前往后扫一遍就好了,如果出现了$p_i=i$,不难证明$swap(p_i,p_{i+1})$一定是最优策略  




------------
**Code**
```cpp
#include<bits/stdc++.h>
using namespace std;
#define il inline
#define ri register int
#define ll long long
il ll read(){
    bool f=true;ll x=0;
    register char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') f=false;ch=getchar();}
    while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    if(f) return x;
    return ~(--x);
}
il void write(const ll &x){if(x>9) write(x/10);putchar(x%10+'0');}
il void print(const ll &x) {x<0?putchar('-'),write(~(x-1)):write(x);putchar('\n');}
il int max(const int &a,const int &b){return a>b?a:b;}
il int min(const int &a,const int &b){return a<b?a:b;}
int n;
const int MAXN=1e5+7;
int a[MAXN];
int ans;
int main(){
    n=read();
    for(ri i=1;i<=n;++i) a[i]=read();
    for(ri i=1;i<=n;++i){
        if(a[i]==i){
            swap(a[i+1],a[i]);
            ++ans;
        }        
    }
    print(ans);
    return 0;
}
```


---

## 作者：eEfiuys (赞：1)

题目：[AT3525](https://www.luogu.com.cn/problem/AT3525)

很显然，如果 $a_i=i\left(1\leq i<n\right)$，那么交换 $a_i$ 与 $a_{i+1}$ 后，不管之前是否 $a_{i+1}=i+1$，交换后一定为 $a_{i+1}\not=i+1$。

同理，最后如果 $a_n=n$，只需交换 $a_n$ 与 $a_{n-1}$ 即可。

核心代码如下：
```cpp
for(int i=1;i<n;i++)
	if(a[i]==i)ans++,swap(a[i],a[i+1]);
if(a[n]==n)ans++;
```

---

## 作者：μηδσ (赞：1)

## Definition

有一个长度为$n$的数列$p_1,p_2,p_3,\cdots,p_n$

现在有操作可以将相邻的两个元素交换位置

求进行多少次交换过后使得这个数列满足对任意$1\le i \le n$有$p_i\neq i$，求最小交换次数

## Solution

对于每个位置，如果该位置不合法（即$p_i=i$）记录为$false$；对于每个位置，如果该位置合法（即$p_i\neq i$）记录为$true$则相邻两个元素有以下情况

情况一：$true-true$即，两个元素均满足要求，此时不需要置换

情况二：$true-false$（或$false-true$）且$q_i = i,q_{i+1}\neq i,i+1$。此时交换相邻两个元素，便可使得两元素满足要求

情况三：$false-false$此时$q_i=i,q_{i+1}=i+1$，此时交换两个元素便可使得两元素满足要求

于是我们对每个$false$，若此时$i<n$均交换$p_i,p_{i+1}$；若这个位置为$n$则交换$p_n,p_{n-1}$，从左往右遍历。

可见情况二和情况三只需交换一次便可以使得这两个元素满足要求，所以统计情况二和情况三出现的次数即可

## Code

~~~cpp
#include <cstdio>
#include <iostream>
#include <algorithm>

#define il inline
#define rep(i, j, k) for(register long long i = j;i <= k;i++)
#define per(i, j, k) for(register long long i = j;i >= k;i--)

using namespace std;
typedef long long ll;

const int MAXN = 100005;

template <typename T>				//快读 
il void read(T &x){
	x = 0;
	char c = 0;
	T w = 0;
	while(!isdigit(c))
		w |= c == '-', c = getchar();
	while(isdigit(c)) x = x * 10 + (c ^ 48), c = getchar();
	if(w)
		x = -x;
}

int n; 
int a[MAXN];

int main(){
	read(n);
	rep(i, 1, n)
    	read(a[i]);
    int cnt = 0;
    rep(i, 1, n)
        if (a[i] == i){
            cnt++;
            if(i < n && a[i + 1] == i + 1) 
				i++;
        }
    printf("%d\n", cnt);
    return 0;
}
~~~

---

## 作者：little_rubbish (赞：0)

## 思路
因为在一个序列中不存在两个相同的数，所以当 $P_i = i$ 时，交换 $P_i$ 和 $P_{i+1}$ 后 $P_i$ 就不再可能等于 $i$，所以这样既可以达成目标（$P_i \ne i$）,因为只交换了需要交换的数所以是最小次数。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std; 
int n,ans,c;
int a[100010];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++){
		if(a[i]==i){
			ans++;
			i++;
			//swap(a[i],a[i+1]);因为前面有了i++，直接跳过了i+1，所以交不交换都无所谓。
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Fire_Raku (赞：0)

### 题目分析：

因为 $p_i \ne i$，所以这道题可以这样做：循环枚举序列 $p$ 到 $n - 1$，如果 $p_i = i $，那么就把他与下一个数交换，并把交换次数加一，因为这样就可以保证，交换后两个数一定各不等于 $i$，后面的 $p_n$ 需要特判，如果相等，也把交换次数加一。

因为交换后的两个数一定符合条件，所以如果需要交换，可以交换完后，直接把 $i$ 加一，跳过交换好的 $p_i + 1$。

**代码（拒绝抄袭）：**

```cpp
#include<bits/stdc++.h>
using namespace std ;
int ans , n , a[1000010] ; 
int main(){
	cin >> n ; 
	for(int i = 1 ; i <= n ; i++) cin >> a[i] ; 
	for(int i = 1 ; i < n ; i++){
		if(a[i] == i){ //如果需要交换
			ans++ ; //交换次数加一
			swap(a[i] , a[i + 1]) ; //与后面的数交换
			i++ ; //跳过p[i + 1]
		}
	}
	if(a[n] == n) ans++ ; //特判，如果怕数组越界，还是加吧
	cout << ans << endl ; //记得加岛国特有的换行
	return 0 ;
}
```

---

