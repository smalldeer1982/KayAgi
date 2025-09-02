# Exact Neighbours (Hard)

## 题目描述

在最近食死徒对霍格华兹城堡发动了一些袭击之后，凤凰社决定将 $n$ 个成员安置在霍格迈德村。这些房子将坐落在一片风景如画的正方形场地上。每个巫师都有自己的房子，每个房子都属于某个巫师。每栋房子将占据一个正方形的空间。

然而，正如你可能知道的，巫师是非常迷信的。在周末，每个巫师 $i$ 都想参观距离自己房子$a_i$（$0 \leq a_i \leq n$）的房子。

村里的道路是水平和垂直修建的，因此点（$x_i，y_i$）和（$x_j，y_j$）之间的距离在 $n \times n$ 域上是$   |x_{i} - x_{j}| + |y_{i} - y_{j}| $ 。巫师们相互了解和信任，所以当第二个巫师不在时，一个巫师可以去另一个巫师的家。建造的房子将会足够大，所有 $n$ 个巫师都可以同时参观任何房子。

除此之外，每个巫师都必须能看到北边的霍格沃茨城堡和南边的禁林，所以其他巫师的房子不应该挡住视线。就村庄而言，这意味着在 $n \times n$ 域的每一列中，最多可以有一个房子，所以如果第 $i$ 个房子有坐标$（x_i，y_i）$，那么对于所有 $i$ 不等于 $j$ ，都有 $x_i \neq x_j$。

凤凰社还不知道是否有可能以这样的方式放置 $n$ 栋房子，以满足所有 $n$ 位巫师的参观和景观要求，所以他们请求您帮助设计这样的计划。

如果可以有一个正确的位置，其中第 $i$ 个向导的房子离它有 $a_i$ 的距离，而第 $i$ 个巫师的房子是他们列中唯一的房子，输出 $YES$，每个巫师的房子的位置，以及每个巫师周末应该去哪个向导的房子。

如果无法正确放置，则输出 $NO$。

## 样例 #1

### 输入

```
4
0 4 2 4```

### 输出

```
YES
4 4
1 3
2 4
3 1
1 1 1 3```

## 样例 #2

### 输入

```
4
1 3 0 1```

### 输出

```
YES
2 1
4 1
1 1
3 1
3 3 3 1```

# 题解

## 作者：xxgirlxx (赞：8)

## 说在前面

这题有一个坑点，就是它是以左下角为 $(1,1)$ 的。

## 题目大意

给你一个 $n \times n$ 的网格，要求在每一行上建一个房子，且要求第 $i$ 列的房子要和另一个房子（不一定唯一）的曼哈顿距离为 $a_i$。

注：

若设两点分别为 $(x_1,y_1)$ 和 $(x_2,y_2)$，则它们的曼哈顿距离为：

$$|x_1-x_2|+|y_1-y_2|$$

## Easy

