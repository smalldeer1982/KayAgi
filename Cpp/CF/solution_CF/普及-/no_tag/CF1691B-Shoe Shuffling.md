# Shoe Shuffling

## 题目描述

一个班的学生想要互相换鞋子，假设这个班有 $n$ 名学生，给定一个**非递减**的序列记录每个学生鞋子的码数。你需要给出一个下标排列，使得每个学生拿到的都不是自己的鞋子，并且码数与原来的相同。如果找不到这样的下标排列，输出 $-1$ 。

定义一个下标排列由整数 $1$ 到 $n$ 组成，顺序任意。比如， $ [2,3,1,5,4] $ 是一个下标序列；$ [1,2,2] $ 不是一个下标数列，因为 $2$ 出现了两次；$ [1,3,4] $ 不是一个下标序列，因为排列的长度为 $3$ 却出现了元素 $4$。

## 说明/提示

对于第一组数据，除了 $[1, 2, 3, 4, 5]$ 外的长度为 $5$ 的下标序列都是合法的，因为每个同学之间都能穿对方的鞋子。

对于第二组数据，可以证明没有合法的下标序列。

## 样例 #1

### 输入

```
2
5
1 1 1 1 1
6
3 6 8 13 15 21```

### 输出

```
5 1 2 3 4 
-1```

# 题解

## 作者：RE_Prince (赞：9)

# CF1691B Shoe Shuffling

