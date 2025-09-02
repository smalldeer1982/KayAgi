# Movie Critics

## 题目描述

A film festival is coming up in the city N. The festival will last for exactly $ n $ days and each day will have a premiere of exactly one film. Each film has a genre — an integer from 1 to $ k $ .

On the $ i $ -th day the festival will show a movie of genre $ a_{i} $ . We know that a movie of each of $ k $ genres occurs in the festival programme at least once. In other words, each integer from 1 to $ k $ occurs in the sequence $ a_{1},a_{2},...,a_{n} $ at least once.

Valentine is a movie critic. He wants to watch some movies of the festival and then describe his impressions on his site.

As any creative person, Valentine is very susceptive. After he watched the movie of a certain genre, Valentine forms the mood he preserves until he watches the next movie. If the genre of the next movie is the same, it does not change Valentine's mood. If the genres are different, Valentine's mood changes according to the new genre and Valentine has a stress.

Valentine can't watch all $ n $ movies, so he decided to exclude from his to-watch list movies of one of the genres. In other words, Valentine is going to choose exactly one of the $ k $ genres and will skip all the movies of this genre. He is sure to visit other movies.

Valentine wants to choose such genre $ x $ ( $ 1<=x<=k $ ), that the total number of after-movie stresses (after all movies of genre $ x $ are excluded) were minimum.

## 说明/提示

In the first sample if we exclude the movies of the 1st genre, the genres $ 2,3,2,3,3,3 $ remain, that is 3 stresses; if we exclude the movies of the 2nd genre, the genres $ 1,1,3,3,3,1,1,3 $ remain, that is 3 stresses; if we exclude the movies of the 3rd genre the genres $ 1,1,2,2,1,1 $ remain, that is 2 stresses.

In the second sample whatever genre Valentine excludes, he will have exactly 3 stresses.

## 样例 #1

### 输入

```
10 3
1 1 2 3 2 3 3 1 1 3
```

### 输出

```
3```

## 样例 #2

### 输入

```
7 3
3 1 3 2 3 1 2
```

### 输出

```
1```

# 题解

## 作者：洛璟 (赞：2)

## Solution:

我们看到相邻位置不同的个数时，自然能想到先去重预处理。

接下来怎么做？

我们来转化一下这个答案。

不难发现，在去重之后，相邻的数必然为不同的数字，也就是说，我们要做的就是在去重后的序列中去掉其中出现的一个数字并再次进行去重后使剩下的数字的数量最小，自然也就做到了相邻且不同的数最小。

那接下来的事也就简单了，由于我们前面已经去过重了，因此在去掉一个数字后如果仍需要去重，那这两个相同的数字一定只隔了一个数字。

举个例子，样例#1:

```
10 3

1 1 2 3 2 3 3 1 1 3

```

去重后：

```
1 2 3 2 3 1 3
```
此时若我们去掉了 $2$ 这个数，那么明显第三个数和第五个数会成为相邻且相同的数字，那么这时去掉一个 $2$ 相当于又去掉了一个 $3$。

所以我们只需要在遍历时判断一下一个数的左右两边是否相同并统计就好啦。

## Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n, k, cnt, ans, nw;
int sum[500010], a[500010], b[500010];
inline int read()
{
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c>'9')
    {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        x = (x << 3) + (x << 1) + (c ^ '0');
        c = getchar();
    }
    return x * f;
}
int main()
{
    n = read();
    k = read();
    for (int i = 1;i <= n;++i)
    {
        a[i] = read();
        if (a[i] != a[i - 1])//去重后统计数字个数
        {
            b[++cnt] = a[i];
            sum[a[i]]++;
            nw = max(sum[a[i]], nw);
        }
    }
    for (int i = 1;i <= cnt;++i)
    {
        if (b[i - 1] == b[i + 1])//判断两边是否有相同的数
        {
            sum[b[i]]++;
            if (sum[b[i]] > nw)
            {
                nw = sum[b[i]];
            }
        }
    }
    for (int i = 1;i <= k;++i)//找最小的答案
    {
        if (sum[i] == nw)
        {
            printf("%d", i);
            return 0;
        }
    }
    return 0;
}
```

---

## 作者：Free_Duck (赞：2)

## 题目大意

给出一个长度为 $n$ 的序列，序列仅包含 $1$ 到 $k$ 的数字，且对于每个数字，在序列中的出现次数至少为一次。

现在请你选出一个数字，使删去数列中所有的这个数字后，相邻位置的数字是不同的个数最小。

如果答案有多个，请输出最小的一个。

## 解法说明

由于需要求的是相邻的数字不同的个数，那么我们可以把一段连续且相同的数字压缩为一个，也就是去重。

让我们来看一个例子：

```cpp

10 3

1 1 2 3 2 3 3 1 1 3

```

去重后：

```cpp

1 2 3 2 3 1 3