[题目传送门](https://www.luogu.com.cn/problem/CF1970B1)

Easy 的性质是：所有的 $a_i$ 为偶数。

根据这条性质，我们可以把所有的房子都建在对角线上。即把第 $i$ 行的房子建在 $(i,i)$ 上。可以证明它一定是正确的。

因为我们建在了对角线上，所以 $|x_1-x_2|$ 和 $|y_1-y_2|$ 一定是相等的，所以它们加起来一定是偶数。也不会出界，因为 $a_i \le n$，所以 $a_i$ 对对应的房子的影响也就只有 $\frac{a_i}{2}$，所以如果 $i \le \frac{a_i}{2}$，我们就输出 $i+\frac{a_i}{2}$，因为 $\frac{a_i}{2}\le\frac{n}{2}$ 且 $i<\frac{n}{2}$，所以 $i+\frac{a_i}{2}<n$。否则输出 $i-\frac{a_i}{2}$。

### code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,a[N];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	cout<<"YES\n";
	for(int i=1;i<=n;i++)cout<<i<<" "<<i<<"\n";
	for(int i=1;i<=n;i++){
		if(a[i]/2<i)cout<<i-a[i]/2<<" ";
		else cout<<i+a[i]/2<<" ";
	}
	return 0;
}
```

## Medium

[题目传送门](https://www.luogu.com.cn/problem/CF1970B2)

其实 Easy 对之后的题目没什么作用（~~应该是送分的~~）。Medium 对 Hard 的启发才是比较大的。

Medium 的性质是：$a_1=0$。

因为 $a_1=0$，所以考虑将其自己与自己进行配对，然后放在 $(1,1)$ 这个位置上。并将其作为后续比对的模板。

后续的操作是：

对于每个 $2 \le i \le n$ 的 $i$。

如果 $a_i<i$，那么说明前面有一个房子与自己处于水平状态的距离为 $a_i$。也就是第 $i-a_i$ 个房子，我们便可以直接将这个房子的横坐标定成跟那个房子一样的，并将配对的屋子改成那个房子。因为我们每次操作完都会保存这个屋子的横坐标（纵坐标直接是 $i$，不用保存），所以这个操作是很容易实现的。

否则我们就将配对的房子定为第 $1$ 个，因为如果将配对的房子定为第 $1$ 个，就会只剩下 $a_i-i+1$ 个距离，这个时候，我们就将房子向右移，移到 $a_i-i+2$（因为原本就在 $1$）。

### code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,a[N],mp[N],ans[N];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i],mp[i]=1;
	cout<<"YES\n1 1\n",mp[1]=ans[1]=1;
	for(int i=2;i<=n;i++){
		if(a[i]<i)cout<<i<<" "<<mp[i-a[i]]<<"\n",mp[i]=mp[i-a[i]],ans[i]=i-a[i];
		else cout<<i<<" "<<2+a[i]-i<<"\n",mp[i]=2+a[i]-i,ans[i]=1;
	}
	for(int i=1;i<=n;i++)cout<<ans[i]<<" ";
	return 0;
}
```

## Hard

