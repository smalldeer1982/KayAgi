# Yet Another Sorting Problem

## 题目描述

Petya 有一个整数数组 $ a_1, a_2, \ldots, a_n $。他只喜欢有序数组。但给定的数组可能是任意的，因此 Petya 想要将其排序。

Petya 喜欢挑战自己，所以他只想使用每次选择三个数进行轮换的方法进行排序。形式化地说，每次操作中，他可以选择三个互不相同的下标 $ i $, $ j $, $ k $（ $ 1 \leq i, j, k \leq n $ ）并对数组 $ a $ 应用 $ i \to j \to k \to i $ 轮换。该操作会同时将 $ a_i $ 放到位置 $ j $，$ a_j $ 放到位置 $ k $，$ a_k $ 放到位置 $ i $，其他元素保持不变。

例如，若 $ a $ 为 $ [10, 50, 20, 30, 40, 60] $ 并选择 $ i = 2 $, $ j = 1 $, $ k = 5 $，则数组变为 $ [\underline{50}, \underline{40}, 20, 30, \underline{10}, 60] $。

Petya 可以进行任意次（包括零次）的轮换操作。你需要判断 Petya 是否能将数组 $ a $ 排序为一个单调不减的序列。

## 说明/提示

在第六个测试用例中，Petya 可以使用 $ 3 $ -轮换 $ 1 \to 3 \to 2 \to 1 $ 来排序数组。

在第七个测试用例中，Petya 可以先应用 $ 1 \to 3 \to 2 \to 1 $ 得到 $ a = [1, 4, 2, 3] $，再应用 $ 2 \to 4 \to 3 \to 2 $ 完成排序。

----

翻译由 DeepSeek 生成。

## 样例 #1

### 输入

```
7
1
1
2
2 2
2
2 1
3
1 2 3
3
2 1 3
3
3 1 2
4
2 1 4 3```

### 输出

```
YES
YES
NO
YES
NO
YES
YES```

# 题解

## 作者：王熙文 (赞：9)

## 思路

看到交换和排序后的数组，可以想到逆序对。

一个逆序对的结论：**在一个没有重复数字的序列中交换两个不同的位置 $i,j$（$i<j$），逆序对的个数奇偶性改变**。

证明：

首先，如果交换相邻的位置，则逆序对的个数只会被它们两个的关系改变，即会 $+1$ 或 $-1$。在模 $2$ 意义下相当于 $+1$。

**可以将交换不同的位置转换成交换相邻的位置**。设最左边的那个数是 $a$，右边的是 $b$，中间的区间为区间 $R$。则最开始的顺序是 $\text{aRb}$。首先，将 $a$ 和区间 $R$ 从左到右交换，此时的顺序变成了 $\text{Rab}$。其次，交换 $a$ 和 $b$，此时的顺序变成了 $\text{Rba}$。最后，将 $b$ 和区间 $R$ 从右到左交换，此时的顺序变成了 $\text{bRa}$，就完成了交换。可以发现，相邻的位置交换了 $1+(j-i-1) \times 2$ 次，所以**逆序对的个数奇偶性改变**。

但是这道题中有重复的数，所以我们先处理重复的数。当有重复的数时，**利用两个重复的数可以做到将一个重复的数与其他的一个数交换**。所以最初可以先将两个重复的数填到该放的位置上。

这个性质可以扩展到，**利用重复的数可以交换任意两个数**。比如 $\text{abc}$，$a,b$ 是要交换的两个数，$c$ 是一个重复的数。那么首先交换 $a,c$，变成 $\text{cba}$，接下来交换 $c,b$，变成 $\text{bca}$，最后交换 $c,a$，变成 $\text{bac}$，就完成了交换。

这样，剩下的数通过交换就可以都放到它们该放的地方了。因此，**重复的数一定可以排序**。

剩下的情况便是没有重复的数的情况了。考虑原操作用交换来表现出来。原操作是将 $\text{abc}$ 变成 $\text{cab}$。这个操作就等价于交换，$a,b$，变成 $\text{bac}$，然后交换 $b,c$，变成 $\text{cab}$。那么因为交换一次逆序对奇偶性改变，所以交换两次，**即原操作，逆序对奇偶性就不会改变**。而排序后的数组逆序对个数为 $0$，所以我们猜测**当且仅当逆序对个数为偶数的时候可以排序**。

