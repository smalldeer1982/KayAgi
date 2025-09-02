# Mark and His Unfinished Essay

## 题目描述

One night, Mark realized that there is an essay due tomorrow. He hasn't written anything yet, so Mark decided to randomly copy-paste substrings from the prompt to make the essay.

More formally, the prompt is a string $ s $ of initial length $ n $ . Mark will perform the copy-pasting operation $ c $ times. Each operation is described by two integers $ l $ and $ r $ , which means that Mark will append letters $ s_l s_{l+1} \ldots s_r $ to the end of string $ s $ . Note that the length of $ s $ increases after this operation.

Of course, Mark needs to be able to see what has been written. After copying, Mark will ask $ q $ queries: given an integer $ k $ , determine the $ k $ -th letter of the final string $ s $ .

## 说明/提示

In the first test case, the copy-paste process is as follows.

- The first step is pasting string $ \texttt{mark} $ at the end, yielding the string $ \texttt{mark}\color{red}{\texttt{mark}} $ .
- The second step is pasting string $ \texttt{mar} $ at the end, yielding the string $ \texttt{markmark}\color{red}{\texttt{mar}} $ .
- The third step is pasting string $ \texttt{rkmark} $ at the end, yielding the string $ \texttt{markmarkmar}\color{red}{\texttt{rkmark}} $ .

In the second test case, the copy-paste process is as follows.

- The first step is pasting string $ \texttt{re} $ at the end, yielding the string $ \texttt{creamii}\color{red}{\texttt{re}} $ .
- The second step is pasting string $ \texttt{ea} $ at the end, yielding the string $ \texttt{creamiire}\color{red}{\texttt{ea}} $ .
- The third step is pasting string $ \texttt{reamiire} $ at the end, yielding the string $ \texttt{creamiireea}\color{red}{\texttt{reamiire}} $ .

## 样例 #1

### 输入

```
2
4 3 3
mark
1 4
5 7
3 8
1
10
12
7 3 3
creamii
2 3
3 4
2 9
9
11
12```

### 输出

```
m
a
r
e
a
r```

# 题解

## 作者：Noby_Glds (赞：7)

我的代码算短的了。
### 思路：
我们可以发现，任何一个新增的字符，都是由之前的字符复制过来的。

所以，我们可以想个办法，让一个新增的位置回溯到原字符串中的某一个位置。

可以发现，复制的次数非常小，所以我们可以~~乱搞~~**从后往前**遍历每次复制操作。（不能从前往后遍历，不用我赘述。）

如果我们所求的目标位置在粘贴区间内，就回溯到原区间的对应位置。

不断回溯，就可以找到答案。
### 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,c,q,x,y,len,l[45],r[45],cha[45];
char a[200010];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n>>c>>q;
		for(int i=1;i<=n;i++) cin>>a[i];
		len=n;
		for(int i=1;i<=c;i++){
			cin>>l[i]>>r[i];
			cha[i]=len-l[i]+1;//每个粘贴的位置和其对应的原位置之间的差值是一定的，我们把这个差值记下来。
			len+=r[i]-l[i]+1;
		}
		while(q--){
			cin>>x;
			for(int i=c;i;i--) if(x>=l[i]+cha[i]&&x<=r[i]+cha[i]) x-=cha[i];//减去差值，回溯到对应位置。
			cout<<a[x]<<endl;
		}
	}
	return 0;
} 
```


---

## 作者：Jeremiahy (赞：5)

## 题意

给出长度为 $n$ 的字符串 $s$，进行 $c$ 次复制操作，每次操作给出 $l$ 和 $r$，将 $s_l$，$s_{l+1}$，···，$s_{r}$ 接在 $s$ 后面，接着有 $q$ 次询问，每次询问有一个数 $k$，询问 $s_k$ 是什么字符。

# 分析

首先看一下数据范围：$1\le l\le r\le 10^{18}$，$1\le k\le 10^{18}$。

这么大的范围，数组肯定开不下，这就需要我们发现其中的规律：变化后的字符串每个字符都在原序列中出现过。于是我们可以寻找进行几次复制操作（设为 $i$ 次）后可以到达 $k$ 这么大的下标，这时 $a_k$ 就等于 $a_{l_i+k-sum_{i-1}-1}$（$sum_i$ 指进行 $i$ 次操作后字符串的长度），如此递归下去，即可将 $k$ 缩小到 $[1,n]$，直接就可输出。

另外，因为数据范围达到了 $10^{18}$，所以要开 long long。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
struct node {
	int l, r;
}ch[42];
int t, n, sum[42], k, c, q; 
char a[200010];
int query(int m) {
	if (m <= n) //到达 1 ~ n 的范围
		return m;
	int z = lower_bound(sum + 1, sum + c + 1, m) - sum;//寻找i
	if (sum[z] > m) {
		z--;
		return query(m - sum[z] + ch[z + 1].l - 1);//递归查询
	}
	return query(ch[z].r);//正好是右边界。
}
signed main () {
	cin >> t;
	while (t--) {
		cin >> n >> c >> q;
		cin >> a + 1;
		sum[0] = n;
		for (int i = 1; i <= c; i++)
			cin >> ch[i].l >> ch[i].r, sum[i] = sum[i - 1] + ch[i].r - ch[i].l + 1;//读入及预处理
		while (q--) {
			cin >> k;
			cout << a[query(k)] << "\n";
		}
	}
	return 0;
}
```


