# Dominant Piranha

## 题目描述

There are $ n $ piranhas with sizes $ a_1, a_2, \ldots, a_n $ in the aquarium. Piranhas are numbered from left to right in order they live in the aquarium.

Scientists of the Berland State University want to find if there is dominant piranha in the aquarium. The piranha is called dominant if it can eat all the other piranhas in the aquarium (except itself, of course). Other piranhas will do nothing while the dominant piranha will eat them.

Because the aquarium is pretty narrow and long, the piranha can eat only one of the adjacent piranhas during one move. Piranha can do as many moves as it needs (or as it can). More precisely:

- The piranha $ i $ can eat the piranha $ i-1 $ if the piranha $ i-1 $ exists and $ a_{i - 1} < a_i $ .
- The piranha $ i $ can eat the piranha $ i+1 $ if the piranha $ i+1 $ exists and $ a_{i + 1} < a_i $ .

When the piranha $ i $ eats some piranha, its size increases by one ( $ a_i $ becomes $ a_i + 1 $ ).

Your task is to find any dominant piranha in the aquarium or determine if there are no such piranhas.

Note that you have to find any (exactly one) dominant piranha, you don't have to find all of them.

For example, if $ a = [5, 3, 4, 4, 5] $ , then the third piranha can be dominant. Consider the sequence of its moves:

- The piranha eats the second piranha and $ a $ becomes $ [5, \underline{5}, 4, 5] $ (the underlined piranha is our candidate).
- The piranha eats the third piranha and $ a $ becomes $ [5, \underline{6}, 5] $ .
- The piranha eats the first piranha and $ a $ becomes $ [\underline{7}, 5] $ .
- The piranha eats the second piranha and $ a $ becomes $ [\underline{8}] $ .

You have to answer $ t $ independent test cases.

## 说明/提示

The first test case of the example is described in the problem statement.

In the second test case of the example, there are no dominant piranhas in the aquarium.

In the third test case of the example, the fourth piranha can firstly eat the piranha to the left and the aquarium becomes $ [4, 4, 5, 4] $ , then it can eat any other piranha in the aquarium.

## 样例 #1

### 输入

```
6
5
5 3 4 4 5
3
1 1 1
5
4 4 3 4 4
5
5 5 4 3 2
3
1 1 2
5
5 4 3 5 5```

### 输出

```
3
-1
4
3
3
1```

# 题解

## 作者：ttq012 (赞：2)

这个题还是很有意思的。

**第一部分：题目大意**

给定一个数组 $a$，现在定义一次对于 $i$ 的操作为：如果 $a_{i-1}$ 或者 $a_{i+1} < a_i$，那么删除 $a_{i-1}$ 或者 $a_{i+1}$，并且让 $a_i = a_i + 1$。现在要求你求出一个数 $i$ 满足进行 $n-1$ 次对于 $i$ 的操作之后，只剩下 $a_i$ 一个数。如果这样的 $i$ 不存在那么输出 $-1$。

**第二部分：思路**

小清新签到题。

我们定义 $mx$ 为序列 $a$ 中的最大值。

然后分类讨论即可：

如果 $n= 1$，也就是数组中只有一个元素，那么 $1$ 号元素就是满足条件的。

如果 $a_1 = mx$，并且 $a_2 < a_1$，那么可以删除 $a_2$，这样 $a_1$ 就成为了最大的，满足条件。

如果 $a_n = mx$，并且 $a_{n-1} < a_n$，那么可以删除 $a_{n-1}$，这样 $a_n$ 成为了最大的，满足条件。

如果 $a_i(2\le i\le n-1) = mx$，并且 $a_{i-1} < a_i$ 或者 $a_{i+1} < a_i$ 那么就可以删除 $a_{i-1}$ 或者 $a_{i+1}$，$a_i$ 成为最大的，满足条件。

否则都不满足条件。

时间复杂度 $O(\sum n)$。

**第三部分：代码**

```cpp
#include <bits/stdc++.h>

using namespace std;

int a[1000010];

signed main() {
    int t;
    cin >> t;
    while (t --) {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i ++)
            cin >> a[i];
        int mx = (*(max_element(a + 1, a + n + 1)));
        if (n == 1) puts("1");
        else if (a[1] == mx && a[2] != mx) puts("1");
        else if (a[n] == mx && a[n - 1] != mx) printf ("%d\n", n);
        else {
            for (int i = 2; i < n; i ++)
                if (a[i] == mx && (a[i + 1] != mx || a[i - 1] != mx)) {
                    printf ("%d\n", i);
                    goto nlbl;
                }
            puts("-1");
        }
        nlbl:;
    }
    return 0;
}

```



---

## 作者：Natsume_Rin (赞：2)

这一题真的巨水。

首先，$a_i$ 最大的鱼肯定更具有优势。

如果可以找到一个位置 $pos$ 使得 $a_{pos}=max$ 且 $a_{pos-1}\neq max$ 或者 $a_{pos+1}\ne max$。

