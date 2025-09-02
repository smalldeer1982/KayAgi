# [USACO11DEC] Cow Photography G/S

## 题目描述

今天的奶牛们特别调皮！Farmer John 想做的只是给排成一排的奶牛拍照，但是在他拍下照片之前，奶牛们一直在移动。

具体地说，FJ 有 $N$ 头奶牛（$1 \leq N \leq 20\,000$），每头奶牛都有一个唯一确定的编号。FJ 想要以一个特定的顺序拍下一张奶牛排成一排的照片，这个顺序用数组 $A[1 \ldots N]$ 表示，其中 $A[i]$ 代表排在 $i$ 位置的奶牛的编号。

他按照这样的顺序将奶牛们排列好，但在他按下快门之前，有些奶牛（可能是零头或任意多头奶牛，位置也不一定连续）将移到一个新的位置。更准确地说，一些奶牛离开队列，剩下的奶牛靠拢，这些离开的奶牛再将自己重新插入到队列中的任意位置（不一定是他们之前的位置）。FJ 感到非常沮丧，他再次按照 $A$ 数组的顺序重新安排了队列。但在他再次按下快门之前，又有一些奶牛移动到了新的位置。

就这样，FJ 拍了五张照片。给出每张照片拍摄的内容（即 FJ 按下快门时奶牛的顺序），请你尝试推算出 FJ 最初为奶牛们排的顺序（即 $A$ 数组）。由于可能有奶牛移动，照片显示的顺序与原来的顺序可能有所不同。但是，一头奶牛最多只会移动一次：即如果一头奶牛在拍其中一张照片时移动了，它在拍其他四张照片的时候都不会移动。当然，由于其他奶牛也在移动，它在不同照片中的顺序并不一定相同。

## 样例 #1

### 输入

```
5 
10 
20 
30 
40 
50 
20 
10 
30 
40 
50 
30 
10 
20 
40 
50 
40 
10 
20 
30 
50 
50 
10 
20 
30 
40 
```

### 输出

```
10 
20 
30 
40 
50 
```

# 题解

## 作者：winmt (赞：11)

我又来发第一个题解辣～**【以下代码省略头文件】**

本题要考虑**相对位置**而不是绝对位置。。。其实很容易想到：如果5张照片中有**大于或等于3张**照片里牛A在牛B的前面，那么开始序列中牛A一定在牛B之前。这样我们就很容易得到了下面的代码：



```cpp
int n;
int p,ans[20005];
map<int,int>r[10];
bool cmp(int x,int y)
{
    int f=0;
    for(int i=1;i<=5;i++)
    {
        if(r[i][x]<r[i][y])f++;
    }
    return f>=3;
}
int main()
{
    cin>>n;
    for(int k=1;k<=5;k++)
    {
        for(int i=1;i<=n;i++)
        {
            cin>>p;
            ans[i]=p;
            r[k][p]=i;
        }
    }
    sort(ans+1,ans+n+1,cmp);
    for(int i=1;i<=n;i++)cout<<ans[i]<<endl; 
    return 0;
}
```
这个代码在USACO官网提交是AC的，USACO标程也差不多这样，但是在洛谷上只能拿80分，TLE后两个大数据，这是为什么呢？我也在这里卡了很久，不知其为啥TLE。**（插叙：于是我傻逼的与kkk争论了起来，kkk说是STL-sort常数大，说改成手写版就AC了～这是有道理的，但是我有更好的办法，只需改一点点2333，最终还比kkk总共快500ms左右，想知道的继续看下去！）**其实这段代码本身就是超时的，USACO开了O2所以能过。你可能会说这程序sort是nlogn，所以复杂度就是O(nlogn)，可以过啊～但是别忘了map是很慢的，map速度是logn，其中n是节点个数。我们可以精确计算下上面代码的时间复杂度：5\*nlogn\*2\*logn=10\*n\*(logn)^2，n取200000，所以算一下就知道大约是578000000，这还只是算了sort的cmp函数里的复杂度啊就早爆了！所以立马就得到用map不行，那么秒想到用**哈希**啊！（注意要解决哈希冲突）很容易得到了以下代码：


