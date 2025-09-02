# Sequence Transformation

## 题目描述

You are given a sequence $ a $ , initially consisting of $ n $ integers.

You want to transform this sequence so that all elements in it are equal (i. e. it contains several occurrences of the same element).

To achieve this, you choose some integer $ x $ that occurs at least once in $ a $ , and then perform the following operation any number of times (possibly zero): choose some segment $ [l, r] $ of the sequence and remove it. But there is one exception: you are not allowed to choose a segment that contains $ x $ . More formally, you choose some contiguous subsequence $ [a_l, a_{l + 1}, \dots, a_r] $ such that $ a_i \ne x $ if $ l \le i \le r $ , and remove it. After removal, the numbering of elements to the right of the removed segment changes: the element that was the $ (r+1) $ -th is now $ l $ -th, the element that was $ (r+2) $ -th is now $ (l+1) $ -th, and so on (i. e. the remaining sequence just collapses).

Note that you can not change $ x $ after you chose it.

For example, suppose $ n = 6 $ , $ a = [1, 3, 2, 4, 1, 2] $ . Then one of the ways to transform it in two operations is to choose $ x = 1 $ , then:

1. choose $ l = 2 $ , $ r = 4 $ , so the resulting sequence is $ a = [1, 1, 2] $ ;
2. choose $ l = 3 $ , $ r = 3 $ , so the resulting sequence is $ a = [1, 1] $ .

Note that choosing $ x $ is not an operation. Also, note that you can not remove any occurrence of $ x $ .

Your task is to find the minimum number of operations required to transform the sequence in a way described above.

You have to answer $ t $ independent test cases.

## 样例 #1

### 输入

```
5
3
1 1 1
5
1 2 3 4 5
5
1 2 3 2 1
7
1 2 3 1 2 3 1
11
2 2 1 2 3 2 1 2 3 1 2```

### 输出

```
0
1
1
2
3```

# 题解

## 作者：封禁用户 (赞：2)

## CF1454C Sequence Transformation 题解
### 解题思路
我们可以用一个类似**贪心**的方法去解决这道题。

首先，我们可以可以通过题目得知，我们的目标是给这个数组删去所有不为 $x$ 的数，并且删除次数最少，也就是说，需要**最优化**我们的删除操作。

如果序列 $a$ 中存在一个连续的子串，这个子串的 $\text{长度} \ge 2$，且这个子串中所有的数字相同，则在分割时不用在其中浪费删除次数，所以我们可以对这个数组进行一个特殊的处理，即：**如果有连续相同的数 $x$，则将这 $n$ 个数合并为一个 $x$。**

这时，我们可以对序列中每一个数的个数进行统计，方便最后的计算。假设 $x$ 的个数为 $m_x$，则必定有至少一个 $m_x \ge 1$ 成立。

这道题的数据范围是 $\sum n \le 2 \times 10 ^ {5}$，所以想枚举所有的方案是行不通的。在上面的计算过程中，我们将这个数进行了去重和统计，所以我们可以遍历 $m$，得出每一个 $m_x$ 都属于以下 $4$ 种方案之一：

- 不在左端点也不在右端点：$\text{最少次数} \gets m_x + 1$
- 不在左端点但在右端点：$\text{最少次数} \gets m_x$
- 在左端点但不在右端点：$\text{最少次数} \gets m_x$
- 在左端点也在右端点：$\text{最少次数} \gets m_x - 1$

此时我们可以通过最简单的打擂台求出最终答案，时间复杂度 $O(nt)$。

### 参考代码
```
#include<bits/stdc++.h>
using namespace std;
int t , n , a[200005] = {-1} , b[200005] , c[200005] , btmp , maxa , ans;
int check(int i)
{
	int tmp = 0;
	if(b[1] == i)
	{
		tmp++;
	}
	if(b[btmp - 1] == i)
	{
		tmp++;
	}
	return c[i] - tmp + 1;
}
int main()
{
	ios::sync_with_stdio(0);
	cin >> t;
	while(t--)
	{
		cin >> n;
		btmp = 1;
		maxa = -1;
		ans = 200001;
		for(int i = 1 ; i <= n ; i++)
		{
			cin >> a[i];
			maxa = max(maxa , a[i]);
		}
		for(int i = 0 ; i <= maxa ; i++)
		{
			c[i] = 0;
		}
		for(int i = 1 ; i <= n ; i++)
		{
			if(a[i] == a[i - 1])
			{
				continue;
			}
			b[btmp] = a[i];
			c[b[btmp]]++;
			btmp++;
		}
		for(int i = 1 ; i <= maxa ; i++)
		{
			if(c[i])
			{
				ans = min(check(i) , ans);
			}
		}
		cout << ans << endl;
	}
	return 0;
}
```
#### 感谢观看！