```cpp
#include<bits/stdc++.h>
#define RI register int
using namespace std;
const int MAXN = 3e5+5;
int q, n, a[MAXN];
int maxn, maxid;
int minn;
bool pd;
int main(){
	scanf("%d",&q);
	while(q--){
		maxn=0, pd=1;
		scanf("%d",&n);
		for(RI i=1;i<=n;++i) {scanf("%d",&a[i]);maxn=max(maxn,a[i]);}
		a[0]=a[n+1]=maxn;
		for(RI i=1;i<=n;++i){
			if(a[i]==maxn&&(a[i+1]!=maxn||a[i-1]!=maxn)){
				printf("%d\n",i);
				pd=0;
				break;
			}
		}
		if(pd) 
		printf("-1\n");
	}
	return 0;
}

```

---

## 作者：断清秋 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1433C)

显然体积最大的鱼最有优势。如果只有一条体积最大的鱼，那么答案就是它。

但是可能有很多条体积最大的鱼。那么体积最大，且能够吃掉别的鱼的鱼就是答案。

那么只需要找到所有体积最大的鱼，然后按照条件枚举它左右的鱼是否体积都比它小即可。

时间复杂度 $O(tn)$，但是实际上跑不满，可以通过本题。

代码：
```cpp
#include<bits/stdc++.h>
#include<iostream>
#define ll long long
#define back return
#define ri register int 
using namespace std;
int read()
{
	int x=0,f=1;
    char ch=getchar();
	while(!isdigit(ch))
    {
        if (ch=='-') 
            f=-1;
        ch=getchar();
    }
	while(isdigit(ch))
    {
        x=x*10+ch-48;
        ch=getchar();
    }
	back x*f;
}
bool flag;
int t,n,a[300005];
int main()
{
	cin>>t;
	while(t--)
	{
		flag=0;
		int maxx=-1e9;
		n=read();
		a[0]=a[n+1]=1e9;
		for(ri i=1;i<=n;i++)
		{
			a[i]=read();
			maxx=max(a[i],maxx);
		}
		for(ri i=1;i<=n;i++)
			if(a[i]==maxx)
				if(a[i]>a[i-1]||a[i]>a[i+1])
				{
					flag=1;
					cout<<i<<endl;
					break;
				}		
		if(flag==0)
			cout<<-1<<endl;
	}
    back 0;
}
```

---

## 作者：luosw (赞：0)

### 题目描述

- 给定一个长度为 $n$ 的序列 $a$。
- 对于每一个 $i$，当 $a_{i±1}$ 存在且 $a_{i±1}<a_i$ 的时候，可以删除 $a_{i±1}$ 并且 $a_i\gets a_i+1$。
- 问可不可以通过这些操作，使得序列最后只剩一个值。

### 题目分析

显然，当输入的 $a_i$ 全部相等的时候，绝对不可以找出，因此输出 $\texttt{-1}$。

下面，每一次我们先找出 $a$ 的最大值，并找到满足这样条件的一个位置 $i$：$a_{i+1}\neq a_i ||a_{i-1}\neq a_i$。这样就可以满足条件，则直接输出 $i$ 即可。

时间复杂度：$\mathcal O(t\cdot n)$。

### 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

#ifndef ONLINE_JUDGE
#    define debug
#endif