---

## 作者：Dr_Gilbert (赞：3)

# CF1705C Mark and His Unfinished Essay

【题目大意】给定一个长度不超过 $2\times 10^5$ 的原串，进行不超过 $40$ 次操作，每次操作把字符串的 $[l,r]$ 区间复制并拼接到字符串末尾。最后有不超过 $10^4$ 次询问，每次询问最终得到的字符串的第 $x$ 个字符。

不难发现，如果模拟拼接字符串的过程，在极限情况下最终的串长度可以达到 $2\times 10^{17}$，无论是时间还是空间都是不可接受的。不过从题意我们可以发现，每次复制是在前面复制的基础上进行的，所以可以只记录每次复制前面字符串的 $[l,r]$，记录每次完成修改后的字符串长度，查询时往前跳即可。

具体地，首先在记录每次修改后的串长数组中二分出询问的坐标 $x$ 是在哪次操作后产生的，然后通过记录的 $[l,r]$ 推算出对应的坐标 $x$ 在这次操作前的字符串中对应的坐标，这样就成为了一个子问题，可以迭代或递归求解。单次询问时间复杂度 $\mathcal O(c\log c)$。具体实现有一些细节，可以参考代码实现。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=50;
string str;int s[N];
pair<int,int> ch[N];
char solve(int lim, int x){
    int pos=lower_bound(s+1,s+1+lim,x)-s-1;
    int nxt=x-s[pos]+ch[pos].first-1;
    if (pos==0) return str[nxt];
    return solve(pos-1,nxt);
}
signed main(){
    int t;cin>>t;
    while (t--){
        int n,c,q;cin>>n>>c>>q;
        ch[0].first=1,ch[0].second=n;
        cin>>str;str='0'+str;s[1]=n;
        for (int i=1;i<=c;i++){
            cin>>ch[i].first>>ch[i].second;
            s[i+1]=s[i]+ch[i].second-ch[i].first+1;
        }
        for (int i=1;i<=q;i++){
            int x;cin>>x;cout<<solve(c,x)<<endl;
        }
    }
    return 0;
}
```





---

## 作者：happy_dengziyue (赞：2)

### 1 视频题解

![](bilibili:BV1ud4y1Q7f5)

### 2 思路

我们可以发现，只要知道了操作一次后要求的位置，就能够通过它反向推断出，操作前的对应位置。

因为 $c$ 特别小，但是 $l$ 和 $r$ 都特别大，所以我们可以一步步模拟。

具体来说，设操作 $i$ 次后字符串长度为 $cnt[i]$，要求的位置为 $x$，那么操作 $i-1$ 次前，对应的位置就是 $x-cnt[i-1]+l[i]-1$。

模拟即可。

### 3 代码与记录

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
#define max_n 200000
int t;
int n;
int c;
int q;
char s[max_n+2];
long long l[42];
long long r[42];
long long cnt[42];
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1705C_1.in","r",stdin);
	freopen("CF1705C_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d%d%d%s",&n,&c,&q,s+1);
		for(int i=1;i<=c;++i)scanf("%lld%lld",l+i,r+i);
		cnt[0]=n;
		for(int i=1;i<=c;++i)cnt[i]=cnt[i-1]+(r[i]-l[i]+1);
		for(int i=1;i<=q;++i){
			long long x;
			scanf("%lld",&x);
			for(int j=c;j>=1;--j){
				if(cnt[j-1]<x&&x<=cnt[j])x=x-cnt[j-1]+l[j]-1;
			}
			printf("%c\n",s[x]);
		}
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/80111603)

By **dengziyue**

---

## 作者：RoFtaCD (赞：1)

蒟蒻的第一篇题解（悲）

首先读题：

>One night, Mark realized that there is an essay due tomorrow. He hasn't written anything yet, so Mark decided to randomly copy-paste substrings from the prompt to make the essay.

可以发现 Mark 非常的强（雾）居然通过暴力乱搞来完成他的~~润~~文。

然后康一眼数据范围

$ 1\leq n\leq 2\cdot 10^5$ ，$c\leq 40$  

$ 1\leq q\leq 10^4 $ ，$ 1\leq l\leq r\leq 10^{18} $ ，$ 1\leq k\leq 10^{18} $


发现 $l,r$ 的范围很大，如果用直接模拟复制操作字符串长度可以达到 $10^{18}$ 级别，时间和空间都会爆）

不能直接复制字符串模拟，发现 $c\leq 40$ ，不是一般的小。考虑把每次复制操作存下来。

自然地想到查询时可以先寻找在第几次操作后字符串的长度才能大于等于，暴力扫描每次复制后的长度即可 $k$。

然后每次复制操作的 $l,r$ 都不会超过之前操作后字符串的总长度，并且字符串长度增加的 $r-l+1$ 是由先前字符串的一部分复制来的，所以查找当前位置在上一次复制操作的 “复制源” 的位置。

重复执行，一直到下标在原始字符串长度内，就是 Mark 最开始复制的那个字符。

（那个字符经过了 Mark  奇（残）妙 （暴）乱搞操作后居然被复制到了论文的那么后面，十分的奇妙）。

时间复杂度 $O(cq)$ ，看起来确实很对）

思考，代码并不难，需要注意存储时要使用 `long long` 以及递归求解的写法。

下面是参考代码，有一些细节可以看代码注释。


------------



### 代码：

```cpp
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <algorithm>
const int N=2e5+15;
using namespace std;
typedef long long ll;

