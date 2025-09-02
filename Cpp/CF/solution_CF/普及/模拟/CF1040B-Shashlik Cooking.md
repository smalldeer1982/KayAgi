# Shashlik Cooking

## 题目描述

### 题目大意：
有$n$个烤串，翻动第$i$根烤串会连带着$max(1,i-k)$到$min(n,i+k)$根烤串翻动，问把所有烤串都翻动一遍最少需要翻动几根烤串

## 样例 #1

### 输入

```
7 2
```

### 输出

```
2
1 6 
```

## 样例 #2

### 输入

```
5 1
```

### 输出

```
2
1 4 
```

# 题解

## 作者：Withershine (赞：2)

看到这道题的第一眼，就想到用分块思想来解决。

## 思路
我们知道，当对任意一个 $i$ 进行翻转时，区间 $[i-k,i+k]$ 内的所有元素都会翻转，每次翻转的总个数为 $2 \times k+1$。

因此，我们可以将所有烤串分成长度为 $len=2 \times k+1$ 的 $block=n \div len$ 块，用数组 $L$ 与 $R$ 来记录每一块的左右值，并像分块操作一样对他进行补块操作。此时需要翻转的次数就是 $block$。

接下来进行判断，当 $n$ **恰好**分成长度为 $len$ 的 $block$ 块时，直接输出每个 $L_i$ 即可。此时第一块与最后一块只翻转了长度为 $k+1$ 的烤串，中间的 $block-2$ 个块充分翻转了中间所有的烤串**一次**。

当 $n$ 没有被**恰好**分成长度为 $len$ 的 $block$ 块时，最后一块的长度 $R_i-L_i+1 \ne len$，其实就是 $n \bmod len$。此时将所有的块向右移动 $\frac{n \bmod len}{2}$ 个单位长度在输出 $L_i$ 即可。这里每个烤串**只翻一遍**，需要注意。

## 代码
```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#include<string>
#include<ctime>
#include<cstring>
#include<algorithm>
#include<climits>
#include<queue>
#include<map>
#include<set>
#include<sstream>
#include<cassert>
#define ll long long
#define inf 0x3f3f3f3f
#define fr(i , a , b) for(ll i = a ; i <= b ; ++i)
#define fo(i , a , b) for(ll i = a ; i >= b ; --i)
#pragma comment(linker , "/stack : 200000000")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;
inline char gchar()
{
    static char buf[1000000] , *p1 = buf , *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf , 1 , 1000000 , stdin) , p1 == p2) ? EOF : *p1++;
}
inline ll read()
{
    ll x = 0 , f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
	  {
        if(ch == '-')
        {
        	f = -1;
		}
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')
	  {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}
ll n , k;
ll L[1005] , R[1005];
signed main()
{
    n = read();
    k = read();
    if(k == 0)//特判
    {
        printf("%lld\n" , n);
        fr(i , 1 , n)
        {
            printf("%lld ", i);
        }
        system("pause");
        return 0;
    }
    ll len = 2 * k + 1;
    ll block = n / len;
    fr(i , 1 , block)
    {
        L[i] = R[i - 1] + 1;
        R[i] = len * i;
    }
    if(R[block] < n)
    {
        block++;
        L[block] = R[block - 1] + 1;
        R[block] = n;
    }
    printf("%lld\n" , block);
    if(n % len != 0)
    {
        ll kkk = n % len;
        fr(i , 1 , block)
        {
            printf("%lld " , L[i] + kkk / 2);
        }    
    }
    else
    {
        fr(i , 1 , block)
        {
            printf("%lld " , (L[i] + R[i]) / 2);
        }
    }
    system("pause");
    return 0;
}
```


---

## 作者：small_turtle (赞：1)

贪心，翻动若干个不相交的长度为 $2k+1$ 的区间，剩余部分额外再加一个，答案就为 $p=\lceil{\frac{n}{2k+1}}\rceil$，起始点为 $n-(2k+1)(p-1)-k-1$。如 $\text{0\color{blue}100\color{red}0010000100}$ 中（$1$ 为翻动点），$(2k+1)(p-1)$ 指翻动 $p-1$ 个完整的区间（红色部分），$-k-1$ 指翻动剩下的半个区间（蓝色部分）。有可能会出现负数，这时候需要特判，最后从起始点每隔 $2k+1$ 输出一次即可。
```cpp
//Time:2023.5.10
#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
const ll inf=0x3f3f3f3f;
const double eps=1e-6;
using namespace std;
 
int n,k,p,l,now;

int main()
{
 	std::ios::sync_with_stdio(false);
 	cin.tie(0);
	scanf("%d%d", &n, &k);
	
	p=(n-1)/(k*2+1)+1;
	printf("%d\n", p);
	
	l=max(n-((2*k+1)*(p-1)+k+1), 0);
	printf("%d ", ++l);
	
	for(int i=2;i<=p;++i)
	{
		l+=k*2+1;
		printf("%d ", min(l, n));
	}
 	return 0;
}
```