首先，逆序对个数为奇数的时候，奇偶性不改变，所以一定不能排序。接下来需要构造一个方案使得任意逆序对个数为偶数的时候都可以排序。考虑先将前 $n-2$ 个位置归位。当归位第 $i$ 个位置的时候，用操作将第 $i$ 个位置、该填在这个位置的数、最后一个位置一起执行操作轮换过去即可。最后剩下两个数，此时逆序对一定为偶数，所以它们的关系一定也是顺序的。这样就排好序了。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n; int a[500010];
int tree[500010];
bool vis[500010];
void upd(int wz,int x)
{
	while(wz<=5e5+5)
	{
		tree[wz]+=x;
		wz+=wz&-wz;
	}
}
int get_sum(int wz)
{
	int sum=0;
	while(wz)
	{
		sum+=tree[wz];
		wz-=wz&-wz;
	}
	return sum;
}
signed main()
{
	int t; cin>>t; while(t--)
	{
		cin>>n;
		for(int i=1; i<=n; ++i) cin>>a[i];
		bool flag=0;
		memset(vis,0,n+5);
		for(int i=1; i<=n; ++i)
		{
			if(vis[a[i]]) { flag=1; break; }
			vis[a[i]]=1;
		}
		if(flag) { puts("YES"); continue; }
		int nxd=0;
		for(int i=1; i<=n; ++i)
		{
			nxd+=i-1-get_sum(a[i]);
			upd(a[i],1);
		}
		for(int i=1; i<=n; ++i) upd(a[i],-1);
		puts(!(nxd&1)?"YES":"NO");
	}
	return 0;
}
```

---

## 作者：xiaozeyu (赞：3)

[CF1585D Yet Another Sorting Problem](https://www.luogu.com.cn/problem/CF1585D)

 逆序对以及树状数组。
 
 题目中会给出一个初始序列。
 
 我们每次可以选中 $3$ 个数字，一次操作中可以将这几个数字循环变换。
 
 这里的循环变换是将这三个数字右移变换。
 
 也就是说选出三个位置 $i,j,k$，它同时将 $a_i$ 放置在位置 $j$ 上，$a_j$ 放置在位置 $k$ 上，$a_k$ 放置在位置 $i$ 上，而不改变任何其他元素。
 
 我们要求出这个序列是否能通过一系列的操作排序成不严格单调递增的。
 
 我们可以先考虑选出三个不同的数字进行排序。
 
 在三个数字情况下，在 $2,3,1$ 或 $3,2,1$ 时，变换后逆序对数量是减少的，减少了二队逆序对，这说明更加接近递增情况了。
 
 将其放大到全部情况可以发现也是类似的。
 
 这样子的变换不难发现当为一对逆序对时，无法再变换成严格递增。应为一次拿出三个换，而本身只要拿出两个就行了，另一个一定会受到影响，换后的情况实则一样，此时表明不行。
 
 但是别忘了，题目要求的时不严格单调递增。
 
 不严格与严格的区别在哪里呢？就是不严格时可以有相等的数字放在一起。
 
 我们还需考虑一下相等的数字应该如何去处理。
 
 当选出的三个数字中有两个相同时，我们可以发现，这相当于将不同的那个数字随便放置！
 
 这说明有数字相同时，优势在我！这时一定可以成功。
 
 那我们就再用树状数组计数，检验逆序对的奇偶性，判一下相同数字，直接完成任务。
 
 注意一点，不要直接重置整个数组，可以这样子写。
 
 ```cpp
memset(s,0,n+10<<2);
memset(f,0,n+10<<2);
```

时间复杂度 $O(n\log n)$。

 代码如下。
 
 ---
 
 ```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=a;i<=b;i++)
#define Rep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
int read()
{
	char c=getchar();int x=0;bool f=0;
	while(!isdigit(c))f^=!(c^45),c=getchar();
	while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();
	if(f)x=-x;return x;
}
const int maxn=500010;
int T,n,s[maxn],f[maxn],x;
long long ans;
void update(int x){for(;x<=n;x+=x&-x)s[x]++;}
int query(int x){int ans=0;for(;x;x-=x&-x)ans+=s[x];return ans;}
int main()
{
	T=read();
	while(T--)
	{
		n=read();ans=0;
		memset(s,0,n+10<<2);
		memset(f,0,n+10<<2);
		For(i,1,n) x=read(),f[x]++,ans+=i-1-query(x),update(x);
		For(i,1,n) if(f[i]>1) ans=0;
		puts(ans&1?"NO":"YES");
	}
}