[link](https://www.luogu.com.cn/problem/CF1691B)

## Sol
考场上 T 飞了 qwq

题目要求每人拿到大于等于自己鞋号的鞋，且不是自己的。那么我们考虑，如果一个人有自己独特的鞋号，会发生什么？

比如下面这种情况：
```
7
1 1 1 2 3 3 3
```

显然， $2$ 只能穿 $3$ 的鞋，但是和 $2$ 交换的 $3$ 去穿谁的鞋呢？

鞋的分配会变成如下：

```
2 3 1 5 4 7 6
```

很明显，数列当中的 $4$ 不符合要求。意思是只要有人有自己独特的鞋号，比他大的人就必须和他交换，但那个比他大的人就不符合要求了。因此，我们可以推断出结论：

> 交换时，只能鞋号相同的人才能交换。

> 只要有人有自己独特的鞋号，必定不行。

但还有一个问题，鞋号相同的人如何保证每人都不会得到自己的鞋呢？

这里，我要介绍一个函数：STL的 `rotate()` 函数。

它的作用是将一个数组假设成一个环然后旋转一下。

举个例子：

```
1 2 3 4 5 -> 5 1 2 3 4
```

这样就能保证每人不拿到自己的鞋子了。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m, i, j, k;
const int N = 1e5 + 9;
int a[N], x[N];
signed main()
{
	ios::sync_with_stdio(0);
	int T;
	cin >> T;
	while (T--)
	{
		memset(x, 0, sizeof(x));
		cin >> n;
		for (i = 0; i < n; i++) cin >> a[i], x[i] = i + 1;//
		i = 0;
		int l = 0;
		bool pd = 1;
		while (i < n)
		{
			while (i < n - 1 && a[i] == a[i + 1]) i++;//统计重复的数字
			if (l == i)//如果只有一个
			{
				pd = 0;//直接跳出，输出-1
				break;
			}
			rotate(x + l, x + i, x + i + 1);//否则旋转
			l = i + 1;//记录开始
			i++;//跳过已经被算过的元素
		}
		if (!pd) cout << "-1\n";//不行
		else
		{
			for (i = 0; i < n; i++) cout << x[i] << " ";
			cout << endl;
		}
	}
	return 0;
}
```

---

## 作者：Night_sea_64 (赞：3)

[这里是题目](https://www.luogu.com.cn/problem/CF1691B)

题目中让每个人拿到的都不是自己的鞋子。那么如果看见有一个鞋码在序列中只出现了一次，说明没人跟他换，这种情况下就输出 $-1$。

如果这个鞋码在序列中出现了多次，那么这些人一定可以互相交换。可以让第一个人拿最后一个人的，后面的人都拿前一个人的。

数列本来就是非递减的。要求这个数在序列里出现的次数，可以用系统自带函数 $\operatorname{lower\text{\_}bound}$ 和 $\operatorname{upper\text{\_}bound}$ 的二分算法来完成。如果不会的可以自行百度。以下是 AC 代码：

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int a[100010],b[100010];
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        bool flag=1;//记录当前为止能不能满足要求
        for(int i=1;i<=n;i++)cin>>a[i];
        for(int i=1;i<=n;i++)
        {
            if(upper_bound(a+1,a+n+1,a[i])-lower_bound(a+1,a+n+1,a[i])<=1)//二分求个数。如果只有一个就无法满足要求。
            {
                flag=0;
                break;
            }
            else
            {
                if(a[i]!=a[i-1])b[i]=upper_bound(a+1,a+n+1,a[i])-a-1;
                else b[i]=i-1;
                //让第一个人拿最后一个和他一样的人的。
                //让后面的人拿他前面的人的。
            }
        }
        if(flag)
            for(int i=1;i<=n;i++)
                cout<<b[i]<<" ";
        else cout<<-1;
        cout<<endl;
        //不能在循环里直接输出。因为输出 -1 时可能前面已经有输出了。
    }
    return 0;
}
```

本蒟蒻的题解就到这里。祝大家 RP++！！！

---

## 作者：YangXiaopei (赞：2)

## Solution

很明显，让 $n$ 去二重循环枚举是不可能过的。

在看数据，只有 $O(nT)$ 可以过。我们就要想一个 $O(n)$ 的算法。

先看不可能的情况：

当一种鞋码只出现过一次时。那这个人就只能穿自己的鞋了，便是无解。

所以，只要每种鞋码都出现不只一次，就有解了。

在看可能的情况：

我们可以存一个 $map$ 数组，$mp_{i}$ 里存的是脚码为 $i$ 的所有人。我们再把每个人出现在这个数组的第几个，输出这个数组的下一个即可（最后一个输出第一个）。

好了，最后理一遍代码写法：

* 用 $map$ 数组存下每个脚码有的编号。

* 在存 $map$ 是存下每个人在 $map$ 的第几个。

* 遍历 $map$ 看有没有哪一种脚码只有一个。有就输出 $-1$。

* 扫一遍每个人，输出他所在的 $map$ 中他的下一个。

PS:~~代码就不放了，个人认为已经讲的挺详细了。（其实是代码有点丑）~~。

---

## 作者：Lqingyi (赞：2)

此题题目给出条件非递减序列，已经大大的降低了难度，因为鞋码相同的同学一定在序列的相邻处，那么只需要通过双指针来判断对于当前鞋码来说有多少同学与他相同。若超过两个则可以把最后一个同学的鞋给第一个然后再依次把第一个给第二个，第二个给第一个。

```cpp
#include<iostream>
using namespace std;

const int N = 1e5 + 10;

int a[N];
int t;
int main(){
	cin >> t;
	while(t--){
		int n;
		cin >> n;
		for(int i = 1; i <= n; i++){
			cin >> a[i];
		}
		
		for(int i = 1; i <= n; i++){
			int l = i,r = i;
			while(r <= n - 1 && a[r + 1] == a[i]) r++;
			a[l] = r;
			for(int j = l + 1; j <= r; j++){
				a[j] = j - 1;
			}
			i = r;
		}
		
		bool flag = false;
		for(int j = 1; j <= n; j++) {
			if(a[j] == j) flag = true;
		}
		
		if(flag) cout << "-1" << endl;
		else{
			for(int j = 1; j <= n; j++) {
				cout <<a[j] << " ";
			}
			cout << endl;
		}
			
	}
	
	
	
	
}
```


---

## 作者：donk_666 (赞：1)

#### [博客](https://www.luogu.com.cn/blog/wlt0716/#)食用更佳

##### 题目[luogu](https://www.luogu.com.cn/problem/CF1691B)   [codeforces](https://codeforces.com/problemset/problem/1691/B)
------------

CF水题

------------

思路：暴力模拟，找出每一个由相同数字组成的连续字串，可以理解为一个块，块内每个数用后面那个，最后的用第一个。若有一块只由一个数组成，直接输出 $-1$
。

题目翻译已经减少了分析“只能穿与自己尺码一样的鞋”的步骤。（分析见其它题解）

### 详见代码，配注释~~服~~食用效果更佳

```
#include<bits/stdc++.h>
using namespace std;
int t,n;
int a[100005],f[100005];
int main(){
	cin>>t;
	while(t--){
		memset(f,0,sizeof(f));//数组不清零，OI见祖宗
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		if(n==1){//特判大小为1的情况
			cout<<-1<<endl;
			continue;
		}
		int l=1;//l是这一块内第一个数的编号（初始为0）
		a[n+1]=-1;
		for(int i=1;i<=n;i++){
			if(a[i+1]==a[i]){//如果与后面相同，这个人用后面那人的鞋
				f[i]=i+1;
			}
	    	else{
				if(l==i){
					l=-2;//做上无解标记
					break;
				}
				else{
					f[i]=l;//块尾用块首
					l=i+1;//下一个为新一个块起点
				}
			}
		}
		if(l==-2){
			cout<<-1<<endl;
			continue;
		}
		for(int i=1;i<=n;i++){
			cout<<f[i]<<" ";
		}
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：Coros_Trusds (赞：1)

[更好的阅读体验](https://www.cnblogs.com/Coros-Trusds/p/16341202.html)

~~谨防东方势力入侵 $\rm Codeforces$~~

# 题目大意

求出每一个大小相同的“块”，如果有块的大小为 $1$ 则无解。

否则，我们对于每个“块”，设组成此“块”的每个元素的下标为 $[i,i+1,\cdots,i+k]$，则答案排列为 $[i+k,i,i+1,\cdots,i+k-1]$。

注意求无解和输出要分开操作。

# 代码

```cpp
#include <iostream>
#include <cstdio>
#include <climits>//need "INT_MAX","INT_MIN"
#include <cstring>//need "memset"
#include <numeric>
#include <algorithm>
#include <cmath>
#include <map>
#define enter putchar(10)
#define debug(c,que) std::cerr << #c << " = " << c << que
#define cek(c) puts(c)
#define blow(arr,st,ed,w) for(register int i = (st);i <= (ed); ++ i) std::cout << arr[i] << w;
#define speed_up() std::ios::sync_with_stdio(false),std::cin.tie(0),std::cout.tie(0)
#define mst(a,k) memset(a,k,sizeof(a))
#define stop return(0)
const int mod = 1e9 + 7;
inline int MOD(int x) {
	if(x < 0) x += mod;
	return x % mod;
}
namespace Newstd {
	inline int read() {
		int ret = 0,f = 0;char ch = getchar();
		while (!isdigit(ch)) {
			if(ch == '-') f = 1;
			ch = getchar();
		}
		while (isdigit(ch)) {
			ret = (ret << 3) + (ret << 1) + ch - 48;
			ch = getchar();
		}
		return f ? -ret : ret;
	}
	inline double double_read() {
		long long ret = 0,w = 1,aft = 0,dot = 0,num = 0;
		char ch = getchar();
		while (!isdigit(ch)) {
			if (ch == '-') w = -1;
			ch = getchar();
		}
		while (isdigit(ch) || ch == '.') {
			if (ch == '.') {
				dot = 1;
			} else if (dot == 0) {
				ret = (ret << 3) + (ret << 1) + ch - 48;
			} else {
				aft = (aft << 3) + (aft << 1) + ch - '0';
				num ++;
			}
			ch = getchar();
		}
		return (pow(0.1,num) * aft + ret) * w;
	}
	inline void write(int x) {
		if(x < 0) {
			putchar('-');
			x = -x;
		}
		if(x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
}
using namespace Newstd;
 
const int N = 1e5 + 5;
int a[N];
int n;
inline void solve() {
	mst(a,0);
	n = read();
	bool mark = true;
	for (register int i = 1;i <= n; ++ i) {
		a[i] = read();
	}
	int L = 1,R = 1;
	while (R <= n) {
		while (R + 1 <= n && a[L] == a[R + 1]) R ++;
		if (L == R) {
			puts("-1");
			return;
		}
		L = R + 1;
		R ++;
	}
	L = R = 1;
	while (R <= n) {
		while (R + 1 <= n && a[L] == a[R + 1]) R ++;
		if (L == R) {
			puts("-1");
			return;
		}
		printf("%d ",R);
		for (register int i = L;i < R; ++ i) printf("%d ",i);
		L = R + 1;
		R ++;
	}
	puts("");
}
int main(void) {
	int T = read();
	while (T --) {
		solve();
	}
	
	return 0;
}
```

---

## 作者：JXkcy (赞：0)

## 1.看题目题意
~~上回写 CF 的题没有 Unknown Error 啊……~~

题目中说要使得每个学生拿到的都不是自己的鞋子，并且码数与原来的相同。

但看这个条件就可以得到这样的推论：

**若有一码数 $ a_i $ 只出现了一次，则第 $ i $ 位同学分不到鞋子，则必定无解。**

这是后续代码中判断的条件。

然后看到加粗字体：**非递减**。

这启发了我们输出的方式：

让第 $ i $ 个人拿第 $ k $ 个（$ {\color{Red} k \ne i }  $） $ a _ {k} = a _ {i} $ 的人的鞋子。

## 2.代码逻辑

看到数据范围后，个人认为应该写个二分加快一下效率，**只求更好**。

二分可以自己写也可以用自带的 STL，这里我是用的是自带的 STL。

**区分一下两种二分函数：**

```cpp
lower_bound：在一个有序序列中进行二分查找;
返回指向第一个 大于等于 [x] 的元素的位置的迭代器。
如果不存在这样的元素，则返回尾迭代器。
lower_bound(v.begin(),v.end(),x);

upper_bound：在一个有序序列中进行二分查找;
返回指向第一个 大于 [x] 的元素的位置的迭代器。
如果不存在这样的元素，则返回尾迭代器。upper_bound(v.begin(),v.end(),x)。

时间复杂度都是 O(logN)

一句话：lower_bound找大于等于；upper_bound找大于。
```

大致思路应该是：在每输入一组数据后，挨个去找第一个比第 $ i $ 位同学的鞋码大的同学的下标，同时要判断这个鞋码是否只有这一个，可以用一个 bool 类型的变量存判断的结果，以便输出无解情况。

怎么求呢？

看这段代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int T,n,a[10]={1,2,3,4,6,6,6,6,10};
int main(){
	cout << upper_bound(a,a + 10,6) - a - 1;
	return 0;
}
```
它会输出你在 $ a $ 数组中第一个比 $ 6 $ 大的数的下标(下标为 $ 0 $ 到 $ n - 1 $)，为什么呢？

这就关系到数组的实质了，如果你直接输出这个数组名，会蹦出来一个地址。

如果你这么写：
```cpp
#include <bits/stdc++.h>
using namespace std;
int T,n,a[10]={1,2,3,4,6,6,6,6,10};
int main(){
	for(int i = 0;i < 10;i ++)cout << a[i] << " ";
	cout<<endl;
	for(int i = 0;i < 10;i ++)cout << *(a+i) << " ";
	return 0;
}
```
两行输出会一模一样。

因为这个数组名表示的是数组中第一个元素的地址，而整个数组的地址是连续的，所以两行输出会一模一样。

这样一来你就知道我要怎么求了吧。
## 3.完整代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int T,n,a[100007],ans[100007];
int main(){
	ios::sync_with_stdio(false);//快读可省略
	cin.tie(0);cout.tie(0);//同上
	cin >> T;
	while(T --){
		cin >> n;
		for(int i = 1;i <= n;i ++) cin >> a[i];
		bool fb = true;
		for(int i = 1;i <= n;i ++){
			//upper_bound找大于 lower_bound找大于等于 相减就是等于的啦
			if(upper_bound(a + 1,a + n + 1,a[i]) - lower_bound(a + 1,a + n + 1,a[i]) == 1){
				fb=0;break;
			}
			//否则去求第一个比第i位同学鞋码大的
			if(a[i] != a[i - 1])ans[i] = upper_bound(a + 1,a + n + 1,a[i]) - a - 1;
			else ans[i] = i - 1;
		}
		if(fb == false){
			cout << "-1\n";
			continue;
		}
		for(int i = 1;i <= n;i ++)cout << ans[i] << " ";
		cout << "\n";
	}
	return 0;
}
/*
  拿到的都不是自己的鞋子，并且码数与原来的相同。找不到 cout −1 。
*/
```

不知道为啥 UKE 了，在 [codeforces](https://codeforces.com/problemset/problem/1691/B) 上交了一下。

[AC 记录](https://codeforces.com/contest/1691/submission/223071935)

---

## 作者：legend_cn (赞：0)

## 题目简介
就是要求每人拿到**大于等于**自己鞋号的鞋，且不是自己的。
## 解法
我们举一个例子，当每一个人的唯一的鞋号时，怎么做。

当鞋号时这样的时：$1$ $1$  $2$ $3$ $3$

鞋号是 $2$ 同学这能选择穿鞋号是 $3$ 的鞋，所以鞋号是 $3$ 的同学就需要换一个鞋。

这样就会：
$1$ 号穿 $2$ 号的鞋，
$2$ 号穿 $3$ 号的鞋，
$3$ 号穿 $1$ 号的鞋，
$4$ 号穿 $5$ 号的鞋，
$5$ 号穿 $4$ 号的鞋，
$6$ 号穿 $7$ 号的鞋，
$7$ 号穿 $6$ 号的鞋。

但是这样不符合条件。每个人只要有人有自己独特的鞋号，比他大的人就必须和他交换，但那个比他大的人就不符合要求了。所以**交换时，只能鞋号相同的人才能交换。只要有人有自己独特的鞋号，必定不行。**

还需要保证鞋号相同的人每人都不会得到自己的鞋，所以需要使用 `rotate()` 函数。它会把这个数组看成一个环，转一下，在变成数组。

比如：$1$ $2$ $3$ 会变成 $3$ $1$ $2$

这样就能保证每人不会拿到他们本人的鞋子了。

## AC 代码 
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 9;
int a[N], id[N];
signed main()
{
	int T;
	cin>>T;
	while (T--)
	{
		int n;
		cin>>n;
		for(int i=0;i<n;i++)
		{
			cin>>a[i];
			id[i]=i+1;
		}
		int i=0;
		int len=0;
		bool im=1;
		while(i<n)
		{
			while(i<n-1&&a[i]==a[i+1])
				i++;
			if(len==i)
			{
				im=0;
				break;
			}
			rotate(id+len,id+i,id+i+1);
			len=++i;
		}
		if(!im)
			cout<<"-1\n";
		else
		{
			for(int i=0;i<n;i++)
				cout<<id[i]<<" ";
			cout<<endl;
		}
	}
	return 0;
}
```


---

## 作者：yanhao40340 (赞：0)

### 题意
题面已经说得十分清楚了。有点长，耐心看完即可。
### 分析
#### 思路
首先需要明确，每个人都只能穿与自己鞋码相同的鞋子。

证明：如果结论不对，那么不妨设 $x$ 穿了 $y$ 的鞋子，且 $s_x<s_y$，那么 $y$ 就只能穿比 $y$ 鞋码更大的人的鞋子。以此类推，鞋码最大的人就没有鞋子穿了，矛盾。所以结论正确。
#### 无解情况
如果有一个人的鞋码是独一无二的，那么根据前文中的结论，并且他没有相同鞋码的鞋子穿，输出 $-1$。
#### 实现
推荐用 $\texttt{rotate}$ 函数实现，赛时调了很久，实现方法：
```cpp
rotate(first_element,n_first,last_element)
```
当然也可以用数组或 $\texttt{vector}$ 实现。

~~我的实现有种大炮轰蚊子的既视感。~~
### 代码
```cpp
#include <iostream>
#include <map>
#include <vector>
using namespace std;
const int maxn=100010;
int a[maxn],ans[maxn];
map<int,vector<int> > mp;
int main(){
    int t,n;scanf("%d",&t);
    while (t--){
        scanf("%d",&n);mp.clear();//记得清空
        for (int i=1;i<=n;++i)
            scanf("%d",&a[i]),mp[a[i]].push_back(i);
        for (auto it:mp){
            auto i=it.second;
            if (i.size()==1){puts("-1");goto skip;}//判无解
            ans[i[0]]=i[i.size()-1];
            for (int j=1;j<i.size();++j) ans[i[j]]=i[j-1];//轮换
        }
        for (int i=1;i<=n;++i) printf("%d ",ans[i]);
        putchar('\n');skip:;
    }
    return 0;
}
```

---

## 作者：yaolibo (赞：0)

[题目链接](https://www.luogu.com.cn/problem/CF1691B)

## 题意解释：
给定 $n$ 个人的原本的鞋子码数，需要构造一个拿取鞋子的错排（每个人不拿到自己的鞋子），使得每个人目前得到的鞋子码数不小于自己鞋子的码数。
## 思路 & 方法：

以下提供两个我本人打比赛时的思路，两种思路都可以最终推向一个结论，各位可以选择性的参考。

------------

对于一个编号为 $i$ 的人，他原本的鞋子码数为 $a_i$，

那我们就需要找到一个编号为 $j$ 的人使得 $a_j\ge a_i$。

上述条件对于每个人都要成立，这个问题看似不好解决，但我们可以顺着思路往下想。

### 思路一：

显然，我们可以很容易想到一个结论：**拥有最大鞋码的人一定要拿和自己相同鞋码的鞋。** 因为根本就没有比他穿的鞋码还大的鞋了！

我们设最大鞋码为 $d_1$。

那么对于 $k$ 个鞋码为 $d_1$ 的人，他们需要轮换着使用别人的鞋子，此刻鞋码为 $d_1$ 的鞋子就已经被拿完了。

那么我们接着设次大鞋码为 $d_2$。

此时最大鞋码已经被拿光了！次大鞋码就变成了最大鞋码，那么和上面一样的思路，也只能拿与自己鞋码相同的鞋子。

（换种说法，那就是此时已经没有鞋的鞋码比 $d_2$ 大了）

### 思路二：

我们可以这样问自己：

把 $j$ 的鞋子给 $i$ 穿，那 $j$ 穿谁的鞋子？

假设 $j$ 穿 $k$ 的鞋子，下面我们假设一下：

如果 $a_k>a_j$，那么顺着下去，$k$ 又穿谁的鞋子？

很明显，这么下去，那么其中一个拥有最大鞋码的人的鞋子就会被一个鞋码小于他的人穿走，那么就肯定会有一个最大鞋码的人没有合适的鞋子穿了。

我们来举个例子：

 $n$ 个人的鞋码分别为 $a = \{1,1,5,5,5\}$。    
 
对于两位鞋码为 $1$ 的人来说：
 
+ 一种方法是则两位鞋码为 $1$ 的人可以互换鞋子穿。

+ 当然也可以第一个 $1$ 去穿第二个 $1$，然后第二个 $1$ 去穿第一个 $5$。此时的每个人拿到鞋子码数的数组即为 $b = \{1,5,-,-,-\}$。那我们很容易可以知道，因为有一个 $5$ 被一个 $1$ 给穿了，所以肯定有一个 $5$ 没有鞋子可以穿了。所以这样子是无法构造出合法答案的。所以只能是 $a_i=a_j=a_k$。

------------

通过以上两个思路，我们可以推出一个简单的结论，即：**每个人只会拿与他相同鞋码的人的鞋**。

那么到这里代码就很好写了，我们只需要各自求出每个鞋码出现的人有哪些，然后将他们轮换错排即可。

那么显然，当某个鞋码的人只有一人，那么他无法和别人换鞋，那么就无解。

补充：我的轮换方法是在鞋码相同的人中，第 $j$ 个人去穿第 $j+1$ 个人的鞋，最后一个人去穿第 $1$ 个人的鞋。

## Code：
```cpp
#include <bits/stdc++.h>

#define LL long long

using namespace std;

inline int Read() {
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9') {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        x = (x << 1) + (x << 3) + (c ^ '0');
        c = getchar();
    }
    return x * f;
}

const int N = 1e5 + 10;

vector<pair<int, int> > v;

pair<int, int> p;

int t, n, tot, i, j;

int a[N];

int main() {
    t = Read();
    while (t--) {
        v.clear();
        memset(a, 0, sizeof a);
        n = Read();
        for (i = 1; i <= n; i++) a[i] = Read();
        sort(a + 1, a + 1 + n);
        for (i = tot = 1; i <= n; i++) {
            if (a[i] != a[i + 1]) {
                if (tot == 1) break;
                v.push_back(make_pair(i - tot + 1, i));
                tot = 1;
            }
            else tot++;
        }
        if (i <= n) printf("-1\n");
        else {
            for (i = 0; i < v.size(); i++) {
                for (j = v[i].first; j < v[i].second; j++)
                    printf("%d ", j + 1);
                printf("%d ", v[i].first);
            }
            printf("\n");
        }
    }
    return 0;
}
```

---