```cpp
int n;
int p,ans[20005];
vector<pair<int,int> >r[10][9975];
bool cmp(int x,int y)
{
    int f=0;
    for(int i=1;i<=5;i++)
    {
        int num1=0,num2=0;
        int kkk1=x%9973,kkk2=y%9973;
        for(int j=0;j<r[i][kkk1].size();j++)
        {
            if(r[i][kkk1][j].first==x)num1=r[i][kkk1][j].second;
        }
        for(int j=0;j<r[i][kkk2].size();j++)
        {
            if(r[i][kkk2][j].first==y)num2=r[i][kkk2][j].second;
        }
        if(num1<num2)f++;
    }
    return f>=3;
}
int main()
{
    cin>>n;
    for(int k=1;k<=5;k++)
    {
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&p);
            ans[i]=p;
            r[k][p%9973].push_back(make_pair(p,i));
        }
    }
    sort(ans+1,ans+n+1,cmp);
    for(int i=1;i<=n;i++)printf("%d\n",ans[i]);
    return 0;
}
```
虽然长了一些，但相比kkk的方法修改幅度小很多。我们再算下时间复杂度：忽略常数是5\*nlogn，n取200000，算出来得：17000000，显然之虽然仅是STL-sort的cmp函数内时间复杂度，但是就算加上其他的复杂度也不会有问题嘚～所以这题就轻松搞定啦！23333
这也告诉我们C++党：**不能依赖STL，特别是map之类狂慢的**。。。也一定要算算时间复杂度，不能盲目地觉得AC就提交了～


---

## 作者：swiftc (赞：6)

 我们可以发现，如果一头牛在三张照片中在另一头牛的前面，那么它在原生序列中就在另一头牛的前面，__因为一头牛只有一次机会在一张照片中改变自己和另一头牛的相对位置，在下一张照片中就必须要回去__。

所以代码就很好写了,我们用```map```记录每头牛在每一张照片中的位置，然后给任意一张照片排序，比较的时候就按上文的方法就可以了:

```cpp
#include<bits/stdc++.h>
#include<tr1/unordered_map>
using namespace std;
tr1::unordered_map<int,int>ma[6];//O(1)复杂度的map
bool cmp(int x,int y){
	int num=0;
	for(int i=1;i<=5;i++){
		if(ma[i][x]<ma[i][y])num++;
	}
	return num>=3;
}
int a[20001];
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=5;i++)
	for(int j=1;j<=n;j++){
		int x;
		scanf("%d",&x);
		a[j]=x;
		ma[i][x]=j;
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++){
		printf("%d\n",a[i]);
	}
	return 0;
}
```


---

## 作者：Andysun06 (赞：3)

这一题的代码实现其实很简单，主要是理解吧，用一个优化的map（这个要独自写一个头文件，万能头里没有……）然后排序，按照出现的次数排序，这里为什么是大于等于$3$就能确定呢？下面我就来说一下：

我们先看样例：

10 20 30 40 50 

20 10 30 40 50 

30 10 20 40 50 

40 10 20 30 50 

50 10 20 30 40 

最后的输出是

10 20 30 40 50

由于对于两个奶牛来说，如果一个奶牛曾经在另一个奶牛前面$3$次及以上的话，那么他一定就在他前面，因为每次只会有一个奶牛动，一共有5次，这两头奶牛一共能够动$2$次，就算第一次后面的奶牛跑到前面的奶牛前面，第二次前面的奶牛跑到后面的奶牛后面，也就是在$2$张照片中在他后面，但是其他$3$张都是在他前面，所以我们将可能有误的$2$张去除掉，他对答案没有价值。然后就很简单了。

这里说一下：对于其他三张而言，即使有奶牛的位置会变，但是他们的前后顺序不会变。

具体细节再次看代码：
```cpp
#include<bits/stdc++.h>
#include<tr1/unordered_map>//不要忘了加上这个。
using namespace std;
int n,x,a[20010];
tr1::unordered_map<int,long long>ma[6];//这是一种线性的map。所以更快一点。
bool cmp(int x,int y){//判断前后。
    int ans=0;
    for(register int i=1;i<=5;++i)
        if(ma[i][x]<ma[i][y])
            ++ans;//如果在他前面就+1。
    return ans>=3;//返回是否有3。
}
int main(){
    cin>>n;
    for(register int i=1;i<=5;++i)
        for(register int j=1;j<=n;++j){
            cin>>x;
            a[j]=x;
            ma[i][x]=j;//存下这一次的位置。
        }
    sort(a+1,a+1+n,cmp);//排序（不得不说sort是真的好用）
    for(int i=1;i<=n;i++) cout<<a[i]<<endl;//输出。
    return 0;//完结撒花，管理求过，QWQ
}
```