```

 感谢管理员的审核。
 

---

## 作者：dd_d (赞：2)

[更好的阅读体验](https://www.cnblogs.com/dd-d/p/15712398.html) 

### 题意  
 
给定一个长度为 $n$ 的数组 $a$。  
每次操作可以选择三个数进行循环右移。  
询问是否可以将数组排序。  

### Sol  
若数组中存在相同的数，那么显然有解。  
再考虑没有数相同的情况。  
由于是挑 $3$ 个数循环右移，那么每次逆序对的数量会减少 $2$。  
那么统计一下逆序对即可。  
我用的是树状数组。时间复杂度 $O(n \log n)$，存在 $O(n)$ 做法。  

### Code
```cpp
//LYC_music yyds!
#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(0)
#define lowbit(x) (x&(-x))
using namespace std;
inline char gc()
{
	static char buf[1000000],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
}
int read()
{
	int pos=1,num=0;
	char ch=getchar();
	while (!isdigit(ch))
	{
		if (ch=='-') pos=-1;
		ch=getchar();
	}
	while (isdigit(ch))
	{
		num=num*10+(int)(ch-'0');
		ch=getchar();
	}
	return pos*num;
}
void write(int x)
{
	if (x<0)
	{
		putchar('-');
		write(-x);
		return;
	}
	if (x>=10) write(x/10);
	putchar(x%10+'0');
}
void writesp(int x)
{
	write(x);
	putchar(' ');
}
void writeln(int x)
{
	write(x);
	putchar('\n');
}
const int N=5e5+10;
bool vis[N],flag;
int n,a[N],tree[N];
inline void add(int x,int y)
{
	for (;x<=n;x+=lowbit(x))
		tree[x]+=y;
}
inline int query(int x)
{
	int res=0;
	for (;x;x-=lowbit(x))
		res+=tree[x];
	return res;
}
signed main()
{
	int T=read();
	while (T--)
	{
		n=read(); flag=0;
		for (int i=1;i<=n;i++)
			vis[i]=0,tree[i]=0;
		for (int i=1;i<=n;i++)
		{
			a[i]=read();
			if (vis[a[i]]) flag=1;
			vis[a[i]]=1;
		}
		if (flag)
		{
			puts("YES");
			continue;
		}
		int res=0;
		for (int i=1;i<=n;i++)
		{
			res+=query(n)-query(a[i]);
			add(a[i],1);
		}
		if (res&1) puts("NO");
		else puts("YES");
	}
}




