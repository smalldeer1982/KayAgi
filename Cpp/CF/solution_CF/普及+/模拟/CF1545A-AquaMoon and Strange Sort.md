# AquaMoon and Strange Sort

## 题目描述

AquaMoon has $ n $ friends. They stand in a row from left to right, and the $ i $ -th friend from the left wears a T-shirt with a number $ a_i $ written on it. Each friend has a direction (left or right). In the beginning, the direction of each friend is right.

AquaMoon can make some operations on friends. On each operation, AquaMoon can choose two adjacent friends and swap their positions. After each operation, the direction of both chosen friends will also be flipped: left to right and vice versa.

AquaMoon hopes that after some operations, the numbers written on the T-shirt of $ n $ friends in the row, read from left to right, become non-decreasing. Also she wants, that all friends will have a direction of right at the end. Please find if it is possible.

## 说明/提示

The possible list of operations in the first test case:

1. Swap $ a_1 $ and $ a_2 $ . The resulting sequence is $ 3, 4, 2, 5 $ . The directions are: left, left, right, right.
2. Swap $ a_2 $ and $ a_3 $ . The resulting sequence is $ 3, 2, 4, 5 $ . The directions are: left, left, right, right.
3. Swap $ a_1 $ and $ a_2 $ . The resulting sequence is $ 2, 3, 4, 5 $ . The directions are: right, right, right, right.

## 样例 #1

### 输入

```
3
4
4 3 2 5
4
3 3 2 2
5
1 2 3 5 4```

### 输出

```
YES
YES
NO```

# 题解

## 作者：云浅知处 (赞：5)

遇到这种交换又排序的题，直接考虑排序前后一个数的位置变化你就赢一半了。

对于这道题，由于每个人交换一次就会改变一次方向，而初始和最后方向需要相同，所以每个人初始和最后的位置之间相差的距离必然为偶数。

如果没有重复元素那当然排个序直接瞎判断一下就行了；然而有重复元素就有点难搞。

注意到一个元素如果移动了偶数次那么它在数组中的位置的奇偶性必然不会改变，因此我们建两个桶：用 $f_{i,0}$ 表示 $i$ 这个值在原序列偶数位上出现的次数，$g_{i,0}$ 表示 $i$ 这个值在原序列奇数位上出现的次数。$f_{i,1}$ 表示 $i$ 这个值在排序后的新序列偶数位上出现次数，$g_{i,1}$ 类似。

那么稍加思考可以发现，只需要判断是否对任意 $1\le i\le V$ 有 $f_{i,0}=f_{i,1},g_{i,0}=g_{i,1}$ 即可。其中 $V$ 为值域。

其中的道理不难讲：若存在符合条件的移动方式，那么一个元素如果原来在奇数位上，最后也一定在奇数位上，这表明对每个值 $i$，它在奇数位上的出现次数是不会改变的；偶数同理。必要性是显然的。

于是只需要排个序就行了。

时间复杂度 $O(n\log n)$，但由于值域很小其实可以用计数排序做到 $O(n)$，不过没必要。

```cpp
#include<bits/stdc++.h>

#define int long long

using namespace std;

int read(){
	int x=0,f=1;char ch=getchar();
	for(;(!(ch>='0'&&ch<='9'));ch=getchar())if(ch=='-')f=-1;
	for(;(ch>='0'&&ch<='9');ch=getchar())x=(x<<1)+(x<<3)+(ch-'0');
	return x*f;
}

const int MN=1e5+5;
int n,a[MN],f[MN],g[MN];

signed main(void){
	
	int tt=read();while(tt--){
		n=read();bool ans=1;
		for(int i=1;i<=n;i++){
			a[i]=read();
			f[a[i]]+=(i%2==0),g[a[i]]+=(i%2==1);
		}
		sort(a+1,a+n+1);
		for(int i=1;i<=n;i++)f[a[i]]-=(i%2==0),g[a[i]]-=(i%2==1);
		for(int i=1;i<=n;i++)if(f[a[i]]!=0||g[a[i]]!=0)ans=0;
		puts(ans?"YES":"NO");
		for(int i=1;i<=n;i++)f[a[i]]=g[a[i]]=0;
	}

	return 0;
}
```

---

## 作者：JCLinux (赞：4)

### 题意关键点：

1. 初始全部向右

2. 按 $a_i$ 从小到大的顺序排序

3. 只能移动**相邻**的的两个人

4. 每次移动，方向改变一次

### 思路过程：

看到相邻又有排序，我第一反应是冒泡排序，但一看数据范围和题目要求，显然不对，切换思路。