int t,c,q;
ll len[45],cp[45][2];
char a[N];

void solve(ll x){  / /递归求解，x 表示这次询问在之前那次操作时的下标
	int pt=0;
	if(x<=len[0]){printf("%c\n",a[x-1]);return;}
	while(len[pt]<x) ++pt;  //没有必要二分查找
	x-=len[--pt];  //减去先前字符串的长度
	solve(cp[pt+1][0]-1+x);  //字符串 s 粘贴位置的字符=对应复制位置的字符
	return;
}

int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%lld%d%d%s",&len[0],&c,&q,a);
		for(ll i=1;i<=c;++i)
			scanf("%lld%lld",&cp[i][0],&cp[i][1]),len[i]=len[i-1]+cp[i][1]-cp[i][0]+1; 
            	//输入时存储左，右端点，顺便处理长度
                
		while(q--){
			ll k;scanf("%lld",&k);
			solve(k);
			
		}
	}

	return 0;
}
```



---

## 作者：niaoji (赞：0)

## 题目大意
给你一个长度不超过 $2 \times 10^5$ 的字符串每次操作将位于 $l$ 到 $r$ 之间的字符复制粘贴到字符串的末尾（此操作不超过 40 次），对于 $q$ 次询问，每次问一个位置 $k$，输出第 $k$ 个位置上的字符。
## 题目分析
尽管复制操作只有 40 次，但是 $2 \times 10^5$ 的长度使用暴力明显不现实。  
但是可以从这 40 次入手，考虑每次操作并记录要复制后的新位置，再递推到最初的字符串即可。
## 关键代码
```c
while(t--)
{
	int n,c,q;
	cin>>n>>c>>q;
	string s;
	cin>>s;
	s=" "+s;
	vector<long long> left(c+1),right(c+1),d(c+1);
	right[0]=n;
	left[0]=1;
	for(int i=1;i<=c;i++)
	{
		long long l,r;
		cin>>l>>r;
		left[i]=right[i-1]+1;
		right[i]=left[i]+r-1;
		d[i]=left[i]-l;
	}
	while(q--)
	{
		long long x;
		cin>>x;
		for(int i=c;i>=1;i--)
		{
			if(left[i]<=x&&x<=right[i]) x-=d[i];
		}
		cout<<s[x]<<endl;
	}
}
```

---

## 作者：wanyiheng (赞：0)

### 题目思路：

根据题意，我们可以看出任何一个字符都是之前序列中出现过的。看一看数据范围 $1 \le l \le r \le 10^{18} , 1 \le k \le 10^{18}$，范围太大，开数组会爆。根据之前的分析，可以发现我们只需通过回溯到原序列中的某一个位置就可以得到答案。

### **code：**

```cpp
#include<bits/stdc++.h>