[题目传送门](https://www.luogu.com.cn/problem/CF1970B3)

~~Hard 的性质是：没有性质。~~

这题我们需要考虑三个点。

1、有 $a_i=0$ 的情况。

将其与 $a_1$ 交换并放置在 $(1,1)$，跑一遍 Medium 再换回来。

2、有 $a_i=a_j$ 的情况。

将其与 $a_1,a_2$ 交换并放置在 $(1,1),(2,a_i)$，跑一遍 Medium 再换回来。

3、有 $a_i$ 为 $n$ 的排列的情况。

$n\le2$ 就无解。 

找出 $a_i=1,a_j=2,a_k=3$。

将其与 $a_1,a_2,a_3$ 交换并放置在 $(1,1),(2,1),(3,2)$，跑一遍 Medium 再换回来。

### code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,a[N],mp[N],ans[N],ansx[N],ansy[N],flag,flag1,flag2,flag3,c[N];
struct node{
	int num,id;
}b[N];
int cmp(node u,node v){
	return u.num<v.num;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i],mp[i]=1,b[i].num=a[i],b[i].id=i,c[i]=i;
	sort(b+1,b+n+1,cmp);
	for(int i=1;i<=n;i++){
		if(a[i]==0){
			flag1=i;
			flag=1;
			mp[1]=1;
			ansx[1]=1;
			ansy[1]=1;
			ans[1]=flag1;
			swap(c[1],c[flag1]);
			swap(a[1],a[flag1]);
			break;
		}
	}
	if(flag==0){
		for(int i=1;i<n;i++){
			if(b[i].num==b[i+1].num){
				flag=2;
				flag1=b[i].id;
				flag2=b[i+1].id;
				mp[1]=1;
				mp[2]=b[i].num;
				ansx[1]=1;
				ansy[1]=1;
				ansx[2]=2;
				ansy[2]=b[i].num;
				ans[1]=flag2;
				ans[2]=flag1;
				swap(c[1],c[flag1]);
				swap(c[2],c[flag2]);
				swap(a[1],a[flag1]);
				swap(a[2],a[flag2]);
				break;
			}
		}
	}
	if(flag==0){
		if(n<=2){
			cout<<"NO\n";
			return 0;
		}
		for(int i=1;i<=n;i++){
			if(a[i]==1)flag1=i;
			if(a[i]==2)flag2=i;
			if(a[i]==3)flag3=i;
		}
		flag=3;
		mp[1]=1;
		mp[2]=1;
		mp[3]=2;
		ansx[1]=1;
		ansy[1]=1;
		ansx[2]=2;
		ansy[2]=1;
		ansx[3]=3;
		ansy[3]=2;
		ans[1]=flag2;
		ans[2]=flag3;
		ans[3]=flag1;
		swap(c[1],c[flag1]);
		swap(c[2],c[flag2]);
		swap(c[3],c[flag3]);
		swap(a[1],a[flag1]);
		swap(a[2],a[flag2]);
		swap(a[3],a[flag3]);
	}
	for(int i=flag+1;i<=n;i++){
		if(a[i]<i)ansx[i]=i,ansy[i]=mp[i-a[i]],mp[i]=mp[i-a[i]],ans[i]=c[i-a[i]];
		else ansx[i]=i,ansy[i]=2+a[i]-i,mp[i]=2+a[i]-i,ans[i]=c[1];
	}
	if(flag==1){
		swap(ansx[1],ansx[flag1]);
		swap(ansy[1],ansy[flag1]);
		swap(ans[1],ans[flag1]);
	}
	else if(flag==2){
		swap(ansx[1],ansx[flag1]);
		swap(ansy[1],ansy[flag1]);
		swap(ans[1],ans[flag1]);
		swap(ansx[2],ansx[flag2]);
		swap(ansy[2],ansy[flag2]);
		swap(ans[2],ans[flag2]);
	}
	else{
		swap(ansx[1],ansx[flag1]);
		swap(ansy[1],ansy[flag1]);
		swap(ans[1],ans[flag1]);
		swap(ansx[2],ansx[flag2]);
		swap(ansy[2],ansy[flag2]);
		swap(ans[2],ans[flag2]);
		swap(ansx[3],ansx[flag3]);
		swap(ansy[3],ansy[flag3]);
		swap(ans[3],ans[flag3]);
	}
	cout<<"YES\n";
	for(int i=1;i<=n;i++)cout<<ansx[i]<<" "<<ansy[i]<<"\n";
	for(int i=1;i<=n;i++)cout<<ans[i]<<" ";
	return 0;
}
```

---

## 作者：rizynvu (赞：1)

[我的博客](https://www.cnblogs.com/rizynvu/p/18172772)。

*Easy* 没什么启发性，直接考虑 *Medium*。

考虑到 $a_1 = 0$，那么 $1$ 明显直接和自己配对就行，考虑分配到一个特殊的位置 $(1, 1)$。  

接下来考虑如果还有 $a_i = 0$，那么明显 $i$ 也是和自己配对，此时因为这是无关紧要的就可以离特殊的 $(1, 1)$ 尽量远一点，也就是让 $x$ 坐标尽量大。  
同时如果有 $a_i = a_j$，那么就可以让 $i, j$ 互相配对，还是一样尽量远，可以让两个的 $x$ 坐标就相差 $1$，构造 $(x, 1), (x + 1, a_i)$ 即可。

剩下的不同的 $a_i$ 的取值肯定就只存在一个 $a_i$ 了。  
这个时候考虑到 $(2, y)$ 与 $(1, i)$ 的距离可以为 $1\sim n$，$(3, y)$ 与 $(2, i)$ 的距离可以为 $2\sim n + 1$……  
那么就可以把剩下的 $a_i$ 从小到大排序，然后 $x$ 从 $2$ 开始依次往大了去填，因为 $a_i\le n$ 且因为每种取值最多存在一个有 $a_i\ge x - 1$，肯定可以分配出 $y$。

那么就构造完了，按照这个方式可以知道肯定有解。

时间复杂度 $\mathcal{O}(n)$。

代码写丑了写成了 $\mathcal{O}(n\log n)$，把 *map* 换成桶即可。

```cpp
#include<bits/stdc++.h>
const int maxn = 2e5 + 10;
int a[maxn];
int dx[maxn], dy[maxn], to[maxn];
bool vis[maxn];
int main() {
   int n;
   scanf("%d", &n);
   for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
   dx[1] = dy[1] = to[1] = 1;
   std::map<int, int> mp;
   int w = n;
   for (int i = 2; i <= n; i++) {
      if (! a[i]) {
         dx[i] = w--, dy[i] = 1, to[i] = i;
      } else {
         if (mp[a[i]]) {
            int j = mp[a[i]];
            dx[i] = w--, dx[j] = w--, to[i] = j, to[j] = i;
            dy[i] = 1, dy[j] = a[i];
            mp[a[i]] = 0;
         } else
            mp[a[i]] = i;
      }
   }
   w = 2;
   for (auto _ : mp) {
      int v = _.first, id = _.second;
      if (! id) continue;
      dx[id] = w, dy[id] = 1 + v - (w - 1), to[id] = 1, w++;
   }
   puts("YES");
   for (int i = 1; i <= n; i++) printf("%d %d\n", dx[i], dy[i]);
   for (int i = 1; i <= n; i++) printf("%d ", to[i]);
   return 0;
}
```

接下来考虑 *Hard*。

首先如果存在 $a_i = 0$，那么还是像 *Medium* 那样做就行了。

否则考虑用一些其他的替代掉 $a_i = 0$ 的作用。

一个想法是对于 $a_i = a_j$ 的，可以分配到 $(1, 1), (2, a_i)$，然后就像 *Medium* 一样构造。  
但是能发现这个有个小问题，就是因为 $x = 2$ 已经被占了，导致如果存在 $a_k = 1$ 这个 $k$ 没有位置了。  
但是可以考虑把 $k$ 拎出来，先填完 $2\sim n$ 的。  
因为 $a_k = 1$ 实际上就是 $x$ 坐标差 $1$，$y$ 坐标相同，设填完 $2\sim n$ 最后一个填的的坐标是 $(x, y)$，给 $k$ 分配 $(x + 1, y)$ 即可。  
还有一种方式是一开始分配成 $(1, a_i), (2, 1)$，然后特殊点就变为 $(2, 1)$，就是完全一样的了。

发现还是会漏掉情况。  
但是能发现漏掉的情况只会有 $1\sim n$ 都只刚好出现 $1$ 次。  
这个时候能发现 $n = 2$ 时无解。  
否则对于 $a_i = 1, a_j = 2, a_k = 3$，可以分别构造出 $(1, 1), (2, 1), (3, 2)$，其中 $i\to j, j\to k, k\to i$。  
然后对于 $4\sim n$ 的和其他的一样构造即可。

时间复杂度 $\mathcal{O}(n)$。

```cpp
#include<bits/stdc++.h>
const int maxn = 2e5 + 10;
int a[maxn];
int dx[maxn], dy[maxn], to[maxn];
int lst[maxn];
int main() {
   int n;
   scanf("%d", &n);
   for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
   int f = 0, fid = 0, bk = n, edy = 0, edid = 0;
   for (int i = 1; i <= n; i++) {
      if (! a[i]) {
         if (! f) dx[i] = ++f, fid = i, edy = 1, edid = i;
         else dx[i] = bk--;
         dy[i] = 1, to[i] = i;
      } else if (lst[a[i]]) {
         int &j = lst[a[i]];
         if (! f) dx[i] = ++f, dx[j] = ++f, fid = i, edy = a[i], edid = j;
         else dx[i] = bk--, dx[j] = bk--;
         dy[i] = 1, dy[j] = a[i], to[i] = j, to[j] = i;
         j = 0;
      } else lst[a[i]] = i;
   }
   if (! f) {
      if (n == 2)
         return puts("NO");
      int &x = lst[1], &y = lst[2], &z = lst[3];
      f = 3, fid = x, edy = 2, edid = z;
      dx[x] = 1, dy[x] = 1;
      dx[y] = 2, dy[y] = 1;
      dx[z] = 3, dy[z] = 2;
      to[x] = y, to[y] = z, to[z] = x;
      x = y = z = 0;
   }
   for (int i = 2; i <= n; i++)
      if (lst[i]) {
         int p = lst[i];
         dx[p] = ++f, dy[p] = 1 + i - (f - 1), to[p] = fid;
         edy = dy[p], edid = p;
      }
   if (lst[1]) {
      int p = lst[1];
      dx[p] = ++f, dy[p] = edy, to[p] = edid;
   }
   puts("YES");
   for (int i = 1; i <= n; i++) printf("%d %d\n", dx[i], dy[i]);
   for (int i = 1; i <= n; i++) printf("%d ", to[i]);
   return 0;
}
```

---

## 作者：EXODUS (赞：0)

# Part 1：前言

比较简单的构造。

# Part 2：正文

从 B1 看起。由于 $a_i\in [0,n]$ 且为偶数，所以直接在主对角线上填所有巫师的房子就是对的，这个比较简单。

然后来看 B2。对于这种构造题，我们一般希望能够钦定对于某个数被谁贡献。注意到 $a_1=0$，也就是说 $a_1$ 的条件天然满足，所以我们希望钦定一组顺序 $ord$，使得 $ord_i$ 被 $ord_{i-1}$ 满足且 $ord_1=1$。而每列只有一个巫师给了我们一个很明确的提示，也即按行填巫师。不妨直接尝试把 $1$ 号巫师填在左上角，然后按照 $ord$ 的顺序在列中顺次分配接下来的巫师。我们希望的是，对于第 $ord_i$ 个巫师，其与 $ord_{i-1}$ 个巫师在列上的距离是 $a_i-1$，且其位置不能超过地图边界。不难想到将除了 $1$ 以外的巫师按照 $a_i$ 降序排序，然后以下-上-下-上的方式排列这些巫师。由于 $a_i\leq a_{i-1}$，故其不会越过边界。

最后看 B3。我们寄希望于用类似 B2 的手法来构造解。也就是我们希望能够找到若干个位置，其限制条件能被天然满足，然后我们就能将其平移以后进行上面的算法。存在 $a_i=0$ 就是 B2 的做法。如果存在一对 $(i,j)$ 满足 $a_i=a_j$，我们可以将其分别放在 $(a_i-1,1)$ 和 $(1,2)$ 的位置，注意到此时 $(2,1)$ 巫师的限制被满足了，故可以对剩下的巫师跑 B2 的做法。

剩下的东西满足 $a_i$ 两两不同，说白了就是一个长度为 $n$ 的排列。我们只需要对于这种情况特殊构造即可。经过一点手玩，我们发现可以让 $a_i=1,2,3$ 互相满足，然后让后一个满足前一个的方式完成这种情况的构造，下面给出一个 $n=5$ 的例子。

```
5..21
..3..
.....
.....
.4...