namespace luosw {
namespace IO {
    template < typename T >
    inline T read() {
        T    ret = 0, f = 1;
        char ch = getchar();
        while (ch < '0' || ch > '9') {
            if (ch == '-')
                f = -f;
            ch = getchar();
        }
        while (ch >= '0' && ch <= '9')
            ret = ret * 10 + ch - '0', ch = getchar();
        return ret * f;
    }
    template < typename T >
    void write(T x) {
        if (x < 0) {
            putchar('-');
            x = -x;
        }
        T y = 10, len = 1;
        while (y <= x) {
            y *= 10;
            len++;
        }
        while (len--) {
            y /= 10;
            putchar(x / y + 48);
            x %= y;
        }
    }
    template < typename T >
    void write(T x, bool flag) {
        if (x < 0) {
            putchar('-');
            x = -x;
        }
        T y = 10, len = 1;
        while (y <= x) {
            y *= 10;
            len++;
        }
        while (len--) {
            y /= 10;
            putchar(x / y + 48);
            x %= y;
        }
        if (flag)
            putchar('\n');
    }
}  // namespace IO
namespace tools {
    template < typename T >
    T cmax(T a, T b) {
        return max(a, b);
    }
    template < typename T >
    T cmin(T a, T b) {
        return min(a, b);
    }
    template < typename T >
    T cgcd(T a, T b) {
        return __gcd(a, b);
    }
    template < typename T >
    T clcm(T a, T b) {
        return a * b / cgcd(a, b);
    }
}  // namespace tools
}  // namespace luosw
#define read(t) t = luosw::IO::read< int >()
#define write(t) luosw::IO::write< int >(t, true)
const int MAXN = 3e5 + 5;
int       t, n, a[MAXN], m = 0, ans, temp;
bool      flag;
signed    main() {
    read(t);
    while (t--) {
        memset(a, 0, sizeof(a));
        m    = 0;
        flag = false;
        read(n);
        ans = 0;
        for (int i = 0; i < n; i++) {
            read(a[i]);
            m = max(m, a[i]);
        }
        temp = a[0];
        for (int i = 1; i < n; i++) {
            if (a[i] != temp) {
                flag = true;
                break;
            }
        }
        if (!flag) {
            write(-1);
            continue;
        }
        if (a[0] == m && a[1] < m) {
            write(1);
            continue;
        }
        if (a[n - 1] == m && a[n - 2] < m) {
            write(n);
            continue;
        }
        for (int i = 1; i < n - 1; i++) {
            if (a[i] == m) {
                if (a[i - 1] < m || a[i + 1] < m) {
                    ans = i + 1;
                    break;
                }
            }
        }
        write(ans);
    }
#ifdef debug
    system("pause");
#endif
    return 0;
}
```

---

## 作者：—维尼— (赞：0)

## 题目描述
给定一列鲨鱼，每条鱼可以吃掉相邻的鱼（前提是体积比相邻的至少大1），吃一次自己体积加一，让你找出优势食人鱼，即其他食人鱼不动的情况下这条鱼能吃遍所有鱼

## 方法解释
其实贪心即可做，为什么直接取最大的鱼不是正解，因为两边可能会有相同体积的，那么，我们只要找出最大体积的鲨鱼中，有东西可吃的鱼，直接就能过

如何找？

找出最右边的最大值，也就是不断更新

然后判断一下有几个最大值，也就是看我们找的最大值和左边是否相等

这时，如果最大值的编号不是n，就可以直接输出（因为有右边可以吃）

如果是$n$那就倒回来继续搜一遍，找到符合条件的最大值就行（就是当前数左边是比他小的）

贪心$o(n)$

## 代码
```c++
#include<bits/stdc++.h>
using namespace std;
int a[300005];
int main(){
	int t;
	cin>>t;
	while(t--){
		int n,maxn=-100005,num;
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			if(a[i]>=maxn){
				maxn=a[i];
				num=i;
			}
		}
		//cout<<maxn<<","<<num<<endl;
		int sum=0;
		for(int i=2;i<=n;i++){
			if(a[i]!=a[i-1])
			sum=1;
		}
		if(sum==0){
			cout<<-1<<endl;
			continue;
		}
		if(num==n){
			while(num--){
			if(a[num]<a[num+1])
			break;
			}
			cout<<num+1<<endl;
		}
		else
		cout<<num<<endl;
	}
}
```

---

## 作者：vectorwyx (赞：0)

当所有 $a$ 均相同时一定没有满足条件的虎头鱼。

否则，与非最大值相邻的那个最大值一定满足条件。因为这个最大值一定可以先吃掉与它相邻的非最大值，然后它就变成了所有虎头鱼中唯一的最大值，可以将所有其他的虎头鱼都吃掉。

代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define ll long long
#define fo(i,x,y) for(register int i=x;i<=y;++i)
#define go(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;

inline int read(){
	int x=0,fh=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*fh;
}

const int maxn=3e5+5;
int a[maxn];

void work(){
	int n=read(),mx=-1,ans=-1;
	fo(i,1,n) a[i]=read(),mx=max(mx,a[i]);
	a[0]=a[n+1]=mx;
	fo(i,1,n) if(a[i]==mx&&(a[i-1]<a[i]||a[i+1]<a[i])){
		ans=i;
		break;
	}
	printf("%d\n",ans);
	//puts("");
}
int main(){
	int T=read();
	while(T--){
		work();
	}
	return 0;
}
```


---

## 作者：ql12345 (赞：0)

[传送门](https://codeforces.com/contest/1433/problem/C)

这题做的时候真傻了，想了半天各种复杂做法，然后发现其实这么简单，导致D和E切得晚了...

引理：选择最大数

证明：

- 如果序列全为最大数，无解

- 否则序列定有一段最大数且这一段的边界旁边会有一个小一点的数，于是可以让边界的最大数吃它，然后这个数变成整个序列唯一的最大数，显然是答案

代码模拟（找到这一位置）即可，记得开long long

#### Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 3e5 + 7;
int a[N];
signed main()
{
	int t;
	scanf("%lld", &t);
	while(t --)
	{
		int n, mx = 0;
		scanf("%lld", &n);
		for(int i = 1; i <= n; ++i)
		{
			scanf("%lld", &a[i]);
			mx = max(mx, a[i]);
		}
		int f = 1, lst = a[1];
		for(int i = 2; i <= n && f; ++i)
			if(a[i] != lst) f = 0;
		if(f)
		{
			puts("-1");
			continue;
		}
		for(int i = 1; i <= n && ! f; ++i)
			if(a[i] == mx && i != 1 && a[i - 1] < a[i])
			{
				printf("%lld\n", i);
				f = 1;
			}
			else if(a[i] == mx && a[i + 1] != mx && i != n){
				printf("%lld\n",i);
				f = 1;
			}

		for(int i = 1; i <= n; ++i) a[i] = 0;
	}
	
	return 0;
}
```

---