---

## 作者：flora715 (赞：1)

###### （p.s）这是第300道ac题，所以还是好好写个题解qwq

### 题意简化
对一个长为n的串进行反转操作。

每次选择一个p点，反转与p距离小于等于k的所有位置，

问使得所有位置都被反转的最小操作次数。

### 思路分析
尽量让每次反转发挥最大的贡献。

首先让第一个翻面，然后每隔2*k个之后再翻一次，

这样保证除了第一个剩下的都是最大化的。

然后就会发现，最后剩下没有翻转的烤串一定小于k个，

因为最后剩下的小于k个，把所有的翻转点右移即可。

### 代码实现
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#include<deque>
#include<cmath>
using namespace std;
typedef long long ll;

void reads(ll &x){ //读入优化（正负整数）
    int fx=1;x=0;char s=getchar();
    while(s<'0'||s>'9'){if(s=='-')fx=-1;s=getchar();}
    while(s>='0'&&s<='9'){x=x*10+s-'0';s=getchar();}
    x*=fx; //正负号
}

/*【B.Shashlik Cooking】
对一个长为n的串进行反转操作，每次选择一个p点，
反转与p距离小于等于k的所有位置，问使得所有位置都被反转的最小操作次数。*/

/*【分析】尽量让每次反转发挥最大的贡献，首先让第一个翻面，然后每隔2*k个之后再翻一次，
这样保证除了第一个剩下的都是最大化的，这样就会发现，最后剩下没有翻转的烤串一定小于k个，
然后把所有的翻转点右移即可，因为小于k个，第一个又是反转的，所有右移可行。*/

int main(){
    ll n,k,now=1; reads(n); reads(k);
    ll ans=(n-1)/(2*k+1)+1; cout<<ans<<endl; 
    ll lastt=n-(1+(2*k+1)*(ans-1)+k); //寻找剩下的个数 
    if(lastt<0) lastt=0; now+=lastt; //右移
    while(ans--){ cout<<now<<" "; now+=2*k+1; }
    return 0;
}
```

---

## 作者：Manki23333333 (赞：0)

感谢审核大大。

## 题意描述：

给定两个正整数 $ n $，$ k $ 和一个数列 $ a $。

最开始数列 $ a $ 都为 $ 0 $。

定义一次操作可以选定一个 $ i $，使得 $ [i - k, i + k] $ 加 $ 1 $，超过区间的忽略不计。

求最少的操作次数使得 $ a $ **正好**全为 $ 1 $。

## 题解：

观察发现，$ n $ 与 $ k $ 的数据范围只有 $1000$，可以尝试 $ O (n^2) $ 或者 $ O (nk) $。

又知道，所有相邻的（即两个操作中间没有其他操作）操作的 $ i $ 的间隔都只能为 $ 2k $。

证明：

考虑有 $ i $，$ j $ 相邻的两个位置 （ $ i < j $ ）。

如果 $ |i - j| > 2k $，那么 $ [i + k, j - k] $ 这段区间没有被覆盖。如果在这段区间再次操作，会导致这个操作的区间和 $ i, j $ 的两个区间覆盖。

如果 $ |i - j| < 2k $，那么 $ i, j $ 的两个区间相互覆盖。

综上所述，命题得证。

所以我们只需要枚举第一个起始点，往后加 $ 2k + 1 $ 跳跃就行了。

细节看代码。

```cpp
#include <bits/stdc++.h>

using namespace std;

int n, k;

int ans = 1e9, ans_i = 1; // ans 要初始化为极大值，ans_i 代表最佳起始点。

int main () {
	cin >> n >> k;
	
	for (int i = 1 ; i <= k + 1 ; i ++) { // 枚举起始点，注意 k + 1 也有可能是起始点。
		int sum = 0;
		
		int j;
		for (j = i ; j <= n ; j += 2 * k + 1) { // 向后枚举操作。
			sum ++;
		}
		
		if (j - (2 * k + 1) + k < n) // 如果这个操作根本满足不了条件，直接跳了。
			continue;
		
		if (sum < ans) { // 如果答案更优，直接记录。
			ans_i = i;
			ans = sum;
		}
	}
	
	cout << ans << endl;
	
	for (int j = ans_i ; j <= n ; j += 2 * k + 1) {
		cout << j << " "; // 向后输出答案。
	}
  
	return 0;
}
```

---