## 莫抄袭，没了AC记录，空悲切！

---

## 作者：ωαηg (赞：2)

**Map？哈希？这题需要那么麻烦吗？离散化一下就好了呀！复杂度标准$O(n\ log \ n)$，没有附加产品。**

----

解题思路@ [winmt](https://www.luogu.org/user/16817) 大佬应该已经讲得很清楚了，但是我还是要重申一遍，加入了我自己的一些理解。 

**如果在至少三个序列中能保证存在奶牛$A$排在奶牛$B$之前，那么就可以说明在原序列中奶牛$A$排在奶牛$B$之前。**

一个序列并不能说明，因为A可能是从后面跑上来的，B也可能是从前面跑下去的；两个序列同样不能说明，因为可能在一个序列中A是从后面跑上来的，而在另一个序列中B是从前面跑下去的。但是三个序列就可以说明了。

**问：是否可能存在虽然不能保证存在三个序列，但是能够通过别的序列的情况推理得出$A$在$B$之前？**

**答：不可能。因为每一次排错的奶牛数量没有限制。因此一只奶牛的排错只会对和自己有关的相对顺序产生影响，而无法对其他奶牛产生影响。因此不存在推理这种操作。**

----

我们只要对输入的数据进行一次sort，魔改cmp函数，将其判断大小的依据改为是否存在至少三个序列满足$x$在$y$之前即可。

----

### 代码

实在不明白为什么会出现Map和哈希这种操作。。。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
//<fastIO>
inline int read(){int sum=0,fushu=1;char c=getchar();while(!isdigit(c)){if(c=='-') fushu=-fushu;c=getchar();}while(isdigit(c)){sum=sum*10+(c^48);c=getchar();}return sum*fushu;}
void write(int x){if(x<0) putchar('-'),x=-x;if(x>=10) write(x/10);putchar(x%10+48);}
inline void writeln(int x){write(x);putchar('\n');}
//</fastIO>
int const maxn=20005;
int n,b[maxn],ans[maxn],pos[maxn][6],num[6][maxn];
inline bool cmp(int x,int y){
	int cnt=0;
	for(int i=1;i<=5;i++)
	  if(pos[x][i]<pos[y][i]) cnt++;
	return cnt>=3;
}
signed main(){
	n=read();
	for(int i=1;i<=5;i++)
	  for(int j=1;j<=n;j++)
	    num[i][j]=read();
	for(int i=1;i<=n;i++)
	  b[i]=num[1][i];
	sort(b+1,b+n+1);
	//每头奶牛编号唯一，所以无需去重 
	for(int i=1;i<=5;i++)
	  for(int j=1;j<=n;j++){
	  	  num[i][j]=lower_bound(b+1,b+n+1,num[i][j])-b;
	  	  pos[num[i][j]][i]=j;
	  }
	for(int i=1;i<=n;i++)
	  ans[i]=i;
	sort(ans+1,ans+n+1,cmp);
	for(int i=1;i<=n;i++)
	  writeln(b[ans[i]]);
	return 0;
}
```
在没有O2的情况下跑了132ms，应该算比较快了吧。

---

## 作者：scp020 (赞：1)

# P3034 [USACO11DEC] Cow Photography G/S 题解

模拟赛考到的题，来发题解。

## 解法

因为题中说如果一头奶牛在拍其中一张照片时移动了，它在拍其他四张照片的时候都不会移动，所以设有两头奶牛 $A$ 和 $B$，其中 $A$ 应该在 $B$ 的前面，那只有当奶牛 $A$ 跑到 $B$ 后面或者 奶牛 $B$ 跑到 $A$ 前面这两种情况能让两头奶牛的相对位置互换，所以对于这 $5$ 张照片，如果一头奶牛在另一头奶牛之前的位置超过 $5-2=3$ 次，则表明这头奶牛应该在那头奶牛的前面，他们的相对位置就确定下来了。我们只需要确定所有奶牛的相对位置即可。知道了所有奶牛的相对位置即可知道所有奶牛的绝对位置。这个可以在排序的过程中实现。

时间复杂度 $\mathcal{O}(n \log n)$，瓶颈在于排序。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace fast_IO
{
	/*
	fast Input/Output
	*/
};
using namespace fast_IO;
int n;
struct cow
{
	int x,pos[6];
	inline bool operator<(const cow &rhs) const
	{
		int cnt=0;
		for(int i=1;i<=5;i++) if(pos[i]<rhs.pos[i]) cnt++;
		return cnt>=3;
	}
};
cow a[20010];
unordered_map<int,int> mp;
int main()
{
	read(n);
	for(int i=1,x;i<=n;i++) read(x),a[i].x=x,a[i].pos[1]=i,mp[x]=i;
	for(int i=2,x;i<=5;i++) for(int j=1;j<=n;j++) read(x),a[mp[x]].pos[i]=j;
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++) write(a[i].x),write('\n');
	fwrite(Ouf,1,p3-Ouf,stdout),fflush(stdout);
	return 0;
}
```


---

## 作者：YuYuanPQ (赞：1)

# 洛谷 P3034 题解

## 题目大意

此为简要概括：

农夫要给奶牛们拍照；

但是奶牛会**乱动**，我们要求出奶牛原顺序；

题目会给出 $5$ 次拍照时，奶牛的顺序。

## 分析

我们可以发现：

如果其中 $1$ 头牛，出现在另外 $1$ 头牛前面**大于或等于** $3$ 次，那么说明它在原序列中就是在另外 $1$ 头牛**前面**。

可以自行**举例证明**，如果不明白或者不懂举例，也可以[**私信我**](https://www.luogu.com.cn/chat?uid=1029900)。

小提示：可以用`tr1::unordered_map`，因为它的**时间复杂度**是 $\mathcal{O}{(1)}$。

细节请看代码。

## 具体做法

- 读入。

- 排序（见上分析）。

- 输出。

## 注意事项

无。

## Code

```cpp
#include<bits/stdc++.h>
#include<tr1/unordered_map>
using namespace std;
int n,data[20010],x;
tr1::unordered_map< int , int > mp[11];
bool cmp(int p,int q){
	int cnt=0;
	for(int i=1;i<=5;i++)
	{
		if(mp[i][q]>mp[i][p]) cnt++;
	}
	if(cnt>=3) return 1;
	else return 0;
}
class P3034{
	public:
		void lzy(){
			read();
			solve();
			print();
		}
	private:
		void read()
		{
			scanf("%d",&n);
			for(int i=1;i<=5;i++)
			{
				for(int j=1;j<=n;j++)
				{
					scanf("%d",&x);
					if(i==5) data[j]=x;
					mp[i][x]=j;
				}
			}
		}
		void solve()
		{
			sort(data+1,data+1+n,cmp);
		}
		void print()
		{
			for(int i=1;i<=n;i++) printf("%d\n",data[i]);
		}
};
int main()
{
	P3034 y;
	y.lzy();
	return 0;
}
```


## 另附

- [题目链接](https://www.luogu.com.cn/problem/P3034)

- 如有更好做法，欢迎[私信我](https://www.luogu.com.cn/chat?uid=1029900)。

- [我的提交记录](https://www.luogu.com.cn/record/list?pid=P3034&user=1029900)

- 这是我第 $3$ 次写题解，如有错误请各位大佬**指出**。

---

## 作者：ImposterAnYu (赞：1)

# 解析
题目中有几个很重要的信息：

1. FJ 拍了 $5$ 张照片。

2. **每头奶牛最多只移动一次。**（如果没有这个条件，这道题就不可做了。）

3. 奶牛的编号在 $[1,10^9]$ 内。

其中，前两个信息是告诉我们答案的。为什么呢？我们先一步步分析。

假设原先的 $A$ 序列里有两个编号 $a_i$ 和 $a_j$，并且 $i < j$，那么当这 $5$ 张照片里出现 $a_i$ 和 $a_j$ 且 $i > j$ 时，要么就是 $a_i$ 跑到了 $a_j$ 后面，要么就是 $a_j$ 跑到了 $a_i$ 前面。因为每头奶牛最多乱跑一次，所以当原先的 $a_i$ 在 $a_j$ 前面时，最多只会有 $2$ 张照片里出现 $a_i$ 在 $a_j$ 后面。

于是，我们就可以通过这个特点写一个比较器，直接将打乱的 $A$ 序列用 `sort` 排序即可！

但是，奶牛的编号范围有点大，直接用这个范围开数组的话……不炸才怪！所以，为了方便起见，我们直接从 `STL` 里掏出一个~~常数有点大~~的大宝贝——`unordered_map`，并且可以直接当作正常的数组使用！
# code
```c++
#include<bits/stdc++.h>
#define int1 int
#define p 20005
using namespace std;
int1 n,i,j,a,ans[p],s;
unordered_map<int1,int1> b[10];
int1 read(){//快读。 
	int1 x = 0,f = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-'){
			f = -1;
		}
		ch = getchar();
	}
	while(isdigit(ch)){
		x = (x << 1) + (x << 3) + ch - '0';
		ch = getchar();
	}
	return x * f;
}
void print(int1 x){//快写。 
  	if(x < 0){
    	putchar('-');
    	x = -x;
  	}
  	if(x > 9){
    	print(x / 10);
  	}
  	putchar(x % 10 + 48);
  	return ;
}
bool cmp(int1 x,int1 y){//比较器。 
	for(i = 1,s = 0; i <= 5; i++){
		s += (b[i][x] < b[i][y]);
	}
	return s >= 3;//因为最多只能有 2 张照片里的顺序反过来，所以最少要有 3 张照片里的顺序是正着的。 
}
int main(){
	n = read();
	for(i = 1; i <= 5; i++){
		for(j = 1; j <= n; j++){
			a = read(),ans[j] = a,b[i][a] = j;//记录每头奶牛在照片（序列）里的位置。 
		}
	}
	sort(ans + 1,ans + n + 1,cmp);//直接排序。 
	for(i = 1; i <= n; i++){
		print(ans[i]);
		putchar('\n');
	}
    return 0;
}
```

---

## 作者：Exber (赞：1)

## 题意
- #### 有 $n$ 头牛，用小于等于 `1,000,000,000` 的正整数编好了号。牛们初始有一个排列顺序，FJ 希望以个顺序给牛拍照。
- #### FJ 一共拍了 5 张照，但是牛很不安分，总是从它自己的位置移动到其它位置，所以 FJ 不得不在每次拍照前都让它们排好序。
- #### 每头牛都有一次机会在拍某张照前移动到另一个位置。但一旦用了这个机会这头牛在拍剩下的四张照片时都不会再乱动了。
- #### 给出 5 张照片的顺序，求初始的排列顺序。

## 做法
哈希+排序。

首先，因为每头牛只能动一次，所以如果两头牛在超过 2 张照片中的先后顺序相同，那么这两头牛在初始的排列顺序中先后顺序便固定了。

那么只要对牛的任意一张照片用这种特殊的比较方法排一个序，就可以了。

可是有一个问题就是怎么 $O(1)$ 求出牛在某张照片里的位置。解决方法也很简单，只要用一个哈希表来把牛的编号映射到牛的位置就行了。

但是手写哈希比较麻烦，所以我们可以使用 `STL` 的 `unordered_map`。它的使用方法和 `map` 相同，不同的是 `map` 内部用的是红黑树，查询和修改时间复杂度均为 $O(log_2n)$；而 `unordered_map` 内部用的才是哈希表，查询时间为复杂度为 $O(1)$，但修改则比较慢。而对于这道题，由于只有输入的时候需要修改，所以使用 `unordered_map` 会更好些。

## AC 代码
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <tr1/unordered_map> // 头文件 

using namespace std;
using namespace std::tr1; // 注意这里，unordered_map 的命名空间是 std::tr1 

int n,ans[20005]; // ans 存初始排列（答案） 
unordered_map<int,int> a[10]; // a 存每张照片中牛的编号对应的位置 

bool cmp(int x,int y)
{
	int cnt=0; // 计数器，存有多少张照片中中 x 的位置比 y 靠前
	for(int i=1;i<=5;i++)
	{
		if(a[i][x]<a[i][y]) // 在这张照片中 x 的位置比 y 靠前 
		{
			cnt++; // 计数器 ++ 
		}
	}
	return cnt>2; // 计数器大于 2，则初始排列中 x 比 y 靠前 
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=5;i++)
	{
		for(int j=1;j<=n;j++)
		{
			int x;
			scanf("%d",&x);
			a[i][x]=j; // 建立映射关系 
			ans[j]=x;  // 对最后一张照片排序（其实对哪一张都没问题） 
		}
	}
	sort(ans+1,ans+n+1,cmp); // 排序 
	for(int i=1;i<=n;i++)
	{
		printf("%d\n",ans[i]); // 输出，记得换行 
	}
}
```

---

## 作者：Blender (赞：1)

## 题意：
- 有一堆奶牛，每次拍照前按一定顺序排好。
- 每次拍照时，有若干奶牛重新插入到新位置，不动的奶牛之间相对位置（即顺序）不变。
- 每个奶牛至多移动一次，若一个奶牛在一次拍照时移动，则在其他拍照时不动。
- 给你五次拍照后的结果，让你求原序列。

## 解析

**这道题的核心在于：考虑相对位置。**

设奶牛 x 和 y ，原序列中 x 在 y 前，我们尽可能让最多的时间 x 在 y 后：

1. 第一次， x 移到 y 后。
2. 第二次， y 移到 x 前。
3. 由于 x 和 y 都移动过了，而不管其他奶牛怎么移动，都不可能令 x 在 y 后，所以，至少有 3 次 x 和 y 保持 原序列的相对顺序。

所以，只需统计每次照相时两两的相对位置，若出现三次及以上**一者在另一者前的情况**，则原序列中也有如此前后关系。

~~为什么Farmer John要拍五次照？为了使保持任何两头奶牛维持原序列的先后状态（3+）， 永远大于不同于原序列的先后状态 （2-），因为这样才有唯一解。~~

**但是，有一句“保证所有编号都是不超过 1\,000\,000\,0001000000000 的非负整数。”**

说明 FJ 并不是按照“1，2，3 ···”的顺序编号的，此时我们要用离散化。

但是，如果直接用 STL map 的话，会时间超限。

看了高人的题解后，我知道了一种叫
```cpp
tr1::unordered_map
```
的东西，于是斗胆用了一下，经过多次尝试后，发现这东西可以帮助我们通过此题。

下面附上源码：
```cpp
#include <bits/stdc++.h>
#include <tr1/unordered_map>
using namespace std;
const int MAXN = 20000;
int n, List [MAXN+1];
tr1::unordered_map <int, int> Dis [6]; //离散化映射，具体在其他题解里有 
bool cmp (int a, int b){ //排序函数 
	int end = 0;
	for (int i=1; i<=5; i++) end += Dis[i][a]<Dis[i][b];
	return end >= 3;
}
int main (){
	scanf ("%d", &n);
	for (int i=1; i<=5; i++){
		for (int j=1; j<=n; j++){
			scanf ("%d", &List [j]);
			Dis [i][List[j]] = j;
		}
	}
	sort (List+1, List+n+1, cmp); // 通过cmp排序
	for (int i=1; i<=n; i++) printf ("%d\n", List [i]);
	return 0;
}
```


---

## 作者：Celtic (赞：1)

考虑到每对奶牛在 $5$ 次排列中最多有两次顺序调换。

证明很简单，第一次 $A$ 到 $B$ 后面去，$B$ 不动，第二次 $B$ 到 $A$ 前面去， $A$ 不动，其他情况 $A$,$B$ 都没法再动了，所以只有两次。

那么直接`sort`一遍就好了，`cmp`里就是 $A$ 在 $B$ 前的次数比 $B$ 在 $A$ 前的次数多。

代码

```cpp
#include<bits/stdc++.h>
#define re register
#define N 201001
#define MAX 2001
#define inf 1000000000000000000
using namespace std;
typedef long long ll;
typedef double db;
inline void read(re ll &ret)
{
    ret=0;re char c=getchar();re bool pd=false;
    while(!isdigit(c)){pd|=c=='-';c=getchar();}
    while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c&15);c=getchar();}
    ret=pd?-ret:ret;
    return;
}
ll n,a[6][N],pos[6][N],b[N],num[N];
map<ll,ll>mp;
inline bool cmp(re ll x,re ll y)
{
    re ll ret1=0,ret2=0;
    for(re int i=1;i<=5;i++)
    {
        if(pos[i][x]<pos[i][y])
            ret1++;
        else
            ret2++;
    }
    return ret1>ret2;
}
int main()
{
    read(n);
    for(re int j=1;j<=5;j++)
    {
        for(re int i=1;i<=n;i++)
        {
            read(a[j][i]);
            if(j==1)
                b[i]=a[j][i];
        }
    }
    sort(b+1,b+n+1);
    for(re int i=1;i<=n;i++)
    {
        num[i]=b[i];
        mp[b[i]]=i;
        b[i]=i;
    }
    for(re int j=1;j<=5;j++)
        for(re int i=1;i<=n;i++)
            pos[j][mp[a[j][i]]]=i;
    sort(b+1,b+n+1,cmp);
    for(re int i=1;i<=n;i++)
        printf("%lld\n",num[b[i]]);
    #ifdef WIN32
    system("pause");
    #endif
    exit(0);
}
```


---

## 作者：king_xbz (赞：1)

看了题解去众多大神的map，hash，今天我来分享一个stable_sort+unordered_map的算法。

我们先来了解一下STL中的stable_sort与unordered_map

- stable_sort是c++中的稳定排序函数。

它与sort最大的不同便是它的底层实现是归并排序。二者的复杂度都是O（nlogn）,但stable_sort更加稳定，而sort存在极端情况下复杂度为O（n^2）的可能。同时对于相等的元素sort可能会改变顺序而stablesort则可以保证排序后相等的元素次序不变；

- unordered_map是基于hash_table的一种映射。

相比普通的map而言，它能牺牲部分内存来换取常数级的查询复杂度。map的查询复杂度为O(nlogn)，而unordered_map的复杂度为O（1）。

知道了这些我们便可以在面对恶意数据下选择更优的写法来获取更多的分数了。

对于这道题，我们只需用映射模拟位置交换的过程，即若一头牛在三张照片中在另一头牛的前面，那么它在一定中就在另一头牛的前面，依次得到以下算法（c++11下无需O2即可AC）
```cpp
#include<bits/stdc++.h>
#include<unordered_map>
#define h 5001
#define p 783963
#define fint register int
using namespace std;
int a[p];
unordered_map<int,int>mp[h];//基于hash的map
inline int read();
inline bool cmp(int x,int y);
signed main()
{
	int n;
	n=read();
	int pos;
	for(fint i=1;i<=5;i++)
	for(fint j=1;j<=n;j++)
	pos=read(),mp[i][pos]=j,a[j]=pos;//储存位置及映射
	stable_sort(a+1,a+n+1,cmp);//稳定排序
	for(fint i=1;i<=n;i++)
	printf("%d\n",a[i]);
	return 0;
}

inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
		f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}

inline bool cmp(int x,int y)
{
    int ans=0;
    for(int i=1;i<=5;i++)
        if(mp[i][x]<mp[i][y])
		ans++;
    return ans>=3?1:0;
}
```
- 关于c++

我们知道unorder_map是c++11的特性，可是noip并不支持c++11，所以我们在c++编译模式下需要加上
```cpp
#include<tr1/unordered_map>
using namespace std::tr1;
```
不知不觉码了这么多行，估计我也是这道冷门题为数不多能如此详细讲解几种排序与映射的优劣了，希望管理大大给过。

最后祝大家AC愉快！

---

## 作者：yeshubo_qwq (赞：1)

思路：

考虑对于两头奶牛 $x$ 和 $y$，如何确定它们的先后顺序。

极端情况下，在一张照片里 $x$ 动了，导致顺序发生变化，在另一张照片里 $y$ 动了，导致顺序发生变化，那么，至少在另外的三张照片里，$x$ 和 $y$ 的顺序是确定的，我们可以根据这一点写一个 `cmp`，用 `sort` 进行排序。

重点要注意奶牛的编号的范围是 $10^9$，需要用离散化将奶牛的编号转成 $1 \sim n$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,i,j,a[6][20005],c[6][20005],b[20005],ans[20005];
bool cmp(int x,int y){
	int tot=0;
	for  (int i=1;i<=5;i++)
		if (c[i][x]<c[i][y]) tot++;
	return tot>=3;
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for (i=1;i<=5;i++)
		for (j=1;j<=n;j++)
			cin>>a[i][j];
	for (i=1;i<=n;i++) b[i]=a[1][i];
	sort (b+1,b+1+n);
	for (i=1;i<=5;i++)
		for (j=1;j<=n;j++){
			a[i][j]=lower_bound(b+1,b+1+n,a[i][j])-b;
			c[i][a[i][j]]=j;
		}
	for (i=1;i<=n;i++) ans[i]=i;
	sort (ans+1,ans+1+n,cmp);
	for (i=1;i<=n;i++) cout<<b[ans[i]]<<'\n';
	return 0;
}
```


---