using namespace std;

#define int long long

const int N=200010,C=50;

int t,n,c,q,x,y,len,l[C],r[C],cha[C];
char a[N];

int query(int x){
	for(int i=c;i;i--){
		if(x>=l[i]+cha[i]&&x<=r[i]+cha[i]){
			x-=cha[i];
		}
	}
	return x;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n>>c>>q;
		for(int i=1;i<=n;i++)cin>>a[i];
		len=n;
		for(int i=1;i<=c;i++){
			cin>>l[i]>>r[i];
			cha[i]=len-l[i]+1;
			len+=r[i]-l[i]+1;
		}
		while(q--){
			cin>>x;
			cout<<a[query(x)]<<endl;
		}
	}
	
	return 0;
} 
```

---

## 作者：__AFO__ (赞：0)

## 题解

一道类似于递归的题，先利用前缀和算出每一次操作的区间，再利用二分答案找出要求的字母位置属于那个区间，看他在这个区间的位置，来确定下一次递归，找到在字符串内时，就立刻输出。

 _代码_ ：
 ```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,c,q,sum[1005],m,u;
string s;
struct nn{
	long long x,y,c;
}a[1005];
void find(long long m){
	 if(m<=s.size()){
	 	cout<<s[m-1]<<endl;
	 	return;
	 }else{
	 	u=lower_bound(sum,sum+1+c,m)-sum;
	 	find(a[u].y-(sum[u]-m));
	 }
	 return;
}
int main() {
	scanf("%lld",&t);
	while(t--) {
		scanf("%lld%lld%lld",&n,&c,&q);
		cin>>s;
		sum[0]=s.size();
		for(long long i=1; i<=c; i++) {
			scanf("%lld%lld",&a[i].x,&a[i].y);
			a[i].c=a[i].y-a[i].x+1;
			sum[i]=sum[i-1]+a[i].c;
		}
		for(long long i=1;i<=q;i++){
			scanf("%lld",&m);
			find(m);
		}
	}



	return 0;
}
```


## 完结撒花

---

## 作者：Addicted_Game (赞：0)

## [Mark and His Unfinished Essay](https://www.luogu.com.cn/problem/CF1705C)

### 题目大意
先进行 $c$ 此操作，将 $s_{l_i}$ 与 $s_{r_i}$ 复制到 $s$ 之后，再进行 $q$ 次询问，每次给定一个数 $k_i$ 要求输出操作后的 $s_{k_i}$。

### 思路
输出当前位置的字符，我们可以想到去找原串的对应位置。借用倍增思想，往前跳区间，用二分找每次跳到的区间，直到在原本的字符串之内。

### 部分代码
```cpp
while(true){
	if(k<=n){
		printf("%c\n",s[k]);
		break;
	}
## 	long long t=lower_bound(sum+1,sum+c+1,k)-sum;//哪一个区间 sum是记录字符串长度的前缀和
	k=r[t]-(sum[t]-k+1)+1;//区间的对应位置
} 
```

---

## 作者：DBL_MAX (赞：0)

题目：[CF1705C](https://www.luogu.com.cn/problem/CF1705C)
# 续
[上次](https://www.luogu.com.cn/blog/726044/cf1705c-di-ti-xie)说了本题的解法，这次~~给不太熟悉 STL 的同学~~引申一下 lower_bound 和 upper_bound 的用法。详情请看下文。
## 介绍
### lower_bound
- `lower_bound` 函数用于在指定区域内查找不小于目标值的**第一个**元素。也就是说，使用该函数在指定范围内查找某个目标值时，最终查找到的**不一定**是和目标值相等的元素，还可能是**比目标值大**的元素。

- 定义该函数的头文件：`<algorithm>`。
***

该函数有以下 $2$ 种语法格式：

1. 在 $[first, last)$ 区域内查找不小于 $val$ 的元素。
它的语法格式为：
```cpp
lower_bound (ForwardIterator first, ForwardIterator last,const T& val);
```

2. 在 $[first, last)$ 区域内查找第一个不符合 $comp$ 规则的元素。
它的语法格式为：
```cpp
lower_bound (ForwardIterator first, ForwardIterator last,const T& val, Compare comp);
```
***
其中，$first$ 和 $last$ 都为正向迭代器，$[first, last)$ 用于指定函数的作用范围；$val$ 用于指定目标元素；$comp$ 用于自定义比较规则，此参数可以接收一个包含 $2$ 个形参（第二个形参值始终为 $val$）且返回值为 bool 类型的函数，可以是普通函数，也可以是函数对象。
***
函数返回值：
函数返回的是一个正向迭代器。当查找成功，该迭代器指向找到的元素。如果查找失败，迭代器的指向和 $last$ 迭代器相同。
***

### upper_bound
- 功能：用于在指定范围内查找**大于**目标值的**第一个**元素。

- 定义该函数的头文件： `<algorithm>` 。
***
该函数的语法格式有 $2$ 种，分别是：
1.  查找 $[first, last)$ 区域中第一个**大于** $val$ 的元素。
```cpp
upper_bound (ForwardIterator first, ForwardIterator last,const T& val);
```
2.  查找 $[first, last)$ 区域中第一个**不符合** $comp$ 规则的元素。
```cpp
upper_bound (ForwardIterator first, ForwardIterator last,const T& val, Compare comp);
```

***
- 其中，$first$ 和 $last$ 都为正向迭代器，$[first, last)$ 用于指定该函数的作用范围；$val$ 用于执行目标值；$comp$ 作用自定义查找规则，此参数可接收一个包含 $2$ 个形参（第一个形参值始终为 $val$）且返回值为 bool 类型的函数，可以是普通函数，也可以是函数对象。

- 实际上，第一种语法格式也设定有比较规则，即使用 $<$ 比较 $[first, last)$ 区域内某些元素和 $val$ 的大小，直至找到一个大于 $val$ 的元素，只不过此规则**无法改变**。这也意味着，如果使用第一种语法格式，则 $[first,last)$ 范围的元素类型**必须支持** $<$ 运算符。

- 函数返回值：和 `lower_bound` 一样，函数会返回一个正向迭代器。当查找成功时，迭代器指向找到的元素；反之，如果查找失败，迭代器的指向和 $last$ 迭代器相同。
***

## 本题思路
用二分加上一些特殊处理，这题就完成了。

定义一个结构体，存储待处理序列的左端点和右端点。

读入时用 $sum$ 数组维护调整序列，再用 `lower_bound` 找到第一个大于等于待处理元素的位置，接着用递归处理下一个元素。

### 解题步骤
1. 读入

1. 处理 $sum_l\sim sum_r$，从读入的字符串 $l\sim r$ 区间内向 $sum_l\sim sum_r$ 里传。

1. 调用二分函数，递归解决问题。递归函数返回字符数组下标。

1. 输出字符数组中刚刚求得的下标对应的字符。
***
## 结语
代码先不放了，有需要的同学可以在文章开头的链接里继续学习哦！

---

## 作者：Michael1234 (赞：0)

- 本题可以使用**二分查找**的思路：

- 首先，维护一个 $len$ 数组，用于储存每次操作后字符串长度。

- 简单的推导公式：$len_i=len_{i-1}+(r_i-l_i+1)$，记得将 $len_0$ 初始化为 $n$。

- 接下来，每次输入询问 $k$ 后，二分查找到 $k$ 在哪个 $len_{now}$ 与 $len_{now-1}$ 之间，那么，将 $k$ 减去 $len_{now}-r_{now}$。

- 这样得到的仍然是原来的字符。

## CODE

~~~cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll N=2e5+5;
ll t,n,c,q,l[N],r[N],k,now,len[N];
char str[N];
ll binary_search(ll x)
{
	ll l=1,r=c,mid;
	while(l<r)
	{
		mid=(l+r)/2;
		if(len[mid]<x)//没到所在区间
		{
			l=mid+1;//往后找
		}
		else
		{
			r=mid;
		}
	}
	return l;
}//二分查找
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n>>c>>q>>str;
		len[0]=n;//初始化！
		for(ll i=1;i<=c;i++)
		{
			cin>>l[i]>>r[i];
			len[i]=len[i-1]+(r[i]-l[i]+1);//按照公式维护
		}
		while(q--)
		{
			cin>>k;
			while(k>n)//缩回原字符串
			{
				now=binary_search(k);//所在区间
				k-=(len[now]-r[now]);//按照公式往下找
			}
			cout<<str[k-1]<<"\n";//下标从0开始！
		}
	}
	return 0;
}

---

## 作者：DBL_MAX (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1705C)


# 思路
用二分加上一些特殊处理，这题就完成了。

定义一个结构体，存储待处理序列的左端点和右端点。

读入时用 $sum$ 数组维护调整序列，再用 `lower_bound` 找到第一个大于等于待处理元素的位置，接着用递归处理下一个元素。

### 步骤
1. 读入

1. 处理 $sum_l\sim sum_r$，从读入的字符串 $l\sim r$ 区间内向 $sum_l\sim sum_r$ 里传。

1. 调用二分函数，递归解决问题。递归函数返回字符数组下标。

1. 输出字符数组中刚刚求得的下标对应的字符。
***

# Code
```cpp
#include <bits/stdc++.h>//万能头文件
using namespace std;//定义命名空间
#define int long long//不开long long见祖宗
struct node { //定义结构体
	int l, r;
	//在结构体中定义2个变量，这种类型的变量有这两个小变量
} ch[101]; //定义个node类型的数组
int t, n, sum[101], k, c, q; //定义题目所需的变量/数组
char a[200010];

