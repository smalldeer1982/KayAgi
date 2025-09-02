# Lose it!

## 题目描述

You are given an array $ a $ consisting of $ n $ integers. Each $ a_i $ is one of the six following numbers: $ 4, 8, 15, 16, 23, 42 $ .

Your task is to remove the minimum number of elements to make this array good.

An array of length $ k $ is called good if $ k $ is divisible by $ 6 $ and it is possible to split it into $ \frac{k}{6} $ subsequences $ 4, 8, 15, 16, 23, 42 $ .

Examples of good arrays:

- $ [4, 8, 15, 16, 23, 42] $ (the whole array is a required sequence);
- $ [4, 8, 4, 15, 16, 8, 23, 15, 16, 42, 23, 42] $ (the first sequence is formed from first, second, fourth, fifth, seventh and tenth elements and the second one is formed from remaining elements);
- $ [] $ (the empty array is good).

Examples of bad arrays:

- $ [4, 8, 15, 16, 42, 23] $ (the order of elements should be exactly $ 4, 8, 15, 16, 23, 42 $ );
- $ [4, 8, 15, 16, 23, 42, 4] $ (the length of the array is not divisible by $ 6 $ );
- $ [4, 8, 15, 16, 23, 42, 4, 8, 15, 16, 23, 23] $ (the first sequence can be formed from first six elements but the remaining array cannot form the required sequence).

## 样例 #1

### 输入

```
5
4 8 15 16 23
```

### 输出

```
5
```

## 样例 #2

### 输入

```
12
4 8 4 15 16 8 23 15 16 42 23 42
```

### 输出

```
0
```

## 样例 #3

### 输入

```
15
4 8 4 8 15 16 8 16 23 15 16 4 42 23 42
```

### 输出

```
3
```

# 题解

## 作者：Lily_White (赞：7)

本题是一道很不错的题目。

首先，我们不难想到将题目中给的奇奇怪怪的数字进行**离散化**，因为只有$6$个取值，```if```一下也可以。

Code：
```cpp
		if (x == 4)x = 1;
		if (x == 8)x = 2;
		if (x == 15)x = 3;
		if (x == 16)x = 4;
		if (x == 23)x = 5;
		if (x == 42)x = 6;
	
```

这时，我们需要在$O(n)$的时间内确定匹配的方案，需要注意到，**我们并不关心某个数与哪个数配对**，因此只需要记录长度为$i(1 \leq i \leq 6)$的序列已经有多少个完成$(cnt_i$)就可以。

对于扫描时遇到的某个数，我们将它和对应的那个数配对。这时$cnt_{i-1}=cnt_{i-1}-1,cnt_i=cnt_i+1$。特判$i=1$即可。答案为$n-6 \times cnt_6$。代码如下：

```
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 500500;
int a[MAXN];
int n;
int ans;
int cnt[7];
int main()
{
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		int x;
		cin >> x;
		if (x == 4)x = 1;
		if (x == 8)x = 2;
		if (x == 15)x = 3;
		if (x == 16)x = 4;
		if (x == 23)x = 5;
		if (x == 42)x = 6;
		a[i] = x;
	}
	for (int i = 1; i <= n; i++)
	{
		if (a[i] == 1)
			cnt[1]++;
		else
		{
			if (cnt[a[i] - 1])
			{
				cnt[a[i]]++;
				cnt[a[i] - 1]--;
			}
		}
	}
	cout << n - 6 * cnt[6] << endl;
	return 0;
}

```




---

## 作者：JHR100330 (赞：3)