所有人开始时都向右，最终也都向右（假设能办到），每移动一次，面向的方向改变一次，那么要满足要求，显然这个人要经过偶数次移动，从**原位置**移动到**排序之后的位置**。

最直接的感觉就是看看某个数原来的位置和后来的位置之差的绝对值是不是偶数。

那么，这么想对不对呢。

是对的：

先假设直接往目标位置移动，那么移动次数就是 abs(初始位置 - 排序后位置) ，假设中间经过周折，那么向左多走的次数**等于**向右多走的次数，在位置绝对值上加了个偶数，对原有的奇偶性无影响，因此可以用坐标奇偶来判断。

问题又来了，怎么判断：

既然走偶数步，那么原来位置是奇数，走完后**还是**奇数，偶数亦然。

所以，对于一个数，统计有几次是在奇数位置上，有几次在偶数位置上，排序后再统计一次，比较排序前后奇数位置数量和偶数位置数量是否对应相等即可。相等就是能实现，不相等就是不能实现。

因为某个数的个数不会变，因此只需要统计奇数（偶数）即可。

### 上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int inital[100005];
int sorted[100005];
int arr[100005];
int n;
int main(){
	int t;cin >>t;
	while(t--){
		cin >>n;
		int mmax=0;
		int mmin=100005;
		for(int i=1;i<=n;i++){
			cin >>arr[i];
			mmax=max(mmax,arr[i]);
			mmin=min(mmin,arr[i]);
		}
		for(int i=mmin;i<=mmax;i++)inital[i]=sorted[i]=0;
		for(int i=1;i<=n;i++) {
			if(i%2){
				inital[arr[i]]++;
			}
		}
		sort(arr+1,arr+1+n);
		for(int i=1;i<=n;i++){
			if(i%2){
				sorted[arr[i]]++;
			}
		}
		bool flag=1;
		for(int i=mmin;i<=mmax;i++){
			if(inital[i]!=sorted[i]){
				flag=0;
				break;
			}
		}
		if(flag)cout <<"YES"<<endl;
		else cout <<"NO"<<endl;
	}
}
```


---

## 作者：FutaRimeWoawaSete (赞：2)

打的时候本来差点就正解了，结果自己打错加上去 WA 掉了没发现，听别人说了一个错解也没想就直接换上去过了 pretest 过后以为就没事了……以后还是要先思考一下再动手啊/tuu   


转化的有点复杂。           

首先我们可以树状数组 $O(n \log n)$ 求一个数前面有多少个数比它大记为 $x_i$ ，以及后面有多少个数比它小记为 $y_i$，如果所有数都保证互不相同那么就看所有的 $x_i + y_i$ 是不是偶数就好了。               

但是由于有相同所以我们考虑相同的数该怎么办。我们把相同的数的 $x_i + y_i$ 模 $2$ 的值按它们原来在序列中的顺序排列，那么现在得到了若干个 $01$ 串，我们只需要考虑能不能把每个 $01$ 串变成全是 $0$ 的串就好了。         

考虑我们的交换操作，其实也就只能把挨在一起的 $11$ 或 $00$ 变成 $00$ 或 $11$ ，那么如果我们要匹配两个 $1$ 把它们都消掉，是不是中间得全是偶数个 $0$ ，则可以得到两个 $1$ 的下标奇偶性互异。          

我们把奇下标看成左括号，偶下标看成右括号，那么这就是一个括号匹配问题了，对于每个 $01$ 串做一个括号匹配就好了，总的时间复杂度 $O(n \log n)$ 。           

```cpp
#include "bits/stdc++.h"
using namespace std;
const int Len = 1e5 + 5;
int n,m,c[Len],a[Len],sum[Len],maxa,cnt[Len][2],Cnt[Len];
//vector<int> v[Len];
int lowbit(int x){return x & (-x);}
void add(int x,int Add)
{
	while(x <= maxa) 
	{ 
		c[x] += Add;
		x += lowbit(x);
	}
}
int query(int x)
{
	int res = 0;
	while(x) 
	{
		res += c[x];
		x -= lowbit(x);
	}
	return res;
}
int main()
{
	int t;scanf("%d",&t);
	while(t --)
	{
		maxa = 0;
		scanf("%d",&n);
		//memset(Cnt , 0 , sizeof Cnt);
		for(int i = 1 ; i <= n ; i ++) 
		{
			scanf("%d",&a[i]);
			maxa = max(maxa , a[i]);
			cnt[a[i]][0] = cnt[a[i]][1] = 0;
			//if(n >= 1000) Cnt[a[i]] ++;
			//if(n >= 1000) if(Cnt[a[i]] >= 2) puts("124182r9qywdiaschud");
			sum[i] = 0;
		}
		for(int i = 0 ; i <= maxa ; i ++) c[i] = 0;
		for(int i = 1 ; i <= n ; i ++)
		{
			sum[i] += i - 1 - query(a[i]);
			//printf("%d %d\n",i,sum[i]);
			add(a[i] , 1);
		}
		for(int i = 1 ; i <= maxa ; i ++) c[i] = 0;
		bool flag = true;
		for(int i = n ; i >= 1 ; i --)
		{
			sum[i] += query(a[i] - 1);
			//printf("%d %d\n",i,sum[i]);
			sum[i] %= 2;
			//v[a[i]].push_back(sum[i]);
			add(a[i] , 1);
		}
		/*for(int i = 1 ; i <= maxa ; i ++) 
		{
			if(v[i].size() != 0) 
			{
				printf("%d:\n",i);
				for(int j = 0 ; j < v[i].size() ; j ++) printf("%d ",v[i][j]);
				puts(""); 
			}
		}*/
		for(int i = 1 ; i <= n ; i ++) 
		{
			if(sum[i]) 
			{
				if(cnt[a[i]][(i % 2) ^ 1]) cnt[a[i]][(i % 2) ^ 1] --;
				else cnt[a[i]][(i % 2)] ++;
			}
		}
		for(int i = 1 ; i <= n ; i ++)
		{
			if(cnt[a[i]][0] || cnt[a[i]][1]) 
			{
				puts("NO");
				flag = false;
				break;
			}
		}
		if(flag) puts("YES");
	}
	return 0;
}
```

---

## 作者：Acfboy (赞：2)

纪念我的第一场 Div.1 $\to$ A FST 且 B pretest 都没过，一夜回到 expert。

题目要求一个数要被交换偶数次，意味着相对原来的位置移动的距离是偶数次。  
然后赛场上的我是这样想的，如果每一个能和目标位置相匹配就行了，所以作个差，然后若不行的交换一下就改变奇偶性，所以要有偶数个在奇数位就行了。**改变个锤子！** 你把两个奇偶性相同位置的进行交换根就啥也没有改变吧！

事实上，移动距离是偶数意味着每个奇偶性相同的位置都是可以到达的，那么只要比较一个数字在目标状态和原始状态的奇数位置个数和偶数位置个数是否相同就行了。

代码就不必了。

---

## 作者：Loser_Syx (赞：1)

我们考虑如果走两步的情况，那么是先变成朝左再变成朝右，那么朝向是不变的，由此可以得出当 $i$ 走了偶数步时，朝向不会改变。

再来考虑如果我先向左走了一步，又向右走一步的情况，此时总步数为 $2$，朝向不会改变，还是在原位上，并不会对答案产生影响。

于是我们可以考虑对 $a$ 排序，记排序后的数组为 $b$，我们对于每个 $i$，求出 $a_i$ 在 $b$ 中的位置，两位置的距离便是走的步数。

但是发现 $a_i$ 中同一个数会出现多次，但是我走之后的朝向仅是对模 $2$ 取余后的答案相关，所以我们直接统计每个 $a_i$ 中 $i$ 为奇偶分别多少次，再用排序后的比对即可。

```cpp
int a[101010], cnt[101010][2], n, t;
signed main() {
	read(t);
	while (t--) {
		read(n);
		for (int i=0;i<=1e5;++i) cnt[i][0]=cnt[i][1]=0;
		for (int i=1;i<=n;++i) cnt[a[i]=read()][i%2]++;
		sort(a+1,a+1+n);
		for (int i=1;i<=n;++i) cnt[a[i]][i%2]--;
		int flg=0;
		for (int i=0;i<=1e5;++i) if (cnt[i][0] || cnt[i][1]) flg=1;
		puts(flg?"NO":"YES");
	}
	return 0;
}
```

---

## 作者：Patricky (赞：1)

看了一圈，没有该做法。

顺便
~~水一篇题解~~
补充一个十分好用但相当冷门的 STL 系列 -- std::valarray 的一小部分。

## 题意

序列 $\{A\}$ 中的每一个元素都为 $(A_i, 0)$。

你可多次选择相邻两元素 $A_{(i, i + 1)}$ 使其变为 $(A_{i + 1}, s_{i + 1}\oplus1), (A_i, s_i\oplus1)$。问经过若干次操作后能否使得第一维不递减、第二维全为 $0$。

## 解答

要满足后一个条件，这说明排序前后的位置奇偶性必相同。

因此直接 **把两种位置上的数拎出来排序再插回去** 看看是否有序即可。

## 语法/逐行详解

### Python
在 Python 中，要完成该功能其实是十分简便的。
因为 Python 中有个非常好用的 **切片功能**[^1]：

[^1]: https://docs.python.org/3/whatsnew/2.3.html?highlight=extended%20slices#extended-slices

```py
for tests in range( int(input()) ):
    n, s = input(), [int(_) for _ in input().split()]
    s[0::2] = sorted(s[0::2])
    s[1::2] = sorted(s[1::2])
    print("YES" if s == sorted(s) else "NO")