int search(int m/*定义函数的参数*/) { //定义函数，返回值类型int(实际上是long long)
	if (m <= n)
		return m;//如果m不大于n，就把m return掉
	int p = lower_bound(sum + 1, sum + c + 1, m) - sum; //lower_bound(首地址,末地址,查找的值)-首地址，返回第一个大于等于待查找数字的位置，可以直接当做数组下标
	if (sum[p] > m) {
		p--;
		return search(m - sum[p] + ch[p + 1].l - 1);
	}
}

signed main() { //signed=int
	cin >> t; //读入t
	while (t--) { //等于while(t--!=0)
		cin >> n >> c >> q; //读入*3
		cin >> a + 1; //还是读入
		sum[0] = n; //将sum数组的0号元素的值设置为1
		for (int i = 1; i <= c; i++) { //i从1开始，i<=c,i每次+1
			cin >> ch[i].l >> ch[i].r, sum[i] = sum[i - 1] + ch[i].r - ch[i].l + 1; //读入
		}
		while (q--) { //和上面一样
			cin >> k;
			cout << a[search(k)] << "\n"; //  \n和endl都可以换行
		}
	}
	return 0;//好习惯
}
```
好了，我的题解写完了，再见！

---

## 作者：WaterSun (赞：0)

# 思路

首先我们定义一个结构体，其中维护 $l,r,len$，表示每一次操作输入的 $l$ 和 $r$，以及 $s_l \sim s_r$  的长度。

对于每一次修改操作，我们将新的信息加入结构体中。

对于每一次查询操作，我们可以定义一个函数：$\operatorname{f}(x)$。它的作用是：查询在新的字符串中下标为 $x$ 的字符对应在原字符串中的下标位置。

这个函数可以通过递归的方式来实现，我们按照插入的顺序来计算 $x$ 应在的位置：

```cpp
inline int f(int x){
	for (int i = 1;i <= idx;i++){
		if (x <= arr[i].len){//如果 x <= arr[i].len 说明了 x 一定在 arr[i].l ~ arr[i].r 这个区间中 
			int t;
			/*
			我们先假设当前算出来的结果能够符合条件，那么，我们应该返回的下标不就应该为：arr[i].l + x - 1 吗？
			但是，我们可以发现一个问题：我们 arr[i].l + x - 1 也是有可能不在原字符串区间中的，于是，我们必须继续递归下去 
			*/
			if (arr[i].l + x - 1 > n) t = f(arr[i].l + x - 1);//递归 
			else t = arr[i].l + x - 1;//成立 
			return t;//返回 
		}
		else x -= arr[i].len;//说明 x 一定不在 arr[i].l ~ arr[i].r 区间中 
	}
}
```

# code

```cpp
#include <bits/stdc++.h>
#define int long long
#define re register

