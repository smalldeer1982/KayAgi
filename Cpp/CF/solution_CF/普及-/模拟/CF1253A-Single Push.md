# Single Push

## 题目描述

You're given two arrays $ a[1 \dots n] $ and $ b[1 \dots n] $ , both of the same length $ n $ .

In order to perform a push operation, you have to choose three integers $ l, r, k $ satisfying $ 1 \le l \le r \le n $ and $ k > 0 $ . Then, you will add $ k $ to elements $ a_l, a_{l+1}, \ldots, a_r $ .

For example, if $ a = [3, 7, 1, 4, 1, 2] $ and you choose $ (l = 3, r = 5, k = 2) $ , the array $ a $ will become $ [3, 7, \underline{3, 6, 3}, 2] $ .

You can do this operation at most once. Can you make array $ a $ equal to array $ b $ ?

(We consider that $ a = b $ if and only if, for every $ 1 \le i \le n $ , $ a_i = b_i $ )

## 说明/提示

The first test case is described in the statement: we can perform a push operation with parameters $ (l=3, r=5, k=2) $ to make $ a $ equal to $ b $ .

In the second test case, we would need at least two operations to make $ a $ equal to $ b $ .

In the third test case, arrays $ a $ and $ b $ are already equal.

In the fourth test case, it's impossible to make $ a $ equal to $ b $ , because the integer $ k $ has to be positive.

## 样例 #1

### 输入

```
4
6
3 7 1 4 1 2
3 7 3 6 3 2
5
1 1 1 1 1
1 2 1 3 1
2
42 42
42 42
1
7
6
```

### 输出

```
YES
NO
YES
NO
```

# 题解

## 作者：DERMING (赞：1)

## CF1253A 题解