[传送门](https://www.luogu.com.cn/problem/CF1176C)

# CF1176C Lose it! 题解

该题大意为删掉最少的原数使得剩下的元素都能构成若干个不交子序列 $[4,8,15,16,23,42]$。

即求该序列内不交子序列 $[4,8,15,16,23,42]$ 的最大个数 $t$，输出 $n - 6 * t$ 即可。

先将 $4,8,15,16,23,42$ 离散化为 $1,2,3,4,5,6$。

然后令 $cnt_i$ 为当前状态下序列 $[1,\cdots,i]$ 的个数，$a_i$ 为输入的元素离散化后的值。

对于 $a_i$ 为 $1$ 的情况，直接统计即可。

对于 $a_i$ 为 $2,3,4,5,6$ 的情况，若当前不存在序列 $[1,\cdots,a_i - 1]$，即 $cnt_{a_{i - 1}} = 0$，则 $a_i$ 在最优情况下无法与任何未补全的子序列拼接成为更长序列，不作任何改变。若当前存在若干个序列 $[1,\cdots,a_i - 1]$，则将 $a_i$ 拼接到其中一个序列中得到新的序列，因为序列 $[1,\cdots,a_i - 1]$ 已进行拼接成为更长的序列  $[1,\cdots,a_i]$，所以要将 $cnt_{a_{i}-1}$ 的值减去 $1$，将 $cnt_{a_i}$ 的值加上 $1$。

最后 $cnt_6$ 的值即为整个序列最高的好的序列的个数。

则 $n - 6 \times cnt_6$ 即为最少的删去数的个数，输出即可。

# AC Code:

```cpp
#include<bits/stdc++.h>

using namespace std;

int change[43]; // 离散化数组 
int cnt[7]; // 统计数组 
int n, a;

int main(){
	scanf("%d", &n);
	change[4] = 1; change[8] = 2; change[15] = 3; change[16] = 4; change[23] = 5; change[42] = 6; // 离散化数组初始化 
	for(int i = 1; i <= n; i ++){
		scanf("%d", &a);
      	a = change[a]; // 离散化 
		if(a == 1) // 若 a 为 1 直接统计
			cnt[a] ++;
		else if(cnt[a - 1] != 0){ // 若 a 为 2,3,4,5,6 则尝试拼接 
			cnt[a - 1] --;
			cnt[a] ++;
		}
	}
	printf("%d\n", n - cnt[6] * 6);
	return 0;
}
```

---

## 作者：Strong_Jelly (赞：3)

## 此题map轻松解决

一开始想复杂了，从而得出了蜜汁[MLE](https://www.luogu.org/recordnew/show/20149655)，之前思想大概是：

- 搞一个map打标，存当前数字的上一个数字是什么
- 再用stack搞一个数组存数字串（这块不懂的看代码）
- 然后枚举所有数字，是第一个（4）的就++z（栈的数量）然后push进去，不是就枚举所有栈，寻找可以接上的地方（及这个数字必须接的上一个数字，例：8的上一个数字是4），然后就接上，如果接不上或不是4，就++ans（删掉的数量）
- 最后如果那个栈里有剩余，就ans += pru[i].size();因为剩余的不能组成一个完美的数字串

代码（非正解就不写注释了）：

```cpp
#include <bits/stdc++.h>
using namespace std;
map < int, int > mp;
stack < int > pru[510001];
int o, z, n, q[510001], ans;
int main()
{
    o = 1;
    mp[8] = 4;
    mp[15] = 8;
    mp[16] = 15;
    mp[23] = 16;
    mp[42] = 23;
    scanf("%d", &n);
    for(register int i = 1; i <= n; ++i)
    {
        scanf("%d", &q[i]);
    }
    for(register int i = 1; i <= n; ++i)
    {
        bool f = false;
        if(q[i] == 4)
        {
            pru[++z].push(q[i]);
            f = true;
        }
        else
        {
            for(register int j = o; j <= z; ++j)
            {
                if(mp[q[i]] == pru[j].top())
                {
                    pru[j].push(q[i]);
                    f = true;
                }
            }
        }
        if(!f)
        {
            ++ans;
        }
    }
    for(register int i = o; i <= z; ++i)
    {
        ans += pru[i].size();
    }
    printf("%d", ans);
    return 0;
}
```

正解很简单，和之前的大同小异，只不过把stack省去了，复杂度O(n)。因为只算当前数字前面几个数字，所以直接用map统计每个数字的出现次数就好了

code：

```cpp
#include <bits/stdc++.h>
using namespace std;
map < int, int > mp;
map < int, int > w;
int n, q[510001];
int main()
{
	mp[8] = 4;//打表 
	mp[15] = 8;
	mp[16] = 15;
	mp[23] = 16;
	mp[42] = 23;
	scanf("%d", &n);
	for(register int i = 1; i <= n; ++i)
	{
		scanf("%d", &q[i]);
	}
	for(register int i = 1; i <= n; ++i)
	{
		if(q[i] == 4)
		{
			++w[4];//头数字 
		}
		else
		{
			if(w[mp[q[i]]])//得有当前数字的前缀数字 
			{
				--w[mp[q[i]]];//这个数字被用过了，-- 
				++w[q[i]];//多了这个数字，++ 
			}
		}
	}
	printf("%d", n - 6 * w[42]);//所有字符 - 一组字符数 * 最后连成组成42的数量(完美的) 
	return 0;
}
```

---

## 作者：Phecda (赞：3)

给个常数大点的$\Theta(nlog_2n)$的做法叭.

考虑暴力怎么做:
每次去把$4,8,15,16,23,42$这个串暴力匹配出来删掉,直到不能再匹配为止.

考虑如何优化这个东西.

我们发现,我们匹配的时候需要的是下一个数的位置,而找数很容易想到二分.

但我们发现不能直接在原序列上二分,显然没有单调性.

而排序会破坏序列结构,这在此题中是无法接受的.

但我们还会发现,虽然序列不具备单调性但是这些数字的位置却是单调递增的.

于是我们考虑记下$4,8,15,16,23,42$每个数字在原序列中出现的所有位置.

然后枚举$4$的位置,每次匹配只需要做$5$次二分,就能匹配出一个$4,8,15,16,23,42$.

如果中间有匹配失败,那么显然再往后的$4$都不能完成匹配,所以直接$break$即可.

最后统计出成功匹配的子序列个数,用总长度减去匹配数$\times 6$即可.

这里因为牵扯到删除操作,二分操作,以及单调性,我就使用了$set$,所以这个题...其实对我来说是个$set$题.

$Code:$
```cpp
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <string>
#include <vector>
#include <queue>
#include <cmath>
#include <ctime>
#include <map>
#include <set>
#define MEM(x,y) memset ( x , y , sizeof ( x ) )
#define rep(i,a,b) for (int i = (a) ; i <= (b) ; ++ i)
#define per(i,a,b) for (int i = (a) ; i >= (b) ; -- i)
#define pii pair < int , int >
#define one first
#define two second
#define rint read<int>
#define int long long
#define pb push_back

using std::queue ;
using std::set ;
using std::pair ;
using std::max ;
using std::min ;
using std::priority_queue ;
using std::vector ;
using std::swap ;
using std::sort ;
using std::unique ;
using std::greater ;

template < class T >
    inline T read () {
        T x = 0 , f = 1 ; char ch = getchar () ;
        while ( ch < '0' || ch > '9' ) {
            if ( ch == '-' ) f = - 1 ;
            ch = getchar () ;
        }
       while ( ch >= '0' && ch <= '9' ) {
            x = ( x << 3 ) + ( x << 1 ) + ( ch - 48 ) ;
            ch = getchar () ;
       }
   return f * x ;
}

const int N = 5e5 + 100 ;

int n , v[N] ;
set < int > pos[7] ;
bool mk[N] ;

signed main (int argc , char * argv[]) {
    n = rint () ; rep ( i , 1 , n ) v[i] = rint () ;
    rep ( i , 1 , n ) {
        switch ( v[i] ) {
            case 4 : pos[1].insert ( i ) ; break ;
            case 8 : pos[2].insert ( i ) ; break ;
            case 15 : pos[3].insert ( i ) ; break ;
            case 16 : pos[4].insert ( i ) ; break ;
            case 23 : pos[5].insert ( i ) ; break ;
            case 42 : pos[6].insert ( i ) ; break ;
        }
    }
    int ans = 0 ;
    for ( set < int > :: iterator it = pos[1].begin () ; it != pos[1].end () ; ++ it) {
        int pos1 = *it ; auto tmp1 = pos[2].upper_bound ( pos1 ) ;
        if ( tmp1 == pos[2].end () ) break ;
        int pos2 = *tmp1 ; auto tmp2 = pos[3].upper_bound ( pos2 ) ;
        if ( tmp2 == pos[3].end () ) break ;
        int pos3 = *tmp2 ; auto tmp3 = pos[4].upper_bound ( pos3 ) ;
        if ( tmp3 == pos[4].end () ) break ;
        int pos4 = *tmp3 ; auto tmp4 = pos[5].upper_bound ( pos4 ) ;
        if ( tmp4 == pos[5].end () ) break ;
        int pos5 = *tmp4 ; auto tmp5 = pos[6].upper_bound ( pos5 ) ;
        if ( tmp5 == pos[6].end () ) break ;
        ++ ans ; pos[2].erase ( tmp1 ) ; pos[3].erase ( tmp2 ) ;
        pos[4].erase ( tmp3 ) ; pos[5].erase ( tmp4 ) ; pos[6].erase ( tmp5 ) ;
    }
    printf ("%lld\n" , n - ans * 6 ) ;
    system ("pause") ; return 0 ;
}
```

---

## 作者：One_JuRuo (赞：1)

## 思路

定义一个数组能分为若干份，每一份都是 $4,8,15,16,23,42$ 的前缀的数组是 **半优秀** 的。

容易发现只有满足以下性质的数组才是 **半优秀**：

令 $j$ 在数组的 $[1,i]$ 中出现的次数为 $num_{i,j}$，对于每一个 $i(1\leq i\leq n)$，都存在 $num_{i,j_1}\leq num_{i,j_2},(j_1 \geq j_2)$。

那么，如果一个数的出现，使目前的数组不是 **半优秀** 的，那么它一定会使整个数组不是 **优秀** 的，所以需要删去。

最后的出的数组中，只需要把所有多余的 $4,8,15,16,23$ 删去就是 **优秀** 的数组了。

那么，最后剩下的数的数量就是 $6
 \times num_{n,42}$。

只需要用 $n$ 减去剩下的数的数量，就可以得出答案。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[500005],num[7];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	for(int i=1;i<=n;++i)
	{
		int k=(a[i]==4)?1:(a[i]==8)?2:(a[i]==15)?3:(a[i]==16)?4:(a[i]==23)?5:6;
		if(k==1){++num[k];continue;}
		if(num[k]+1>num[k-1]) continue;
		else ++num[k];
	}
	printf("%d",n-num[6]*6);
	return 0;
}
```

---

## 作者：knsg251 (赞：1)

## 题目解读
给了一个序列，然后给出一个标准的序列 $[4,8,15,16,23,42]$。问需要删除多少个数才能再不丢弃的情况下组成给出的序列。
## 题目分析
这道题需要用到**离散化**的思想，把给出的数组按照序列 $[4,8,15,16,23,42]$ 进行离散化，就像这样。
```cpp
	if(a[i] == 4) b[i] = 1;
	else if(a[i] == 8) b[i] = 2;
	else if(a[i] == 15) b[i] = 3;
	else if(a[i] == 16) b[i] = 4;
	else if(a[i] == 23) b[i] = 5;
	else if(a[i] == 42) b[i] = 6;
```
然后就是寻找有几个标准序列，我们可以先找到一共有多少组序列，组数 $t$，那么答案显然就是 $(n - t \times 6)$。如何找到组数 $t$ 是个重点。
```cpp
	if(b[i] == 1){//当数组为4时
		ans[1]++;//用一个单独的数组去记录为4的情况
	}
	if(ans[b[i] - 1] != 0){//其余情况
		ans[b[i] - 1]--;//把前面减去
		ans[b[i]]++;//把自己增加
	}
```
## 代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
int k;
int a[500005],b[500005],ans[500005];
int main(){
	cin>>k;
	for(int i=1;i<=k;i++){
		scanf("%d",&a[i]);
		if(a[i] == 4) b[i] = 1;
		else if(a[i] == 8) b[i] = 2;
		else if(a[i] == 15) b[i] = 3;
		else if(a[i] == 16) b[i] = 4;
		else if(a[i] == 23) b[i] = 5;
		else if(a[i] == 42) b[i] = 6;
	}
	for(int i=1;i<=k;i++){
		if(b[i] == 1){
			ans[1]++;
		}
		if(ans[b[i] - 1] != 0){
			ans[b[i] - 1]--;
			ans[b[i]]++;
		}
	}
	cout<<k - ans[6] * 6;
    return 0;
}
```

---

## 作者：naroto2022 (赞：0)

# CF1176C 题解

### 题面

[原题传送门](https://www.luogu.com.cn/problem/CF1176C)

### 前置知识

1. 离散化（不会的看后记）

### 思路

首先看题目，题目问最多要删几个数，那不妨换一个角度想，想在数组 $a$ 中有几个数字可以不被删掉，进一步转化为求在长度为 $n$ 的数组里有几个“好的数列”，最后拿总数 $n$ 减去不被删掉的数即可。

### 实现

首先先给数组 $a$ 离散化一下：

```cpp
if(a[i]==4) a[i]=1;
else if(a[i]==8) a[i]=2;
else if(a[i]==15) a[i]=3;
else if(a[i]==16) a[i]=4;
else if(a[i]==23) a[i]=5;
else if(a[i]==42) a[i]=6;
```

离散化后，可以注意到我们**并不需要关心某个数与哪个数配对**，只需要记录长度为 $i(i\in[1,6])$ 的序列有多少个数列是好的数列（$ans[i]$）即可。

对于当前遍历到的数，我们有：$ans[a[i]]+1,ans[a[i]-1]-1$，注意，对于 $a[i]=1$ 需要特判：$ans[1]+1$。

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
long long n,a[500005],ans[10];
int main(){
	scanf("%lld",&n);
	for(int i=1; i<=n; i++){
		scanf("%lld",&a[i]);
		if(a[i]==4) a[i]=1;
		else if(a[i]==8) a[i]=2;
		else if(a[i]==15) a[i]=3;
		else if(a[i]==16) a[i]=4;
		else if(a[i]==23) a[i]=5;
		else if(a[i]==42) a[i]=6; //离散化 
	}
	for(int i=1; i<=n; i++){
		if(a[i]==1) ans[1]++;
		else if(ans[a[i]-1]){
			ans[a[i]]++;
			ans[a[i]-1]--;
		}
	}
	printf("%lld",n-6*ans[6]);
	return 0;
} 
```


### 后记

#### 什么是离散化？

在排序过程中中，通常要知道每个数排序后的编号（$rank$ 值），这个时候就需要离散化。

#### 问题

给定一个 $n$ 个数的数组，输出每个数的排名。

#### 样例输入

```
5
8 2 6 9 4

```

#### 样例输出

```
4 1 3 5 2

```

#### 问题的解决

排序是必须的，关键是怎样把排名写回原来的数“下面”。

程序使用了分别对数值和下标不同关键字 $2$ 次排序的办法来解决这个问题，一个数据“节点”应该包含：数值，排名，下标 $3$ 个元素，可以用结构体，具体见代码。

#### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath> 
using namespace std;
struct node{
	int data,rank,index;//依次表示数值、排名、下标 
}a[10010];
int n;
bool cmpData(node x,node y){
	return x.data<y.data;
}
bool cmpIndex(node x,node y){
	return x.index<y.index;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d",&a[i].data);
		a[i].index=i;
	}
	//按照值排序，求rank 
	sort(a+1,a+n+1,cmpData);
	for(int i=1; i<=n; i++) a[i].rank=i;
	//按照下标排序，回复“原始顺序” 
	sort(a+1,a+n+1,cmpIndex);
	for(int i=1; i<=n; i++) printf("%d ",a[i].rank);
	return 0; 
}

```

---

## 作者：nynkqh_yzp (赞：0)

首先我们不关心每个数的值，那么可以对它离散化。

计算最少的删掉元素数，显然可以转化为求最大的保留元素数。

按照题意，保留的数可以形成一些题目要求的序列。

由于我们并不需要考虑每个元素分到哪个组，而且要严格保证顺序，所以考虑记录在该元素前的还未匹配的该元素在序列中的前一个值（例如，当遇到 $8$ 时，查看在其前面的还未匹配的 $4$ 的数量），如果有，则将其向后转移。

所以我们需要一个数组来记录每个值尚未匹配且在它所属的序列中之前的数都匹配的个数即可。

设保留的数的个数为 $x$，那么答案为：$n-6\times x$。

```cpp
#include <bits/stdc++.h>
using namespace std;
int s[10]={4,8,15,16,23,42};
int n,a[500001],b[11];
int c[50];
int main(){
	scanf("%d",&n);
	for(int i=0;i<6;i++)
		c[s[i]]=i+1;
	b[0]=0x3f3f3f3f;
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		if(b[c[a[i]]-1]>0)
			b[c[a[i]]]++,b[c[a[i]]-1]--;
	}
	printf("%d",n-b[6]*6);
	return 0;
}

```


---

## 作者：__LiChangChao__ (赞：0)

## 思路

计算最少的删掉元素数，显然可以转化为求**最大的保留元素数**。

因为我们并不在意每个元素具体的值，所以先对每个元素进行**离散化**。

如何求最大的保留元素数？

显然，保留下来的元素必然能构成若干个题目要求的序列。 

由于我们并不需要考虑每个元素分到哪个组，而且要严格保证顺序，所以考虑记录在该元素前的还未匹配的该元素在序列中的前一个值（例如，当遇到 $8$ 时，查看在其前面的还未匹配的 $4$ 的数量），如果有，则将其向后转移。 

显然，最后未匹配的第 $6$ 个元素的值就是要保留的序列数，设其为 $x$，则答案为：

$$n-x\times 6$$ 

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=5e5+5;
long long n,a[maxn],num[10];
int check[100];
int main(){
	check[4]=1,check[8]=2,check[15]=3,check[16]=4,check[23]=5,check[42]=6;//离散化 
	scanf("%lld",&n);
	num[0]=maxn;
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		a[i]=check[a[i]];
		if(num[a[i]-1])num[a[i]]++,num[a[i]-1]--;//后移 
	} 
	printf("%lld",n-num[6]*6);//计算答案 
}

```

---

## 作者：qfpjm (赞：0)

# 题解

- 这题的做法十分的精妙。

- 对于每一个数，我们不关心它在哪个子序列中，只关心它有没有出现和在几个子序列中。

- 我们可以记录下当前长度为 $1,2,3,4,5,6$ 的符合题目要求的子序列（或前面一部分）的个数。在遇到新的一个数时，我们看看还有没有刚好可以放下它的子序列。如果有，将那个子序列的长度 $+1$ 的子序列个数 $+1$，将那个子序列的个数 $-1$。

- 最后，$n$ 与 $6\times$ 完整的符合题目要求的子序列个数即为没用的数。

# 代码

- 由于用了许多三目运算符，可能有些阳间。

```cpp
#include <bits/stdc++.h>

using namespace std;

int n, a[500005], sum[500005];

int main()
{
	cin >> n;
	for (int i = 1 ; i <= n ; i ++)
	{
		int x;
		cin >> x;
		a[i] = (x == 4 ? 1 : (x == 8 ? 2 : (x == 15 ? 3 : (x == 16 ? 4 : (x == 23 ? 5 : 6)))));
	}
	for (int i = 1 ; i <= n ; i ++)
	{
		sum[1] += (a[i] == 1);
		int s = (a[i] != 1 && sum[a[i] - 1]);
		sum[a[i] - 1] -= s;
		sum[a[i]] += s;
	}
	cout << n - 6 * sum[6];
}
```



---

## 作者：lin_rany (赞：0)

看了一下题解，好像没有提到我这种做法。题意就是不断从a数组中提取给定的b数组,要求最后剩元素个数最少。

我们可以先考虑m=2的时候的做法，即用一个栈来操作，遇见a[1]栈push(i),遇见a[2]栈pop(),ans++。最后输出n-ans*2

同样的，我们可以考虑m>2时的做法，我们发现我们每次扫描只要考虑a[i]和a[i-1],然后就可以判定最大可以提取多少组了。最后输出n-ans*m即可。时间复杂度为O(n*m).
代码：
```cpp
#include<bits/stdc++.h>

#define ll long long
using namespace std;
template<class T>
void read(T& x)
{
	T res = 0, f = 1; char c = getchar();
	while (!isdigit(c)) {
		if (c == '-')f = -1; c = getchar();
	}
	while (isdigit(c)) {
		res = (res << 3) + (res << 1) + c - '0'; c = getchar();
	}
	x = res * f;
}
const ll N = 2000000 + 10;
const int mod = 1e9 + 7;
int n, a[N];
bool vis[N];
stack<int>p;
int b[] = { 0,4,8,15,16,23,42 };
int main()
{
	//ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen("test.in", "r", stdin);
#endif // ONLINE_JUDGE
	read(n);
	for (int i = 1; i <= n; i++)
	{
		read(a[i]);
		if (a[i] == b[1])vis[i] = 1;
	}
	for (int i = 2; i <= 6; i++)
	{
		while (p.size())p.pop();
		for (int j = 1; j <= n; j++)
		{
			if (a[j] == b[i - 1] && vis[j])p.push(j);
			else if (a[j] == b[i] && p.size())vis[j] = 1, p.pop();
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; i++)if (a[i] == b[6] && vis[i])ans++;
	printf("%d\n", n - ans * 6);
	return 0;
}


```


---