using namespace std;

const int N = 1e4 + 10;
int T,n,q,Q,idx;
string s;

struct node{
	int l;
	int r;
	int len;
}arr[N];

inline int f(int x){
	for (int i = 1;i <= idx;i++){
		if (x <= arr[i].len){//如果 x <= arr[i].len 说明了 x 一定在 arr[i].l ~ arr[i].r 这个区间中 
			int t;
			/*
			我们先假设当前算出来的结果能够符合条件，那么，我们应该返回的下标不就应该为：arr[i].l + x - 1 吗？
			但是，我们可以发现一个问题：我们 arr[i].l + x - 1 也是有可能不在原字符串区间中的，于是，我们必须继续递归下去 
			*/
			if (arr[i].l + x - 1 > n) t = f(arr[i].l + x - 1);//递归 
			else t = arr[i].l + x - 1;//成立 
			return t;//返回 
		}
		else x -= arr[i].len;//说明 x 一定不在 arr[i].l ~ arr[i].r 区间中 
	}
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> T;
	while (T--){
		idx = 0;
		cin >> n >> q >> Q >> s;
		s = ' ' + s;
		arr[++idx] = {1,n,n};
		while (q--){
			int l,r;
			cin >> l >> r;
			arr[++idx] = {l,r,r - l + 1};
		}
		while (Q--){
			int x;
			cin >> x;
			int t = f(x);
			cout << s[t] << endl;
		}
	}
	return 0;
}
```

---

## 作者：I_am_AKed_by_NOI (赞：0)

## 题目大意

有一个字符串 $s$，以及 $c$ 次 copy 操作，$q$ 次询问，每次 copy 操作给出一个区间 $[l, r]$，将 $s[l, r]$ 这个子串拼接到原串后面构成新串 $s$，$c$ 此操作后有 $q$ 次询问，每次询问输出指定位置的字符。

## 思路分析

由于这个字符串最终会非常长，所以不能直接保存下来。

所以对于每次询问都需要向前找到它最初的位置，也就是说，每次询问找出他是从哪一段复制过来的。

找之前可以先维护前 $i$ 次操作后字符串的长度 $sum[i]$，

$sum$ 数组很好得出，每次 copy 操作时： $sum[i]=sum[i-1]+(r-l+1)$ 即可。 

这样找的过程其实就是个二分的过程，二分找到当前位置是从第几次 copy 得到的，

之后就计算出它向前的位置，重复这个过程，直到当前位置落入在输入字符串范围内。

---

## 作者：Anguei (赞：0)

## 题意

给定一个字符串 $s_0$，以及 $c$ 次操作。第 $i$ 操作都会从上次操作得到的结果串中，选择 $s_{i-1_{[l, r]}}$ 范围内的子串，复制粘贴到上次结果串的末尾，得到一个新的串 $s_i$。经历完 $c$ 次操作之后，会得到一个最终串 $s_c$。

有 $q$ 次询问，每次询问指定一个位置 $x$，询问 $s_c$ 的第 $x$ 个字符是什么。

$n \leq 2 \times 10^5$，$c \leq 40$，$q \leq 1 \times 10^4$。

## 分析

第 $i$ 次操作的极限情况，是把 $s_{i-1}$ 完整的复制粘贴一遍。于是，$c$ 次操作之后，$s_c$ 的长度可高达 $n * 2^{40}$。故暴力模拟是不可行的。

记录下每次操作的：$l$，$r$，新生成的串的左右端点 $L$，以及 $R$。那么，每次操作，都会把上一个串的第 $r$ 个位置复制到新串的 $R$ 位置，$r-1$ 复制到 $R-1$ 的位置，以此类推，$l$ 复制到 $R - (r - l) = L$ 的位置。设 $d = R - r = L - l$，那么对于这次操作新生成的每一个位置 $x$，都与 $x - d$ 的位置上的字符相同。

以样例分析。第一组样例，一共有三次操作。原始串用原色表示，后面三个生成的串分别用红绿蓝表示。

| 1 | 2 | 3 | 4 | $\color{red}{\text{5}}$ | $\color{red}{\text{6}}$ | $\color{red}{\text{7}}$ | $\color{red}{\text{8}}$ | $\color{green}{\text{9}}$ | $\color{green}{\text{10}}$ | $\color{green}{\text{11}}$ | $\color{blue}{\text{12}}$ | $\color{blue}{\text{13}}$ | $\color{blue}{\text{14}}$ | $\color{blue}{\text{15}}$ | $\color{blue}{\text{16}}$ | $\color{blue}{\text{17}}$ |
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|
| m | a | r | k | $\color{red}{\text{m}}$ | $\color{red}{\text{a}}$ | $\color{red}{\text{r}}$ | $\color{red}{\text{k}}$ | $\color{green}{\text{m}}$ |  $\color{green}{\text{a}}$ |  $\color{green}{\text{r}}$ | $\color{blue}{\text{r}}$ |  $\color{blue}{\text{k}}$ |  $\color{blue}{\text{m}}$ |  $\color{blue}{\text{a}}$ |  $\color{blue}{\text{r}}$ |  $\color{blue}{\text{k}}$ |

1. 若询问最终串的第 $10$ 个字母，发现位置 $10$ 实在第二次操作（绿色部分）生成的，这次操作的 $d = 11 - 7 = 9 - 5 = 4$，所以第 $10$ 个字符就与第 $10-4=6$ 个字符相同。
2. 继续往前推，第 $6$ 个字符是在第一次操作（红色部分）生成的，这次操作的 $d = 4$，于是它又会与第 $6-4=2$ 个字符相等。
3. 第 $2$ 个字符，是在第零次操作中生成的，即属于原始字符串。直接输出 $s_2$ 即可。

就像这样从后往前跳，无论询问的坐标多大，一定会在 $c$ 次之内跳到原始串的范围当中。故总时间复杂度 $\mathcal{O}(qc)$。

## 代码

```cpp
struct OperationInfo {
  ll l, r, L, R;
  OperationInfo() {}
  OperationInfo(ll l, ll r, ll L, ll R) : l(l), r(r), L(L), R(R) {}
};