[portal](https://www.luogu.com.cn/problem/CF1253A)

题意：给定两个序列，你可以把第一个序列任意一段区间的每一个值加上 $k$ ，使得两个序列完全相同。

思路：因为要修改区间使其完全相同，所以只要找出哪里不同并进行修改即可。但是题目限制我们只能修改一个连续子区间，因此只要判断一下不同的地方是否仅构成**一个不间断序列**。

2023.8.17: 发现代码粘错了，已更正

Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[100001],b[100001];
int main()
{
    cin >> t;
    while(t--)
	{
        cin >> n;
        for(int i=1;i<=n;i++)
		cin >> a[i];
        for(int i=1;i<=n;i++)
		cin >> b[i];
		int pre=0;
        bool flag=1;
        for(int i=1;i<=n;i++)
		if((pre==0&&b[i]!=a[i])||(pre==(b[i]-a[i]))) pre=b[i]-a[i];
        else if((pre!=0&&b[i]!=a[i])||(pre<0))
		{
			flag=0;
        	break;
        }
        if(flag)cout << "Yes\n";
        else cout << "No\n";
    }
    return 0;
}
```


---

## 作者：wkjwkj (赞：1)

**原题链接**:[here](https://codeforces.com/problemset/problem/1253/A)

[~~由于玄学的原因，洛谷的LaTeX不支持中文~~ 推荐博客食用](https://mywkj.github.io/2020/03/05/cf1253a-ti-jie/)

本题只要照题意模拟一下即可。把b序列与a序列相减，观察得到的c序列是否为

$\begin{matrix}\underbrace{00\cdots0}\\x\end{matrix}$ $\begin{matrix}\underbrace{dd\cdots d}\\y\end{matrix}$ $\begin{matrix}\underbrace{00\cdots0}\\z\end{matrix}$
$(x\ge 0,y\ge 0,z\ge 0,d\ge 0)$
若是，则输出$YES$ ，反之，输出$NO$

代码如下:

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100005],b[100005],c[100005];
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int n;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		  scanf("%d",&a[i]);
		for(int i=1;i<=n;i++)
		  scanf("%d",&b[i]);
		bool ok=true;
		for(int i=1;i<=n;i++)
		  if(a[i]!=b[i])ok=false;
		if(ok){//特判a==b的情况
			puts("YES");
			continue;
		}
		for(int i=1;i<=n;i++)
			c[i]=b[i]-a[i];
		int j=1;
		while(c[j]==0)j++;
		if(c[j]<0){
			puts("NO");
			continue;
		}
		j++;
		while(c[j]==c[j-1])j++;
		if(j==n+1){
			puts("YES");
			continue; 
		}
		int yes=true;
		for(;j<=n;j++)
		  if(c[j]!=0)yes=false;
		if(yes)puts("YES");
		else puts("NO");
	}
}
```



---

## 作者：blsya23a2 (赞：0)

## 分析
由题知，我们只需要遍历输入，并分三种状态判断是否满足条件。把输入的两个序列存储在列表 $d$ 和 $e$ 中。

1. 当 $1\le h<l$ 时，$d_h=e_h$。

2. 当 $l\le h\le r$ 时，$e_h-d_h=k$（$k$ 为定值）。
3. 当 $r<h\le n$ 时，$d_h=e_h$。

对于这三种状态，可以设置一个变量来记录。当 $d_h\not=e_h$ 时，状态由 $1$ 变为 $2$。当 $d_h=e_h$ 时，状态由 $2$ 变为 $3$。过程中任何条件不符合，又不能解释为状态变化的，就输出 `NO`，否则输出 `YES`。
## 代码
```python
a = int(input())
for b in range(a):
    c,d,e,f,g = int(input()),list(map(int,input().split())),list(map(int,input().split())),0,0
    for h in range(c):
        if f == 0:
            if e[h]-d[h] < 0:
                f = -1
                break
            elif e[h]-d[h] > 0:
                g,f = e[h]-d[h],1
        elif f == 1:
            if e[h]-d[h] != g:
                if e[h]-d[h] == 0:
                    f = 2
                else:
                    f = -1
                    break
        else:
            if e[h]-d[h] != 0:
                f = -1
                break
    if f == -1:
        print('NO')
    else:
        print('YES')
```
upd：优化了过程说明。

---

## 作者：zwye (赞：0)

[原题链接↓](https://www.luogu.com.cn/problem/CF1253A)

这道题很简单，可以按照题意模拟一下。
### 思路
把序列 $a$ 与序列 $b$ 相减，如果差形式为两个由 $0$ 组成的序列包裹着一个连续的相同的差 $k$，就能使 $a$ 转化成 $b$。

1. 判断是否为负数,因为零不行。

2. 判断是否当前还是 $0$ 或跟上一个一样,这样可以。

3. 储存第一个不是 $0$ 的数。

4. 输出。

### 代码：
```c
#include<bits/stdc++.h>
using namespace std;
int t,n,a[100010],b[100010],c[100010];
int main()
{
	cin>>t;
	while(t--)
	{
		memset(c,0,sizeof(c));
		cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i];
		for(int i=1;i<=n;i++)cin>>b[i];
		bool flag=1;
		int s=1;
		for(int i=1;i<=n;i++)
		{
			c[i]=b[i]-a[i];
			if(c[i]!=0)s=0;
			if(c[i]<0)flag=0;
		}
		if(!flag)
		{
			cout<<"NO"<<endl;
			continue;
		}
		if(s)
		{
			cout<<"YES"<<endl;
			continue; 
		}
		int e=1;
		c[0]=c[1];
		if(c[1]>0)e--;
		for(int i=2;i<=n;i++)
			if(c[i]!=c[i-1]&&c[i])e--;
		if(e>=0)cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
	}
	return 0;
} 
```
有错误请指出。

---

## 作者：lmndiscyhyzdxss (赞：0)

## 题目大意
给出一个操作:在 $ 1 \thicksim n $ 中选出两个数 $ l $ , $ r(1 \leq l \leq r \leq n) $ 在 $ l \thicksim r $这个区间里,每个数加上 $ k(k>0) $ 
给定两个数组 $ a[1...n] $ 和 $ b[1...n] $ 求再一次操作后能否使数组 $ a $ 等于数组 $ b $                            
例如: $ a=[3 $ , $ 7 $ , $ 1 $ , $ 4 $ , $ 1 $ , $ 2 $ ] , $  b=[3 $ , $ 7 $ , $ 3 $ , $ 6 $ , $ 3 $ , $ 2] $ 要使数组 $ a $ 等于数组 $ b $ ,需选择 $ l=3 $ , $ r=5 $ , $ k=2 $  
## 题目分析
1. 这道题首先想到的是暴力枚举 , 是指针一个指向数组 $ a $ ,一个指向数组 $ b $ ,分别做差,但时间复杂度为 $ \left(n^2\right) $
2. 我们可以用数组 $ a $ 与数组 $ b $ 做差,得到 $ c $ 数组,然后用一种类似尺取法的方法进行一个一个判断          
正确的情况应该是:     
 $ \begin{matrix}\underbrace{0,0,0\cdots0}\\l-1\end{matrix} $    $ \begin{matrix}\underbrace{h,h,h\cdots h}\\ l \thicksim r \end{matrix}  $  $ \begin{matrix}\underbrace{0,0,0\cdots0}\\r+1\end{matrix} $         
我们要做什么事呢：
+ 判断是否为负数,因为零不行
+ 判断是否当前还是 0 或跟上一个一样,这样可以
+ 储存第一个不是 0 的数
+ 输出  
我构造了一个前缀和数组 $ , $ 可以快速判断后面是否都是零,不用三个循环了
不像前面两位大佬们那么麻烦了，代码比较精炼
 ## AC代码
 ```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[100010],b[100010],c[100010],d[100010],l,p;
int main()
{
	cin>>t;
	while(t--)
	{
		scanf("%d",&n),p=1,l=0;
		for(int i=1;i<=n;i++)scanf("%d",&a[i]),d[i]=0;
		for(int i=1;i<=n;i++)scanf("%d",&b[i]);
		for(int i=1;i<=n;i++)c[i]=b[i]-a[i],d[i]=d[i-1]+c[i];
		for(int i=1;i<=n;i++)
		{
			if(c[i]<0){printf("NO\n");p=0;break;}//不可能加负数 
			else if(c[i]==0&&l==0||l!=c[i]&&c[i]==0&&d[n]-d[i]==0||l==c[i])continue;//如果当前还是0或跟上一个一样 
			else if(l==0&&c[i]!=0)l=c[i];//第一个不是0的数 
			else {printf("NO\n");p=0;break;}//否则不成立 
		}
		if(p==1)printf("YES\n");
	}
    return 0;
}
```


---

## 作者：_VEGETABLE_OIer_xlc (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1253A)

### 题意

给定长度为 $n$ 的序列 $a$ 和 $b$，序列 $a$ 有且只有一次机会可以选择一个区间让这个区间里的数加上 $k$，问：能不能让序列 $a$ 和序列 $b$ 完全一样。

思路简单但细节很多，我被坑到了好多次。

### 思路

把序列 $a$ 与序列 $b$ 相减，如果差形式为两个由 $0$ 组成的序列包裹着一个连续的相同的差 $k$ ，就能使 $a$ 转化成 $b$。

具体形式可以参考大佬 zhang_kevin 的题解。

### 细节

这是本题的重点，搞清这些就能 AC，但如果细节错一个就会寄掉，功亏一篑。

+ 首先加的数 $k$ 是正整数，不能是负数，可以从样例的第四组数据看出。

+ 要特判全部相同的。

+ 当判断差序列时，注意一开头就不是 $0$ 的就没有机会了（因为这个调了半天）。

好了，细节整完了，上 AC 代码！

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[100010],b[100010],cha[100010];
int main(){
	cin>>t;
	while(t--)
	{
		memset(cha,0,sizeof(cha));//记得清0 
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		for(int i=1;i<=n;i++)
			cin>>b[i];
		bool fushu=1;
		int same=1;
		for(int i=1;i<=n;i++)
		{
			cha[i]=b[i]-a[i];
			if(cha[i]!=0)
			{
				same=0;
			}
			if(cha[i]<0)
				fushu=0;
		}
		if(!fushu)
		{
			cout<<"NO"<<endl;
			continue;
		}
		if(same)
		{
			cout<<"YES"<<endl;
			continue; 
		}//特判
		int jihui=1;
		cha[0]=cha[1];
		if(cha[1]>0)//如果第一个就要操作 
			jihui--;
		for(int i=2;i<=n;i++)
		{
			if(cha[i]!=cha[i-1]&&cha[i])
				jihui--;
		}
		if(jihui>=0)
			cout<<"YES"<<endl;
		else
			cout<<"NO"<<endl;
	}
	return 0;
} 
```


---

## 作者：zhang_kevin (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1253A)

# Content

给定两个长度为 $n$ 的数组 $a$ 和数组 $b$。

定义一个操作：选 $3$ 个数 $l,r,k$ 满足 $(1\leq l \leq r \leq n,k \geq 0)$ 然后将元素 $a_l,a_{l+1},\dots,a_r$ 都加上 $k$。

例如，$a=[3,7,1,4,1,2]$ 然后选择 $l=3,r=5,k=2$，那么操作过后数组 $a=[3,7,3,6,3,2]$。

问你如果最多只能进行一次操作能否使得数组 $a$ 等于数组 $b$。

# Solution

这道题很简单，可以按照题意模拟一下。

我们把 $b$ 数组与 $a$ 数组两两相减得到 $s$ 数组，判断是否可以分为一下这三个小数组即可：

$\begin{matrix}\underbrace{00\cdots0}\\1\sim l-1\end{matrix}$ 

$\begin{matrix}\underbrace{kk\cdots k}\\l \sim r\end{matrix}$

$\begin{matrix}\underbrace{00\cdots0}\\r+1 \sim n\end{matrix}$

$(1\leq l \leq r \leq n,k \geq 0)$

# Code

```cpp
#include<cstdio>
int a[100001], b[100001], s[100001], n;
inline void work(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%d", &a[i]);
	}
	bool same = true, flag = true;
	for(int i = 1; i <= n; i++){
		scanf("%d", &b[i]);
		s[i] = b[i] - a[i];
		if(a[i] != b[i]){
			same = false;
		}
		if(s[i] < 0){
			flag = false;
		}
	}
	if(!flag){
		puts("NO");
		return;
	}
	if(same){
		puts("YES");
		return;
	}
	int l = 1, r = n;
	while(!s[l++]);
	while(!s[r--]);
	l--, r++;
	int Min = 0x3f3f3f3f, Max = -0x3f3f3f3f;
	for(int i = l; i <= r; i++){
		if(Min > s[i]){
			Min = s[i];
		}
		if(Max < s[i]){
			Max = s[i];
		}
	}
	if(Min == Max){
		puts("YES");
	}else{
		puts("NO");
	}
	return;
}
auto Solve = [](void) -> int{
	int T;
	scanf("%d", &T);
	while(T--){
		work();
	}
    return 0;
}();
int main(){return Solve;}
```


---