---

## 作者：fls233666 (赞：2)

### 题意简述：

你有一个长度为 $n$ 的整数序列 $a$ 。

你想要把序列 $a$ 的所有数字变成**相同**的。

你可以选择一个**至少在序列 $a$ 中出现一次**的数字 $x$ ,然后执行如下操作：选择一段**不包含**数字 $x$ 的区间 $[l,r]$ 并删除区间里面的所有数字。

注意，一旦你选择了一个数字 $x$ ，你在之后的操作中**不能更改** $x$。

现在要求让序列中所有数字变成相同的**最小**操作次数。

----

### 解题思路：

有一个显然的结论：**当你选择了一个确定的 $x$ ，完成所有删除操作后，剩下的数字一定都是 $x$ 。** 这个结论是显然的。因为在删除数字时，由于题目要求，选择的区间中都不包含 $x$ ，则 $x$ 一定会在最后被保留。

其次，因为是要最小化操作次数，所以**每次选择删的区间显然越长越好**。比如，设 $x$ 在序列 $a$ 中一次出现的位置为 $i$ ,在位置 $i$ 之后下一次 $x$ 出现的位置为 $j$ ，那么直接删除区间 $[i,j]$ 当中的所有数字显然是最优的。

有了上述结论，我们重新整理一下题意：

- 有一个长度为 $n$ 的整数序列 $a$ 。
- 选择一个**至少在序列 $a$ 中出现一次**的数字 $x$ ，使序列 $a$ 中每段连续的 $x$ 把序列 $a$ 分成的段数最少。

有人可能就会问了：为什么是最小化序列 $a$ 中每段连续的 $x$ 把序列 $a$ 分成的段数？

因为对于序列 $a$ 中每段连续的 $x$ 之间的数字，都是要全部删除的。而为了最小化操作次数，则这些在 $x$ 的连续段之间的数字会被一次删掉。最后显然有**序列 $a$ 中每段连续的 $x$ 把序列 $a$ 分成的段数 $=$ 最小的删除操作次数**。

那么接下来考虑如何实现代码。

------

首先，我们发现序列 $a$ 中各个相同数字的连续段由于长度不定，不太容易处理，所以考虑压缩各个相同数字的连续段。**把每个相同数字连续段压缩成一个数字**，得到一个新的序列 $a'$。

其次，在开始统计之前，考虑特殊情况。（ _下面用 $a_i$ 表示其它数字_ ）

- 情况①：$x_1,a_1,a_2,x_2,a_3,a_4,x_3$ 【样例中的第四组测试数据】
- 情况②：$a_1,a_2,a_3,a_4,x_1,a_5,a_6,a_7,x_2,a_8,a_9$ 【样例中的第五组测试数据】

这些情况说明了当 $x$ 出现在开头和结尾时要特判。**当 $x$ 第一次出现时，特判是否出现在开头，如果不是则说明 $x$ 左侧有其它数字，划分段数增加。对于除了出现在结尾的 $x$ 之外 ，它们的右侧都分别有一段其它的数字，划分段数增加。**

统计完成后，为了更快速的统计答案，可以把重复的数字去除。这样对于每种数字只可能更新答案一次，提高了程序运行效率。

---------