```

---

## 作者：Michael1234 (赞：1)

本题主要考察**如何求逆序对**：

分析题目，我们可以发现，每转一次，我们会改变两组数的顺序，就像这样：`abcde->acdbe`。

此时，`bc` 和 `bd` 的顺序改变。

由此得出当逆序对的数量为偶数时，该序列有解，反之无解。

接下来就是如何在 $O(n\log n)$ 的时间复杂度的情况下求逆序对的数量，这里使用树状数组统计值域的方法。我们倒序枚举 $a$，枚举到 $a_i$ 时。我们将答案加上已统计到的小于 $a_i$ 的数，因为他们在 $a_i$ 后面，所以这个数量就是 $a_i$ 作为大数时逆序对的数量，这里用树状数组值域前缀和维护。再将 $a_i$ 的数量加一。

但是会出现一个问题，一个样例会卡住我们：`aba`。

如果向上面那样统计，这个序列有一个逆序对，但是这个样例可以变为 `aab`，满足要求。这是因为 `aa` 的顺序改变了，但是对序列的单调不降没有影响。所以当出现一对相同的数，其可也可不被统计为逆序对，因此只要出现相同的数时，此序列有解，问题得到解决。

---

## 作者：XL4453 (赞：1)

### 解题思路：

如果存在两个相同的数。那就利用这两个数实现交换其中一个数和任意一个其它的数的操作，这样就一定能实现最终的升序。（或者结合下文将其理解为减少或者增加一个逆序对）

否则就是所有的元素都不相同的情况，则每一次交换若逆序对数量变化，则一定减少两个或者增加两个逆序对，只需要统计出逆序对的数量然后判断奇偶性就行了。

---
这个性质可以用枚举法推导出来，不妨用 $1$，$2$，$3$ 表示从小到大的三个数，然后写出交换后的情况即可，具体如下：

$1$，$2$，$3$ 转化为：$3$，$1$，$2$，增加两组逆序对。

$1$，$3$，$2$ 转化为：$2$，$1$，$3$，逆序对数量不变。

$2$，$1$，$3$ 转化为：$3$，$2$，$1$，增加两组逆序对。

$2$，$3$，$1$ 转化为：$1$，$2$，$3$，减少两组逆序对。

$3$，$1$，$2$ 转化为：$2$，$3$，$1$，逆序对数量不变。

$3$，$2$，$1$ 转化为：$1$，$3$，$2$，减少两组逆序对。

---
### 代码：
```cpp
#include<cstdio>
using namespace std;
int n,num[500005],v[500005],cnt,T,bit[500005],flag;
void init(){
	cnt=0;flag=0;
	for(int i=1;i<=n;i++)
	v[i]=bit[i]=num[i]=0;
}
int lowbit(int x){
	return x&(-x);
}
void add(int i){
	for(;i<=n;i+=lowbit(i))
	bit[i]++;
}
int query(int i){
	int ans=0;
	while(i){
		ans+=bit[i];
		i-=lowbit(i);
	}
	return ans;
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		init();
		for(int i=1;i<=n;i++)scanf("%d",&num[i]);
		for(int i=1;i<=n;i++){
			if(v[num[i]]==1){
				printf("YES\n");
				flag=1;
				break;
			}
			v[num[i]]=1;
		}
		if(flag==1)continue;
		for(int i=1;i<=n;i++){
			cnt+=query(n)-query(num[i]-1);
			add(num[i]);
		}
		if(cnt&1)printf("NO\n");
		else printf("YES\n");
	}
	return 0;
}
```



---

## 作者：skyskyCCC (赞：0)

## 前言。
这个比赛的第五题和第六题都不会，然后勉强写出了第四题，纪念一下。

题意简述：给定一个 $n$ 元序列，每次可以选数组中三个元素进行轮换，即可以将三元组 $\left(i,j,k\right)$ 变成 $\left(j,k,i\right)$ 或者 $\left(k,i,j\right)$。请判断是否通过大于等于 $0$ 次操作使其排为非降序，输出你的判断。
## 分析。
注意到本片题解中的 $i$ 和 $j$ 以及 $k$ 均不是题目中的下标，而是表示一个元素。

首先这就是一个三元组的问题，这种问题的基本思路通常就是分析这个变化的下标，然后取判断特殊情况。

如果我们只考虑 $\left(i,j,k\right)$ 则显然在每次变换中，逆序数都是 $2$ 或 $-2$ 的。但是我们发现，交换的三元组的下标在 $1$ 到 $n$ 中可以随便取，那么我们去考虑交换的三元组中有其它的元素，我们不妨用 $\left(i,num_x,j,k\right)$ 表示在 $i$ 和 $j$ 中间有 $x$ 个元素。首先考虑变化为 $\left(j,num_x,k,i\right)$ 的情况，由于 $num_x$ 到了 $j$ 的右边，所以我们不妨从这个变化比较大的元素上入手。假设在原来的 $num_x$ 中，有 $k$ 个值比 $j$ 大，那么必定有 $x-k$ 个值比 $j$ 小，所以经过分析，我们可以得知 $j$ 对于 $num_x$ 的逆序对个数的数量就会从 $k$ 变成 $x-k$ 个，那么其中变换了 $x-2\times k$ 个。那么同理我们变换 $i$ 则可以知道如果有 $k_2$ 个数比 $i$ 小，那么 $i$ 就会将逆序对的数量变换 $x-2\times k_2$ 个。那么我们现在就可以考虑总数了，此次变换中的逆序对的个数除了 $\left(i,j,k\right)$ 本身的 $\pm 2$ 外，还会变换 $x-2\times k+x-2\times k_2$ 个。我们发现它可以转换为 $2\times x-2\times k-2\times k_2$ 显然可以提出一个 $2$。而这代表着改变偶数个。

同理，我们可以扩展到每一种情况，都不难证明这样的变换总是使得逆序对数量会变化偶数个，所以不改变原排列的奇偶性。此时我们对于一个从 $1$ 到 $n$ 的有序排列下标来说，我们能够任意变换，使其成为一个偶排列。此时我们可以得到本题的一个重要结论：**对于每个元素的下标，题目中的变换形式对下标操作后的结果一定是个偶排列**。

然后分情况讨论在原三元组中是否有相同的元素即可。没有就简单地离散化处理一下，然后求出原三元组所在的序列中的逆序对的数量，只要是个偶数，就一定能存在一种方法使得其满足题目要求。如果有相同的元素，那么如果存在两个相同的元素，变换后放在首尾的位置上，此时逆序对改变的数量为 $1$ 个，原序列的奇偶性可以改变，所以此时无论原序列是奇序列还是偶序列，都存在答案，直接判断为存在即可。

逆序对的数量可以采用树状数组来查询。

代码如下，仅供参考：
```
#include<iostream>
using namespace std;
int t,n;
int flag,ans;
int u[500005],p[500005];
struct node{
    int num,id;
}a[500005];
void add(int x){
    while(x<=n){
        p[x]++;
        x+=(x&-x);
    }
}
int sum(int x){
    int res=0;
    while(x>=1){
        res+=p[x];
        x-=(x&-x);
    }
    return res;
}
int main(){
    cin>>t;
    while(t--){
    	flag=ans=0;
        cin>>n;
        for (int i=1;i<=n;i++){
            cin>>a[i].num;
            a[i].id=i;
            u[i]=p[i]=0;
        }
        for (int i=1;i<=n;i++){
            if(u[a[i].num]){
                flag=1;
                break;
            }
            u[a[i].num]=1;
        }
        if(flag) cout<<"YES\n";
        else{
            for (int i=1;i<=n;i++){
                ans+=sum(n)-sum(a[i].num);
                add(a[i].num);
            }
            if(ans%2!=0) cout<<"NO\n";
			else cout<<"YES\n";
        }
    }
    return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