```

### $C$++
那么在 $C$++ 中，也有类似的语法糖吗？

很遗憾，就操作符来说并没有。
但从语义上来讲，确实有一个
[`std::slice`](https://en.cppreference.com/w/cpp/numeric/valarray/slice)。

这个切片相当强大的地方在于可以适配 `std::valarray`：
**可以通过 `operator[]` 来直接赋值！** 那么：

1.「把东西拎出来」:

  ```cpp
  slice l{0, (n + 1) / 2, 2}, r{1, n / 2, 2};
  valarray o = a[l], e = a[r];
  ```

2.「并将他们排序」。 值得说明的是，`std::valarray` 没有 `.begin()` 这样的第二代器，但依然可以 `std::begin(a)` 这样来使用，具体而言：

  ```cpp
  sort(begin(o), end(o));
  sort(begin(e), end(e));
  ```
  

3.「插回去」。再次调用 `operator[]`：

  ```cpp
  a[l] = o, a[r] = e;
  ```

4.「判有序」。`std::is_sorted` 默认判不降，如果要判不升则可追加 `std::greater` 或其他比较器。

  ```cpp
  puts(is_sorted(begin(a), end(a)) ? "YES" : "NO");
  ```

这样，我们就解决了问题。

## 后记
~~发牢骚环节~~

实际上 `std::valarray` 
相当好用的一点其实是可以相当简洁地对每个元素都 `std::apply` 一个操作。
但常数较大，做了解即可。
笔者也十分期待在不远的将来能够看到更高效的实现。

---

## 作者：KSToki (赞：1)

虽然比较简单，但确实是本场最容易 FST 的题。
# 题目大意
给定一个长度为 $n$ 的数组 $a$，问是否能对每个数进行偶数次与相邻数交换的操作（可以为 $0$），使 $a$ 单调不降。
# 题目分析
对于任意一个数，它交换次数的奇偶性至于初末位置距离的奇偶性有关，与其它数无关，因为如果其它数来干扰，那必然换走后又会换回来。这样，记录每个数在奇数位置和偶数位置的数量，将 $a$ 排序依次判断是否还剩余对应数对应的奇偶位置即可。

因为这玩意使多测，需要每次将 $cnt$ 数组清空。由于 $a_i$ 可以大于 $n$，按以往的习惯从 $1$ 扫到 $n$ 就会导致 FST。这就是为什么这题没有去限制 $\sum n$ 而是把 $T$ 放的很小，就是用来你清空整个 $cnt$ 的。当然其实可以更据 $a$ 去清空，最后使 $\sum n$ 的，但是没有必要。
# 代码
```cpp
#include<bits/stdc++.h>
#define R register
#define I inline
#define ll long long
#define ull unsigned long long
#define db double
using namespace std;
#define pii pair<int,int>
#define mp(x,y) make_pair(x,y)
#define piii pair<pair<int,int>,int>
#define mp3(x,y,z) make_pair(make_pair(x,y),z)
#define fi first.first
#define se first.second
#define th second
#define putint(x) printf("%d\n",x)
#define putll(x) printf("%lld\n",x)
#define putull(x) printf("%llu\n",x)
#define lowbit(x) ((x)&(-(x)))
#define inf (1e9)
#define INF (1e18)
#define eps (1e-8)
I int read()
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
int T,n,a[100001],cnt[100001][2];
int main()
{
	T=read();
	while(T--)
	{
		n=read();
		memset(cnt,0,sizeof(cnt));
		for(R int i=1;i<=n;++i)
		{
			a[i]=read();
			++cnt[a[i]][i&1];
		}
		sort(a+1,a+n+1);
		for(R int i=1;i<=n;++i)
		{
			if(!cnt[a[i]][i&1])
			{
				puts("NO");
				goto over;
			}
			--cnt[a[i]][i&1];
		}
		puts("YES");
		over:;
	}
	return 0;
}
```


---