void solution() {
  int n, c, q;
  read(n, c, q);
  std::string s;
  std::cin >> s;
  s = " " + s;
  std::vector<OperationInfo> oper(c + 1);
  oper[0] = OperationInfo(0, 0, 1, n);
  for (int i = 1; i <= c; ++i) {
    read(oper[i].l, oper[i].r);
    // 求出每次操作新生成的坐标范围
    oper[i].L = oper[i - 1].R + 1;
    oper[i].R = oper[i - 1].R + oper[i].r - oper[i].l + 1;
  }
  auto answer = [&]() {
    ll pos;
    read(pos);
    for (int i = c; i >= 1; --i) {
      if (pos >= oper[i].L) {
        ll dis = oper[i].L - oper[i].l;
        assert(dis == oper[i].R - oper[i].r);
        pos -= dis;
      }
    }
    std::cout << s[pos] << "\n";
  };
  for (int kase = 1; kase <= q; ++kase) answer();
}
```


---

## 作者：codemap (赞：0)

## 题目分析
首先发现 $1\le l,r,k\le 10^{18}$，所以直接模拟复制操作肯定会超时，于是我们考虑其他方法。

发现 $c\le40$，想到可以一次一次向前找对应的字母。

具体来说，只要 $k\gt n$，我们从前往后枚举每次复制操作，记录目前的总长度，当总长度超过 $k$ 时，将 $k$ 变为它来源的下标，这样直到 $k\le n$ 为止。

这样做的话，每次查询的最高时间复杂度为 $\frac{c(c-1)}{2}$，可以通过此题。

最后注意一下需要开 long long 即可。

## 代码
```cpp
#include<iostream>
using namespace std;
long long l[41],r[41];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    long long t,n,c,q,i,j,k,s;
    string a;
    cin>>t;
    while(t--)
    {
        cin>>n>>c>>q>>a;
        for(i=1;i<=c;i++)
            cin>>l[i]>>r[i];
        for(i=1;i<=q;i++)
       	{
            cin>>k;
            while(k>n)
            {
                s=n;
                for(j=1;j<=c;j++)
                {
                    if(s+r[j]-l[j]+1>=k)
                    {
                        k=k-s+l[j]-1;
                        break;
                    }
                    s+=r[j]-l[j]+1;
                }
            }
            cout<<a[k-1]<<"\n";
        }
    }
    return 0;
}
```


---