### 解题代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring> 
#define ll long long
#define rgt register int
#define qmn(a,b) a<b?a:b
using namespace std;
const int mxn = 2e5+5;
int cnt[mxn],ap[mxn],a[mxn],xa[mxn];
int len,lxa,n,ans;
int main(){
	int test;
	scanf("%d",&test);
	while(test--){
		memset(cnt,0,sizeof(cnt));
		len=lxa=0;  //重置，初始化
        
		scanf("%d",&n);
		for(rgt i=1;i<=n;i++){
			scanf("%d",&a[i]);  //读入序列a
			if(a[i]!=a[i-1]){  //压缩序列段，得到序列xa
				lxa++;
				xa[lxa]=a[i];
			}
		}
        
		for(rgt i=1;i<=lxa;i++){  //按上述规则统计
			if(!cnt[xa[i]]){    //特判第一次出现
				if(i>1)  //不在开头，左侧有数组，划分段数++
					cnt[xa[i]]++;
				len++;   //加入最终的答案筛选数组
				ap[len]=xa[i];
			}
			if(i<lxa)  //不在结尾，划分段数++
				cnt[xa[i]]++;
		}
        
		ans=cnt[ap[1]];
		for(rgt i=2;i<=len;i++){
			ans=qmn(ans,cnt[ap[i]]);  //取最小值，得到答案
		}
		printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：胖头鱼学员 (赞：2)

# CF1454C

## [CF传送门](https://codeforces.com/contest/1454/problem/D)
## [洛谷传送门](https://www.luogu.com.cn/problem/CF1454C)

## $Question Meaning$

给你$n$个数，先选择一个$a_1 \sim a_n$中的数,再删掉多段连续的数，使得删掉的数中不包含$x$，求让删的次数最小的$x$。

## $Solution$

显然，选择的$x$在原数组中出现次数必定最少，那么选择出现次数最小的即可。

## $Code$
```cpp
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int kMaxN = 10000;
const int kInf = 1e9 + 1;

int T, n, ans;

void solve() {
  scanf("%d", &n);
  vector<int> a(n);
  for (auto &it : a) {
    cin >> it;
  }
  vector<int> res(n + 1, 1);
  n = unique(a.begin(), a.end()) - a.begin();
  a.resize(n);
  for (int i = 0; i < n; i++) {
    res[a[i]]++;
  }
  res[a[0]] -= 1;
  res[a[n - 1]] -= 1;
  ans = kInf;
  for (int i = 0; i < n; ++i) {
    ans = min(ans, res[a[i]]);
  }
  printf("%d\n", ans);
}

int main() {
  scanf("%d", &T);
  while (T--) {
    solve();
  }
  return 0;
}
```

---

## 作者：KSToki (赞：1)

显然我们可以暴力枚举 $x$ 统计答案，于是考虑统计的方法。显然两个相邻的 $x$ 是不会对答案产生贡献的，那么我们在输入时将数列压缩保证任意相邻的两数不同即可，做法是如果当前数与上一个输入的数相同则忽略此输入，并把数组长度减一。

这里令 $cnt[x]$ 为 $x$ 在处理后的数列中出现的次数，分类讨论即可。

- $x$ 既不在开头也不在结尾，答案为 $cnt[x]+1$。
- $x$ 仅在开头或仅在结尾，答案为 $cnt[x]$。
- $x$ 既在开头也在结尾，答案为 $cnt[x]-1$。

应该很清晰了，可以画个图理解一下。

这题没什么坑，不要每次 `memset`，如果他没保证 $a_i\le n$ 只需离散化一下。

代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
using namespace std;
#define pii pair<int,int>
#define mp(x,y) make_pair(x,y)
#define piii pair<pair<int,int>,int>
#define mp3(x,y,z) make_pair(make_pair(x,y),z)
#define fi first.first
#define se first.second
#define th second
#define putint(x) printf("%d\n",x);
#define putll(x) printf("%lld\n",x);
#define putull(x) printf("%llu\n",x);
inline int read()
{
	char ch=getchar();
	int res=0,flag=1;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			flag=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res*flag;
}
int T,n,a[200001],cnt[200001];
int main()
{
	T=read();
	while(T--)
	{
		n=read();
		for(int i=1;i<=n;++i)
			cnt[i]=0;
		int tmp=n;
		for(int i=1;i<=tmp;++i)
		{
			a[i]=read();
			if(a[i]==a[i-1])
			{
				--i;
				--tmp;
				continue;
			}
			++cnt[a[i]];
		}
		int ans=min(cnt[a[1]],cnt[a[tmp]]);
		if(a[1]==a[tmp])
			--ans;
		for(int i=1;i<=tmp;++i)
			ans=min(ans,cnt[a[i]]+1);
		putint(ans);
	}
	return 0;
}
```

---

## 作者：hanzhang666 (赞：0)

# 特判  
**第一种情况：** 

``` 1 1 1 ```  

如果所有数都相等，输出 $0$ 即可。

**第二种情况：** 

``` 1 3 5 1 ```

如果首尾相等且该数只出现 $2$ 次，输出 $1$ 。

**第三种情况：** 

``` 1 3 5 5 ``` 或  ``` 4 2 2 1 ```

首或尾数只出现一次，输出 $1$ 。

# 注意

1. 输入时相邻两数去重；
2. 首尾去除；
3. 找到出现次数最少的数，用其出现次数加 $1$ 即可。

# 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[1000006],b[1000006];
signed main(){
	int T;
	cin>>T;
	int maxn=0;
	while(T--){
		maxn++;
		for(int z=1;z<=maxn+1;z++){
			b[z]=0;
		}
		int n;
		cin>>n;
		maxn=-0x3f;
		bool v=1;
		for(int z=1;z<=n;z++){
			cin>>a[z];
			if(a[z]!=a[z-1]){
				b[a[z]]++;
			}
			maxn=max(a[z],maxn); 
			if(a[z]!=a[z-1]&&z-1!=0){
				v=0;
			}
		}
        //特判
		if(v){
			cout<<0<<endl;
			continue;
		}
		if(a[1]==a[n]){
			if(b[a[1]]==2){
				cout<<1<<endl;
				continue;
			}
		}
		if(b[a[1]]==1||b[a[n]]==1){
			cout<<1<<endl;
			continue;
		}
		b[a[1]]--;
		b[a[n]]--;//去除首尾
		int minn=1e9;
		int mi=1;
		for(int z=1;z<=maxn;z++){
			if(b[z]<minn&&b[z]!=0){
				minn=b[z];
				mi=z;
			}
		}
		cout<<b[mi]+1<<endl;//输出
	}
}

```

---

## 作者：Dragonbell_exp (赞：0)

### 思路
举个例子：有一根木条，从木条中间切一刀，这个木条会被分成两段；从木条中间切 $m$ 刀，这个木条会被分成 $m+1$ 段。也就是说，切得刀数越多，分成的段数也就越多。

当我们把题目中给的 $x$ 想象成木条两段之间的切痕（这个切痕可大可小，形如 $y$ $xxx$ $y$ 的数列和 $y$ $x$ $y$ 没有区别）；把分割出的木条想象成一段不包含 $x$ 的区域，就可以得出一个显然的结论：**指定的全部为数字 $x$ 的区域出现次数越小，操作次数就越少。**

这是因为为了使操作次数尽量小，必须要每次的把一段不包含 $x$ 的区域全部删除，最终只留下 $x$。

再来考虑一种情况，如果选择的 $x$ 在数列两侧，形成了诸如 $x$ $y$ $x$ 的形式。以刚才发现的规律来看，所需的操作次数看似是 $3$ 刀，但实际上需要的次数却是 $1$ 刀。因为在边缘的 $x$ 无法将整个数列分成两段，要舍去。
### 做法
第一步，分段。也就是把 $y$ $xxx$ $yy$ 组合成 $y$ $x$ $y$ 的形式。

第二步，寻找不同数字段的出现次数。以第一步的例子来看，$y$ 出现了 $2$ 次，$x$ 出现了 $1$ 次。

第三步，删除首尾元素。在第一步的例子中，首尾都是 $y$，所以 $y$ 的出现次数要减 $2$ 。

第四步，查找并输出。找出出现次数最小的数字段并按照刚才说的规律输出。

详见代码。
### 代码：
```cpp
#include<iostream>
#include<cmath>
#define int long long
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
	while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int t,n;
int a[1000000];//a是读入数组
int b[1000000],cnt;//b是分段数组，cnt是段数
int c[1000000],mx,mn,mm;//c是每个段出现的次数，mx是a中最大值，mn是a中最小值，mm是c中最小值
signed main(){
	t=read();
	while(t--){
		n=read();
		cnt=0;//初始化
		mx=0;
		mn=2e5+5;
		mm=2e5+5;
		for(register int i=1;i<=n;i++){
			a[i]=read();
			mx=max(mx,a[i]);//找出最大值和最小值（主要是为了初始化c，但是删掉应该也行。
			mn=min(mn,a[i]);
		}
		for(register int i=1;i<=n;i++){//分段
			if(a[i]!=a[i-1]){
				b[++cnt]=a[i];
			}
		}
		for(register int i=mn;i<=mx;i++){//初始化c
			c[i]=0;
		}
		for(register int i=1;i<=cnt;i++){//计算每一段出现的次数
			c[b[i]]++;
		}
		c[a[1]]--;//删除首尾元素
		c[a[n]]--;
		for(register int i=1;i<=cnt;i++){//计算出现次数最少的短
			mm=min(mm,c[b[i]]);
		}
		cout<<mm+1<<endl;//输出
	}
	return 0;
}
```


---