```

唯一需要注意的是 $a_i=0$ 的情况和 $n=2$ 且为排列时无解。

# Part 3：代码

```cpp
// I know it looks as if the world has come for us
// 我知道新的世界也许即将到来
// We will never fade away
// 可我们却不会因此而消失
// I know this voices in the ashes to revive
// 我知晓深海中曼妙的歌声即将重现于世
// We will never fade away
// 可我们却不会因此而消逝
// We are the,we are the silence before the storm
// 我们的沉默是暴风雨前的宁静

#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ldb;

#define rep(i,l,r) for(int i(l);i<=(r);++i)
#define per(i,r,l) for(int i(r);i>=(l);--i)
#define eb emplace_back
#define File(filename) freopen(filename ".in","r",stdin),freopen(filename ".out","w",stdout)
#define Exit(p) fprintf(stderr,"[exit]: at breakpoint %d\n",p),exit(0);

#ifdef EXODUS
	#define Debug(...) fprintf(stderr,__VA_ARGS__)
#else
	#define Debug(...) 0
#endif

//=========================================================================================================
// Something about IO

template<typename T>
void read(T &x){
	x=0;T flg=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')flg=-1;ch=getchar();}
	while(isdigit(ch))x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	x*=flg;
}
template<typename T>
void seq_read(T bg,T ed){for(auto i=bg;i!=ed;++i)read(*i);}
template<typename T,typename... Args>
void read(T &x,Args &...args){read(x),read(args...);}