```
假如此时要去掉的数字为 `2`，那么对于前三个数 `1 2 3`，由于 `2` 前后两个数并不相同，所以将 `2` 删去后原本的个数就会减少一；对于第三至第五个数 `3 2 3` 由于 `2` 前后两个数相同，所以将 `2` 删去后原本的个数就会减少二。

最后找到最小的答案即可。 

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,k,x,cnt,a[10005],sum[10005],tot=2e9,ans;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>x;
		if(x!=a[cnt]){
			a[++cnt]=x;
		}
	}
	for(int i=1;i<=n;i++){
		sum[i]=cnt-1;
	}
	for(int i=1;i<=cnt;i++){
		if(a[i-1]==a[i+1]){
			sum[a[i]]-=2;
		}else{
			sum[a[i]]-=1;
		}
	}
	for(int i=1;i<=n;i++){
		if(tot>sum[i]){
			tot=sum[i];
			ans=i;
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：OIerZhao_1025 (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF250C)

## 思路
给出一个长度为 $n$ 的序列，序列仅包含 $1-k$ 的数字，且对于每个数字，在序列中的出现次数至少为一次。
现在请你选出一个数字，使删去数列中所有的这个数字后，相邻位置的数字是不同的个数最小。\
如果答案有多个，请输出最小的一个。

我们先计算一开始共有多少相邻的，最后减掉一下两种可能。\
我们知道会有两种情况：
- 如果前一块和后一块的数字相同，那么会使原本的个数减少 $2$。
- 如果前一块和后一块的数字不相同，那么会使原本的个数减少 $1$。
最后减完就是结果。
## code
```cpp
    for(i=1;i<=n;i++)if(a[i]!=a[i-1]) cnt++;//之前的个数
	for(i=1;i<=n;i++)if(a[i]!=b[cur])b[++cur]=a[i];
	for(ii=1;i<=cur;i++)
	{
		c[b[i]]++;//不管一不一样都有的1
		if(b[i-1]==b[i+1]) c[b[i]]++;//前后一样再加1
	}
	for(i=1;i<=n;i++)if(maxn<c[i]) maxn=c[i],id=i;
```

---

## 作者：alan1118 (赞：0)

## 题意

给你一个数组，请你选择一个数，然后删去数组中所有这个数，使剩下的数中相邻两个不同的位置最小，如果有多个答案，输出最下的数字。

## 思路

首先要算出初始数组有多少个位置。

然后我们可以将整个数组相邻切相同的位合并，得到一个任意相邻数字都不相同的新数组 $b$。不难看出，这一步其实就是去重。

接着我们用一个 $c$ 数组存删除每种数能减少几个不同的位置。然后来分析 $b_i$ 位置，有两种情况：

1. $b_{i-1} \ne b_{i+1}$。这时候只少了 $1$ 组。
2. $b_{i-1} \ne b_{i+1}$。这时候删除中间的数后两边会合在一起，所以这种情况减少了 $2$ 组。

处理完 $c$ 数组后接非常简单了，直接找出最大 $c_i$，输出 $i$ 的即可。

## Code

``` cpp
#include <iostream>
using namespace std;

const int N = 1e5 + 5;

int a[N], b[N], cur;
int c[N];

int main()
{
	int n, k;
	cin >> n >> k;
	int cnt = 0;
	for(int i = 1; i <= n; i++)
	{
		cin >> a[i];
		if(a[i] != a[i-1]) cnt++;
	}
	for(int i = 1; i <= n; i++)
		if(a[i] != b[cur])
			b[++cur] = a[i];
	for(int i = 1; i <= cur; i++)
	{
		c[b[i]]++;
		if(b[i-1] == b[i+1]) c[b[i]]++;
	}
	int maxn = 0, id;
	for(int i = 1; i <= n; i++)
		if(maxn < c[i]) maxn = c[i], id = i;
	cout << id << endl;
	return 0;
}
```

---

## 作者：Chenaknoip (赞：0)

不难发现，形如 `xxxxx` 子串对答案的贡献和 `x` 是一样的。

举个例子，`123333345` 中 `33333` 对答案贡献了 $1$。而`12345` 中 `3` 对答案贡献也是 $1$。

因此可以考虑合并相同的数字，然后进行预处理，使用数组 $cnt_i$ 表示 $i$ 数字两侧不同的数量。

时间复杂度 $O(n)$ 可以通过本题。

---

## 作者：bellmanford (赞：0)

CF250的后三题居然没人交翻译和题解。。。

很容易想到记录每个数字被删掉后减少相邻数字不同的个数，然后取最大的一个。

因为这样子很容易维护。

对于连续的一块相同数字 $x$ ，分两种情况考虑：

- 如果前一块和后一块的数字相同，那么会使原本的个数减少 $2$ 。

- 如果前一块和后一块的数字不相同，那么会使原本的个数减少 $1$ 。

稍微比较一下就发现这是对的，然后模拟就行了。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;

const int M=1e5+5;

int read(){
	int x=0,y=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') y=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*y;
}

int n,k,ans=0,a[M],tong[M];
void solve(){
	n=read(),k=read();
	int last=1;a[1]=read();
	for(int i=2;i<=n;i++){
		a[i]=read();
		if(a[i]==a[last]) continue ;
		if(a[last-1]==a[i]) tong[a[last]]+=2;
		else tong[a[last]]++;
		last=i;
		ans++;
	}
	tong[a[n]]++;
	int Min=1e9,Ans;
	for(int i=1;i<=k;i++){
		if(Min>(ans-tong[i])){
			Min=ans-tong[i];
			Ans=i;
		}
	}
	return (void)(printf("%d\n",Ans));
}

int main(){
	solve();
}
```


---