//=========================================================================================================
//Some useful function

template<typename T>
void cmax(T& x,T y){x=max(x,y);}
template<typename T,typename... Args>
void cmax(T& x,T y,Args ...args){cmax(x,y);cmax(x,args...);}
template<typename T>
void cmin(T& x,T y){x=min(x,y);}
template<typename T,typename... Args>
void cmin(T& x,T y,Args ...args){cmin(x,y);cmin(x,args...);}
template<typename T,typename U>
void seq_assign(T bg,T ed,U val){for(auto i=bg;i!=ed;++i)(*i)=val;}
template<typename T,class F,class=enable_if_t<is_invocable_v<F>>>
void seq_assign(T bg,T ed,F func){for(auto i=bg;i!=ed;++i)(*i)=func(i);}
template<typename T>
void seq_copy(T dstbg,T dsted,T srcbg,T srced){for(auto i=dstbg,j=srcbg;i!=dsted&&j!=srced;++i,++j)(*i)=(*j);}

//=========================================================================================================
// Define the global variables here.

bool membg=0;

constexpr int N=2e5+7;
int n;
int a[N];
pair<int,int>ans[N];
int pos[N];
map<int,int>buc;

bool memed=0;

//=========================================================================================================
// Code here.

void solve(){
	read(n);
	for(int i=1;i<=n;i++)
		read(a[i]);
	int x=-1,y=-1;
	for(int i=1;i<=n;i++)
		if(a[i]==0){
			x=i;
			break;
		}
	if(x!=-1){
		vector<int>ord(n);
		iota(ord.begin(),ord.end(),1);
		rotate(ord.begin(),find(ord.begin(),ord.end(),x),ord.end());
		sort(next(ord.begin()),ord.end(),[&](int X,int Y){return a[X]>a[Y];});
		int sign=1,ny=1;
		ans[x]=make_pair(1,1);
		pos[x]=x;
		for(int i=1;i<n;i++){
			// printf("%d\n",ord[i]);
			ans[ord[i]]=make_pair(i+1,ny+=sign*max(a[ord[i]]-1,0));
			pos[ord[i]]=(a[ord[i]]==0?ord[i]:ord[i-1]);
			sign*=-1;
		}
		printf("YES\n");
		for(int i=1;i<=n;i++)
			printf("%d %d\n",ans[i].first,ans[i].second);
		for(int i=1;i<=n;i++)
			printf("%d ",pos[i]);
		printf("\n");
		return;
	}
	for(int i=1;i<=n;i++){
		if(buc.count(a[i])){
			x=buc[a[i]],y=i;
			break;
		}else{
			buc[a[i]]=i;
		}
	}
	if(x!=-1){
		vector<int>ord(n);
		iota(ord.begin(),ord.end(),1);
		rotate(ord.begin(),find(ord.begin(),ord.end(),x),ord.end());
		ord.erase(find(ord.begin(),ord.end(),y));
		ord.insert(next(ord.begin()),y);
		sort(next(ord.begin(),2),ord.end(),[&](int X,int Y){return a[X]>a[Y];});
		int sign=1,ny=1;
		ans[x]=make_pair(1,a[x]);
		pos[x]=y;
		ans[y]=make_pair(2,1);
		pos[y]=x;
		for(int i=2;i<n;i++){
			// printf("%d\n",ord[i]);
			ans[ord[i]]=make_pair(i+1,ny+=sign*max(a[ord[i]]-1,0));
			pos[ord[i]]=(a[ord[i]]==0?ord[i]:ord[i-1]);
			sign*=-1;
		}
		printf("YES\n");
		for(int i=1;i<=n;i++)
			printf("%d %d\n",ans[i].first,ans[i].second);
		for(int i=1;i<=n;i++)
			printf("%d ",pos[i]);
		printf("\n");
		return;
	}
	if(n==2){
		return printf("NO\n"),void();
	}
	vector<int>ord(n);
	iota(ord.begin(),ord.end(),1);
	sort(ord.begin(),ord.end(),[&](int X,int Y){return a[X]>a[Y];});
	int sign=1,ny=1;
	for(int i=0;i<n-2;i++){
		ans[ord[i]]=make_pair(i+1,ny);
		pos[ord[i]]=ord[i+1];
		ny+=sign*(a[ord[i]]-1);
		sign*=-1;
	}
	pos[ord[n-3]]=ord[n-1];
	pos[ord[n-2]]=ord[n-3];
	ans[ord[n-2]]=make_pair(n-1,ans[ord[n-3]].second+1<=n?ans[ord[n-3]].second+1:ans[ord[n-3]].second-1);
	pos[ord[n-1]]=ord[n-2];
	ans[ord[n-1]]=make_pair(n,ans[ord[n-3]].second+1<=n?ans[ord[n-3]].second+1:ans[ord[n-3]].second-1);
	printf("YES\n");
	for(int i=1;i<=n;i++)
		printf("%d %d\n",ans[i].first,ans[i].second);
	for(int i=1;i<=n;i++)
		printf("%d ",pos[i]);
	printf("\n");
	return;
}


//=========================================================================================================

int main(){
	Debug("%.3lfMB\n",fabs(&memed-&membg)/1024.0/1024.0);
	int timbg=clock();
	int T=1;
	while(T--)solve();
	int timed=clock();
	Debug("%.3lfs\n",1.0*(timed-timbg)/CLOCKS_PER_SEC);
	fflush(stdout);
	return 0;
}
```

---

