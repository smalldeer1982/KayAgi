# Masha and a Beautiful Tree

## 题目描述

Masha 在森林里散步时发现了一棵深度为 $n$ 的满二叉树，它有 $m = 2^n$ 个叶子结点，每个叶子节点上都有一个正整数 $p_i$。

Masha 希望交换一些子树之后可以使从左往右数的第 $i$ 个叶子结点上的正整数为 $i$（因为她觉得这样的一棵满二叉树很漂亮）。你需要帮她找到最少需要交换的次数。

## 样例 #1

### 输入

```
4
8
6 5 7 8 4 3 1 2
4
3 1 4 2
1
1
8
7 8 4 3 1 2 6 5```

### 输出

```
4
-1
0
-1```

# 题解

## 作者：Komorebi_03 (赞：5)

题意不过多概述了。

### 思路：

考虑根左子树的数集合是 $A$。

右子树的数集合是 $B$。

那么无论你左右子树内部怎么转。

这个集合是不会变的。

所以你只有可能通过根的交换。

来换 $A,B$ 这两个完整的集合。

所以有解情况当且仅当 $A,B$ 集合有一个全是小的数另外一个全是大的数。
```cpp
//By:Komorebi_03
#include<bits/stdc++.h>
using namespace std;
#define clear(a) memset(a,0,sizeof a)
#define ll long long
const int N = 1e6+5;
int T,n,a[N];
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}

int main()
{
	T=read();
	while (T--)
	{
		n=read();
		clear(a);
		for (int i=1;i<=n;i++)
			a[i]=read();
		int cnt=0;
		bool flag=false;
		for (int i=2;i<=n;i<<=1)
		{
			for (int j=i;j<=n;j+=i)
			{
				if(a[j-(i>>1)]>a[j])
				{
					swap(a[j-(i>>1)],a[j]);
					cnt++;
				}
				if(a[j-(i>>1)]+(i>>1)!=a[j])
				{
					cout<<-1<<"\n";
					flag=true;
					break;
				}
			}
			if(flag)
				break;
		}
		if(flag)
			continue;
		cout<<cnt<<"\n";
	}
	return 0;
	//Amireux_35
}

```


---

## 作者：smallpeter (赞：4)

一道有趣的题目。

# 解题思路

画个图便能快速的明白这题交换的本质。
![](https://cdn.luogu.com.cn/upload/image_hosting/kgfznl5p.png)
实际上使得 $[L,R]$ 这段区间从小到大排序要满足以下几个条件。
- 区间 $[L,mid]$ 单调递增
- 区间 $[mid+1,R]$ 单调递增
- 区间 $[L,mid]$ 中的数为区间 $[L,R]$ 中的前 $mid-L+1$ 大或前 $mid-L+1$ 小

因为每段区间中的数是被禁锢着的，所以只能进行区间之间的交换。（这点比较好理解，读者可自己理解一下）

## 不满足上列条件

也就是说这段区间不是单调递增的，无解输出 -1。

## 满足上列条件

那么分两种情况讨论。

### 区间 $[L,R]$ 中的数为区间 $[L,R]$ 中前 $mid-L+1$ 大的数

那么需要交换区间 $[L,mid]$ 和 $[mid+1,R]$，操作次数 +1。

### 区间 $[L,R]$ 中的数为区间 $[L,R]$ 中前 $mid-L+1$ 小的数

显然不需要交换，已经满足要求。

## 做法

显然可以用递归模拟这个过程，若 $L=R$ 则不需要进行任何操作它就满足单调递增，直接回溯。否则砍成两段，继续递归下去。回溯过程如上文所述。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
 
#define LL long long
 
const LL N=262145;
 
LL t,n,a[N],b[N],c[N];
 
LL dfs(LL l,LL r)
{
	if(l==r) return 0;
	LL mid=(l+r)>>1;
	LL t1=0,t2=0;
	for(LL i=l;i<=mid;i++) b[++t1]=a[i];
	for(LL i=mid+1;i<=r;i++) c[++t2]=a[i];
	sort(b+1,b+t1+1);
	sort(c+1,c+t2+1);
	if(b[1]>=c[t2]) //两端都单调递增且左端为前 mid-l+1 大 
	{
		LL x=dfs(l,mid);
		LL y=dfs(mid+1,r);
		if(x==-1||y==-1) return -1; //不能使得这段单调递增 
		return x+y+1;
	}
	else if(b[t1]<=c[1]) //两端都单调递增且左端为前 mid-l+1 小 
	{
		LL x=dfs(l,mid);
		LL y=dfs(mid+1,r);
		if(x==-1||y==-1) return -1; //不能使得这段单调递增 
		return x+y;
	}
	return -1; //不能使得这段单调递增 
}
 
int main()
{
	scanf("%lld",&t);
	while(t--)
	{
		scanf("%lld",&n);
		for(LL i=1;i<=n;i++) scanf("%lld",&a[i]);
		printf("%lld\n",dfs(1,n));
	}
} 
```


---

## 作者：A_grasser (赞：2)

## 题意简化

给定一个叶子结点个数为 $n=2^k$ 的完全二叉树，通过交换任意一节点的两棵子树，实现叶子结点编号单调递增。如果能交换出，输出最小交换次数，否则无解。

## 解法分析

这道题要动脑筋想一想。先理解下面这几条内容：

1. 不管两棵子树怎么交换，它**里面的元素都不变**，即**别的节点的子树上的东西无法转移到当前子树上**。

1. 为了得出结果，每棵子树**都应是连续单调递增的**。

理解上面内容后，实现也就比较简单。循环子树，并比较每两棵子树的最大叶子编号，通过交换实现每棵子树的最后一个叶子是从小到大的。需要交换时，答案加一。

根据上面一号结论，当两棵子树交换完，它们最大的叶子结点相差量不等于两棵子树总叶子结点数的二分之一时，应是无解，因为无法从其他子树填补漏掉的那个叶子。于是，就保持了结论二。

想通了之后，这道题好像就做完了。

由于思路取自于[这篇题解](https://www.luogu.com.cn/article/oahunai5)，所以代码会有些相似，请谅解。

最后说一句，我比较推荐万能头文件，这样可以省去很多不必要的麻烦。

## 完整代码

```cpp
//已通过
#include<bits/stdc++.h>
//万能头文件
using namespace std;
int t,n,a[1000007],ans,f;
int main(){
	cin>>t;
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		ans=f=0;
		for(int i=2;i<=n;i*=2){//枚举子树叶子结点数量（子树大小） 
			for(int j=i;j<=n;j+=i){//枚举当前子树最后一个叶子结点 
				if(a[j-(i/2)]/*上一棵相邻子树的最后叶子结点*/>a[j]){//交换 
					swap(a[j-(i/2)],a[j]);
					ans++;
				}
				if(a[j-(i/2)]+(i/2)!=a[j]){//无解情况 
					printf("-1\n");
					f=1;
					break;
				}
			}
			if(f!=0) break;
		}
		if(f==0) printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：CSPJ10pts (赞：2)

# 题目大意：

给你一串连续自然数，交换一些相邻的，长度为 $2^k$ 的区间之后可以使数列有序，求可行性和最少交换的次数。

# 思路：
第一步：假装排个序

我们可以用类似 ST 表的思想，让 $k$ 从小到大递增，比较每两个长度为 $2^k$ 的区间的最后一个数，把大的换到后面，小的放到前面，下一次检查 $2^{k+1}$ 长度的区间时，又只调查最后一个数，可以大大降低时间复杂度。

第二步：判断是否合法

观察每一段有序的连续自然数列，可以发现第 $2^k$ 和第 $2^{k+1}$ 个数差是 $2^k$ 。那么我们便可以用这么一个~~显而易见的~~奇妙的性质检查序列是否可以满足题意：当第 $2^k$ 个数加第 $2^{k+1}$ 个数不等于 $2^k$ 时（即这个数被其他非 $2^k$ 占掉了），可以宣布不合法。

为什么可以这样呢？

首先因为 $k$ 是从小到大的，每一次如果不合法会直接跳出，因此可以知道，每 $2^k$ 个数里一定是一个连续的自然数串。

其次，如果在 $1$ ~ $2^k$ 的连续自然数串里的最大的不是 $2^k$，说明这一段根本不包含这个数或者有更大的数，无论哪种情况都不合理，可以判断不合法。

这一步比较难想，大家可以多思考一下.

# 代码

```
#include <iostream>
#include <algorithm>
using namespace std;
int t, n, a[262150];
int main() {
    cin >> t; // t组数据
    while (t--) {
        bool f = 0; // 结束标记
        int cnt = 0; // 计数器，计算交换次数
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i]; // 输入
        for (int x = 2; x <= n; x *= 2) { // 2的n次方分组
            for (int j = x; j <= n; j += x) {
                if (a[j - x / 2] > a[j]) swap(a[j], a[j - x / 2]), cnt++; // 如果发现逆序的，换一下位子，计数器加1
                if (a[j] != a[j - x / 2] + x / 2) { // 出现不满足要求的情况
                    cout << -1 << endl;
                    f = 1;
                    break; // 下次再见
                }
            }
            if (f) break; 
        }
        if (!f) cout << cnt << endl; // 输出
    }
    return 0;
}
```

[AC记录](https://www.luogu.com.cn/record/91142461)

求过 QwQ

---

## 作者：Symbolize (赞：2)

# 思路
我们可以发现除了叶子节点以外的每一个点，他们都有两个子节点。那我们肯定写一个递归呀，传入目前要操作的区间 $l,r$，外加类似于深度的变量 $u$。那么要想使所有叶子结点从 $1$ 到 $n$ 顺序，那显然，每次操作都必须对成为顺序做出贡献。这不就是对于我们的递归函数传入的 $l,r$ 进行二分吗？显然如果 $a_r-a_l$ 为 $1$。就交换。
# Code
```cpp
#include<bits/stdc++.h>
#define int long long
#define x first
#define y second
#define rep1(i,l,r) for(int i=l;i<=r;i++)
#define rep2(i,l,r) for(int i=l;i>=r;i--)
const int N=1e6+10;
using namespace std;
int t,n,k,a[N],cnt;
bool dfs(int u,int l,int r)
{
	if(u==k)//深度满了 
	{
		if(abs(a[l]-a[r])!=1) return 0;
		if(a[l]>a[r]) 
		{
		    swap(a[l],a[r]);//交换 
		    ++cnt;
		}
		return 1;//递归出口 
	}
	int mid=l+r>>1;
	if(dfs(u+1,l,mid)&&dfs(u+1,mid+1,r))//二分 
	{
		if(abs(a[mid]-a[mid+1])==1) return 1;
		if(abs(a[r]-a[l])==1)
		{
			++cnt;
			//交换 
			swap(a[mid],a[r]);
			swap(a[l],a[mid+1]);
			return 1;
		}
		return 0; 
	}
	return 0;
}
void getans()
{
	cin>>n;
	rep1(i,1,n) cin>>a[i];//输入 
	if(n==1)//特判 
	{
		puts("0");
		return;
	}
	cnt=k=0;
	for(int i=1;i<n;i*=2) ++k;//找那个指数 
	//输出 
	if(dfs(1,1,n)) cout<<cnt<<endl;
	else puts("-1");
}
signed main()
{
// 	freopen("D.in","r",stdin);
// 	freopen("D.out","w",stdout);
	cin>>t; 
	while(t--) getans();//循环要答案 
	return 0;
}
```

---

## 作者：_zqh_ (赞：1)

**水题一道**。

# 思路简述

本题采用分治，只需要 DFS 一遍即可，

每次将序列拆成两块，分别将两块进行递归，统计答案。

然后判断这一层是否要交换，若要交换，则交换序列并答案加一；否则跳过。

**思路部分完结**。

# Code

```cpp
#include <bits/stdc++.h>
#define ios                  \
ios::sync_with_stdio(0); \
cin.tie(0);              \
cout.tie(0)
// #pragma GCC Typetimize(2)
#define ll long long
#define pll pair<ll, ll>
#define pii pair<ll, ll>
#define il inline
#define p_q priority_queue
#define u_m unordered_map
#define r_g register
using namespace std;

namespace Nothing {
	il int read() {
		int f = 1, t = 0;
		char ch = getchar();
		while (ch < '0' || ch > '9') {
			if ( ch == '-' ) {
				f = -1;
			}
			ch = getchar();
		}
		while (ch >= '0' && ch <= '9') {
			t = t * 10 + ch - '0';
			ch = getchar();
		}
		return t * f;
	}

	il void write(int x, bool s) {
		if (x < 0) {
			putchar('-');
			write(-x, false);
			return ;
		}
		if (!s && x == 0)
			return ;
		if (s && x == 0) {
			putchar('0');
			return ;
		}
		write(x / 10, false);
		putchar(x % 10 + '0');
	}
}

int n;
int a[1000005];
int ans = 0;

void dfs(int Size, int fBeg) {
	if (Size < 1) return ;
	int sBeg = fBeg + Size;
	dfs(Size / 2, fBeg);
	dfs(Size / 2, sBeg);
	if (a[fBeg] < a[sBeg]) {
		return ;
	}
	for (r_g int i = fBeg, j = sBeg, k = 1; k <= Size; k++, i++, j++) {
		swap(a[i], a[j]);
	}
	ans++;
}

signed main() {
	ios;
	int T;
	T = Nothing::read();
	while (T--) {
		n = Nothing::read();
		ans = 0;
		for (r_g int i = 1; i <= n; i++) {
			a[i] = Nothing::read();
		}
		dfs(n / 2, 1);
		bool flag = false;
		for (r_g int i = 1; i <= n; i++) {
			if (a[i] != i) {
				flag = true;
				break;
			}
		}
		if (flag) {
			puts("-1");
			continue;
		}
		Nothing::write(ans, true);
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：AlicX (赞：1)

### 题意
给你一颗有 $n$ 个叶节点的树，保证 $n$ 是 $2^k$，让你交换任意一个节点下的两颗子树，最终让叶节点变成 $1$~$n$ 的序列。 如果可以就输出最小的交换次数，不行输出 $-1$。

### 思路
对于这道题我们可以发现除了叶节点以外的每一个点，他们都有两个儿子节点。且要使最终序列为 $1$~$n$，每一个节点经过交换后就一定要是有序的，且需要与其相邻的节点构成一个有序的序列。知道了这些，我们还发现，每次交换，并不需要交换整个区间，而只用交换区间头，区间尾即可。用递归判断判断每一个节点内是否有序，一旦全部有序说明整个区间就有序了。

#### 注：结合代码来看更清晰

## AC code 
```cpp
#include<bits/stdc++.h>
#define int long long
#define x first
#define y second
using namespace std;
typedef pair<int,int> pii;
const int N=300010;
int n,k;
int a[N];
int cnt=0;
inline bool dfs(int u,int l,int r){//u代表深度，l，r代表所管辖的区间 
	if(u==k){//到达了最后一层不是叶节点的点，这一层只会有两个点 
		if(abs(a[l]-a[r])!=1) return false;//判断这两个点是否满足条件 
		if(a[l]>a[r]) swap(a[l],a[r]),cnt++;//为了使原序列有序，这两点应该有序，交换次数加一 
		return true;
	}
	int p1=l+r>>1;//中点 
	if(dfs(u+1,l,p1)&&dfs(u+1,p1+1,r)){//判断左右区间是否有序 
		if(abs(a[p1]-a[p1+1])==1) return true;//左区间的最后一个数与右区间的第一个数是连接上的 
		if(abs(a[r]-a[l])==1){//交换两个区间后变成了有序的 
			cnt++;//交换次数加一 
			swap(a[p1],a[r]),swap(a[l],a[p1+1]);//因为只关于区间头和区间尾，所以只交换头尾 
			return true;
		}
		return false; 
	}
	return false;
}
signed main(){
// 	freopen("D.in","r",stdin);
// 	freopen("D.out","w",stdout);
	int T;
	scanf("%lld",&T);
	while(T--){
		scanf("%lld",&n);
		for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
		if(n==1){//特判 
			printf("0\n");
			continue;
		}
		cnt=0,k=0;
		for(int i=1;i<n;i*=2) k++;//k是这颗树的深度 
		if(dfs(1,1,n)) printf("%lld\n",cnt);//cnt是交换的次数 
		else printf("-1\n");
	}
	return 0;//Bye~ 
}/*
4
8
6 5 7 8 4 3 1 2
4
3 1 4 2
1
1
8
7 8 4 3 1 2 6 5
*/
```
可能会有不足的地方，请大家指出，谢谢。

---

## 作者：我梦见一片焦土 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF1741D)

------------
# 思路：
一个从局部到整体的思想，先确定局部的先后顺序，维护树内的先后顺序。通过缩小树的范围确定每次是否要移动，每相邻两个点的编号的大小比较来确定是否要进行移动。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10;
const int INF=0x3f3f3f3f;
int T,n,ans,s,f,a[N],b[N];
signed main(){
	cin>>T;
	while(T--){
		cin>>n;
		ans=s=f=0;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		if(n==1){
			cout<<0<<endl;
			continue;
		}
		while(1){
			for(int i=1;i<=n;i+=2){
				if(abs(a[i]-a[i+1])!=1){
					f=1;
					break;
				}
				if(a[i]==a[i+1]+1){
					s++;
					swap(a[i],a[i+1]);
				}
			}
			if(f==1){
				break;
			}
			ans=0;
			for(int i=1;i<=n;i+=2){
				ans++;
				b[ans]=a[i+1]/2;
			}
			n=ans;
			for(int i=1;i<=n;i++){
				a[i]=b[i];
			}
			if(n==1){
				break;
			}
		}
		if(f==1){
			cout<<-1<<endl;
		}else{
			cout<<s<<endl;
		}
	}
	return 0;
}
```

---

## 作者：Special_Tony (赞：0)

[洛谷传送门](/problem/CF1741D) & [CF 传送门](//codeforces.com/problemset/problem/1741/D)
# 思路
这题中我们只能对任意一个根节点的两棵子树进行整体**交换**，而不是整体**翻转**。而每两个子树交换两次就会变回原先的样子，所以我们对这两棵子树最多只会交换一次，即要么不交换，要么只交换一次。我们只要用类似归并排序的方式枚举每一对子树的父节点，然后按以下步骤进行递归：
1. 拆分两个子树进行递归；
1. 如果两个子树中有不合法的，则这整棵树肯定也不合法，提前返回不合法；
1. 分情况考虑：
	1. 如果当前整个区间已经有序，即左子树区间的最后一个元素比右子树区间的第一个元素还小，则说明合法，提前返回合法；
	1. 如果左子树和右子树调换后有序，即左子树区间的第一个元素比右子树的最后一个元素还大，则也说明合法，但是要调换过，所以我们要先对两个子树进行调换，然后对记录交换次数的答案 $ans$ 加一，也返回合法；
	1. 其它情况时，不交换也不合法，交换了也不合法，就是真的不合法了，返回不合法。

到此，整个递归流程就完成了。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
int t, n, a[262150], ans;
void merge (int& l, int& mid) { //交换
	int i = l, j = mid + 1;
	while (i <= mid)
		swap (a[i], a[j]), ++ i, ++ j;
	return ;
}
bool stablesort (int l, int r) {
	if (l >= r) //只有一个元素，当然合法
		return 0;
	int mid = (l + r) / 2; //两个子树的分界点，l 到 mid 是左子树，mid+1 到 r 是右子树
	if (stablesort (l, mid) || stablesort (mid + 1, r)) //子树都不合法
		return 1;
	if (a[mid] < a[mid + 1]) //不要交换
		return 0;
	else if (a[l] > a[r]) //要交换
		merge (l, mid), ++ ans;
	else //不合法
		return 1;
	return 0;
}
int main () {
	cin >> t;
	while (t --) {
		cin >> n;
		ans = 0; //多组数据要清空
		for (int i = 0; i < n; ++ i)
			cin >> a[i];
		if (stablesort (0, n - 1)) //这里我其实故意搞反了，1 表示不合法，0 表示合法
			cout << "-1\n";
		else
			cout << ans << '\n';
	}
	return 0;
}
```

---

## 作者：WaterSun (赞：0)

# 思路

我们可以观察样例，不难发现：对于任意一段长度为 $2^k$ 的区间中，如果最大值减最小值加 $1$ 等于此区间的长度，那么一定有解。

因为，我们的目标是使整个序列升序排列。因此，我们在一个区间内的最大值减最小值加 $1$ 与区间长度是相等的。

所以，我们可以用上述结论为判断无解的标准。

那么，如果我们有解，那么我们的交换次数又是多少呢？

结果为任意两个相对的左右子树中，左子树的最小值大于了右子树的最小值的数量。

因为，我们要使序列升序，那么左区间的最小值一定是要小于右区间的最小值的。

所以，我们在上述条件是成立的。

得出了这两个结论后，不难发现：我们一切的过程都与区间最值有关。那么，我们考虑建一棵线段树，维护区间最值。

然后依据上述条件进行操作即可。

# code

```cpp
#include <bits/stdc++.h>
#define re register

using namespace std;

const int N = 3e5 + 10;
int T,n;
int arr[N];

struct node{
	int l;
	int r;
	int Min;
	int Max;
}tr[N << 1];

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + c - 48;
		c = getchar();
	}
	return r * w;
}

inline void pushup(int u){
	tr[u].Min = min(tr[u << 1].Min,tr[u << 1 | 1].Min);
	tr[u].Max = max(tr[u << 1].Max,tr[u << 1 | 1].Max);
}

inline void build(int u,int l,int r){//建树模板 
	tr[u] = {l,r};
	if (l == r){
		tr[u].Max = tr[u].Min = arr[l];
		return;
	}
	int mid = l + r >> 1;
	build(u << 1,l,mid);
	build(u << 1 | 1,mid + 1,r);
	pushup(u);
}

inline bool query1(int u,int l,int r){//按照刚才的规则判断是否合法 
	if (l == r) return true;
	int mid = tr[u].l + tr[u].r >> 1;
	if (!query1(u << 1,l,mid) || !query1(u << 1 | 1,mid + 1,r)) return false;//左右子树均为合法才行 
	if (tr[u].r - tr[u].l == tr[u].Max - tr[u].Min) return true;//还要判断本身是否合法 
	return false;
}

inline int query2(int u,int l,int r){//然后统计一下左子树最小值大于右子树最小值的数量 
	if (l == r) return 0;
	int mid = tr[u].l + tr[u].r >> 1;
	int res = query2(u << 1,l,mid) + query2(u << 1 | 1,mid + 1,r) + (tr[u << 1].Min > tr[u << 1 | 1].Min);//ans = 左子树的数量 + 右子树的数量 + 本身的数量 
	return res;
}

int main(){
	T = read();
	while (T--){
		n = read();
		for (re int i = 1;i <= n;i++) arr[i] = read();
		build(1,1,n);
		if (!query1(1,1,n)) puts("-1");
		else printf("%d\n",query2(1,1,n));
	}
	return 0;
}
```

---

## 作者：awask (赞：0)

# 提供一种类似于归并排序思想的解法

由题意，当这棵树达到 Masha 的预期时，恰好排序成功。利用 DFS 递归解决本问题。若可以通过若干次数的交换达成预期目标，则每个 $[l,r]$ 区间中的 $x_{mid+1}-x_l=\left| mid+1-l \right|$ ，其中$mid = \left \lfloor \frac{l}{r}  \right \rfloor $ 。若存在一区间不符合上式，直接结束 DFS 并输出 $-1$ ；否则，当 $x_{mid+1}-x_l=-(mid+1-l)$ 时，交换 $[x_l,x_{mid}]$ 与 $[x_{mid+1},x_r]$ 区间，同时让 $ans$ 增加 $1$ ；当 $x_{mid+1}-x_l=mid+1-l$ 时，无需操作，因为 $[l,r]$ 区间内排序已经完成。这种情况都有可能达到预期情况，则继续进行 DFS 。

注意，当 $m=1$ 时，需要特判输出 $0$ ，不然 DFS 会爆炸。

由于本人的编码习惯，题目中与代码中的 $n$ 与 $m$ 交换。

细节可以查看代码。

```cpp
#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;
int x[(1<<18)+20],n,m,ans;
bool dfs(int l,int r)
{
	int mid=(l+r)>>1;
	if(l!=r-1)//类似于归并排序的思路
	{
		bool a=1;
		a=a&dfs(l,mid);
		a=a&dfs(mid+1,r);
		if(a==0)return 0;//如果两棵子树产生了无解情况，则停止DFS
		if(abs(x[l]-x[mid+1])!=(mid+1-l))
			return 0;
		if((x[l]-x[mid+1])==(mid+1-l))
		{
			for(int i=l;i<=mid;i++)
				swap(x[i],x[i+r-mid]);
			ans++;
			return 1;
		}
	}
	if(l==r-1)//边界条件，l=r-1，两个点进行比较
		if(abs(x[l]-x[r])!=1)
			return 0;
		else if(x[l]>x[r])
		{
			swap(x[l],x[r]);
			ans++; 
			return 1;
		}
	return 1;//没有中途退出，则有解。
}
int main()
{
	cin>>m;
	while(m--)
	{
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>x[i];
		if(n==1)//特判 m=1 的情况
		{
			cout<<0<<endl;
			continue;
		}
		ans=0;
		if(dfs(1,n))cout<<ans<<endl;
		else cout<<-1<<endl;
	}
	return 0;
}
```
------------
如有疏漏之处或错误之处请尽快通知我，我会尽快更正。

---

## 作者：what_else (赞：0)

它要咱**建树**咱就**建树**。

它要咱**交换**咱就**交换**。


没错，这就是**暴力**！

我们定义这棵树的某个结点有一个权值 $a$，$a=\min(a_l,a_r)$。如果这个结点为**叶子结点**，就令 $a=p_i$ （ $p$ 为初始排列 ）。

不难发现，如果一个非叶子结点的左子树 $l$ 与右子树 $r$ 满足 $a_l>a_r$，那么就得交换，因为这个操作是**必须**的，现在不做以后还得做。

最后跑一遍，看看是否满足要求。

举个例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/jni705kd.png)

从根到叶进行遍历，在结点 $2$ 发现 $a_l>a_r$，将它们交换（实际就是交换左右子树），结点 $3$ 同理，得到 $1,3,2,4$，在结点 $1$ 不用交换。最后得 $p=\{1,3,2,4\}$，显然不符合题意，所以为无解。

如果开始是 $4,3,2,1$ 呢？按照这个算法，会交换一次 $4,3$，一次 $2,1$，一次 $3,4,1,2$，得到 $p=\{1,2,3,4\}$，符合题意，输出交换次数 $3$。



时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int tree[569000],l[569000],r[569000],pui[590000],m,t,pub[590000],cnt;//tree初始序列,l,r左右子树,pui该结点权值,pub新数列
int dfs(int i){//返回当前操作次数
	if(i<m) {
		l[i]=i*2;
		r[i]=i*2+1;
		int j=dfs(i*2);
		int k=dfs(i*2+1);
		if(pui[i*2]>pui[i*2+1]){
			swap(l[i],r[i]);
			pui[i]=min(pui[i*2],pui[i*2+1]);
			return j+k+1;
		}
		else {
			pui[i]=min(pui[i*2],pui[i*2+1]);
			return j+k;
		}
	}
	else {
		pui[i]=tree[i];
		return 0;
	}
}
void check(int i){
	if(i<m){
		check(l[i]);
		check(r[i]);
		return;
	}
	else {
		cnt++;
		pub[cnt]=tree[i];
	}
}
int main(){
	cin>>t;
	for(int i=1;i<=t;i++){
		cin>>m;
		for(int i=1;i<=m*2;i++){
			tree[i]=0;
			pub[i]=0;
			l[i]=0;
			r[i]=0;
			pui[i]=0;
		}
		for(int j=m;j<=m*2-1;j++)
		cin>>tree[j];
		int ans=dfs(1);
		cnt=0;
		check(1);
		bool flag=false;
		for(int j=1;j<=m;j++){
			if(j!=pub[j]){
				flag=1;
				//break;
			}
		}//验证
		if(flag)cout<<-1<<endl;
		else cout<<ans<<endl;
	}
}
```

---

## 作者：Hedgehog_210508 (赞：0)

**题目传送门**：[here](https://www.luogu.com.cn/problem/CF1741D)

~~提示：题解比较抽象。~~

**思路**：先看是否可行。从最终排好序的情况倒过来看，交换之后， $2^i\times j-2^i+1$ 到 $2^i\times j$ 这些数仍然是连续的，因为要么内部交换，要么整体交换。以样例为例：

第一组：$6,5$ 连续；$4,3,1,2$ 连续等等。

最后一组：像 $7,8,4,3$ 就不符合。

再看交换次数：如果左边（左子树）比右边（右子树）大，就会有交换。这里可以记录每一个的最大值即可。

**代码**:

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll t;
ll p[29];
int main(){
	std::ios::sync_with_stdio(false);
	cin>>t;
	p[0]=1;
	for(ll i=1;i<=25;i++) p[i]=2*p[i-1];
	while(t--){
		ll n,x,a[300009],ans=0,m[300009],f=0;
		cin>>n;
		for(ll i=1;i<=n;m[i]=a[i],i++) cin>>a[i];
        x=log2(n);
		for(ll i=1;i<=x;i++){
			for(ll j=1;j<=n/p[i];j++){
				ll v=j*p[i],u=v-p[i-1];
				if(m[u]>m[v]) ans++;
				if(abs(m[u]-m[v])!=p[i-1]||m[v]%p[i-1]) f=-1;
				m[v]=max(m[u],m[v]);
			}
		}
		if(f) cout<<-1;
		else cout<<ans;
		cout<<endl;
	}
	return 0;
}

```


---

## 作者：ImposterAnYu (赞：0)

# 解析
我们可以用归并的方式来处理每棵子树——先处理所有的小的子树，再依次处理大的。如果有一棵子树不合法（不合法指的是无法通过将这棵子树里的一些非叶子节点的子树里的叶子节点的顺序倒过来后来使得这棵子树的叶子节点为一段连续的自然数），那么就算其他的子树都合法，也没有办法满足 Masha 的要求。

```c++
int1 gui_bing(int1 l,int1 r){
	if(l == r){
		return 0;
	}
	int1 mid = (l + r) >> 1,gl = gui_bing(l,mid),gr = gui_bing(mid + 1,r);
	if(gl != -1 && gr != -1 && abs(a[mid + 1] - a[l]) <= r - l){
		return gl + gr + (a[mid + 1] < a[l]);
	}
	return -1;
}
```

（因为个人习惯，代码中的 $a$ 数组即为题目中的 $p$ 数组。）

这代码什么意思呢？我一步步来给大家分析。

首先，叶子节点本身肯定是合法的，所以当 $l = r$ 时，直接返回 $0$（在该代码中，用非负整数表示合法，$-1$ 表示不合法）。

接下来，就是把子树分成两部分，然后分别去处理。毕竟是归并嘛，肯定要先分开处理，再一起处理了。

至于接下来这个 `if`，就需要动点脑子了。因为前两个条件还比较好想，但是最后一个条件是什么意思呢？

我们可以想一想：如果一棵子树里有两个正整数，它们的差比这棵子树里的叶子节点的个数还要大，那么这棵子树合法吗？很明显是不合法的。因为无论怎么交换，都没有办法使得符合这个条件的一对叶子节点分开，到不同的子树下，自然就不能满足 Masha 的要求了。

但是为什么只用判两个子树的叶子节点里的第一个呢？因为当 $gl$ 和 $gr$ 都不为 $-1$ 时，说明这两棵子树都是合法的，所以只需要判一下第一个节点，就知道这棵大的子树合不合法了。

至于函数 `return` 的值……自然就是最小的操作次数啦（因为如果 $a_{mid + 1} < a_l$，说明现在值较大的节点反而靠后了，所以需要一次操作把大的放到后面，小的放在前面）。所以，直接在主函数里调用 `gui_bing(1,m)` 即可。

完整代码……因为太丑了，所以我就不贴啦（光速逃）~

---

## 作者：aimcf (赞：0)

线段树。

建立一个线段树，维护区间最小值和区间最大值。

然后判断是否有解：如果任意的一段长度是 $2$ 的整数幂次方区间的最大值减去最小值加上 $1$ 和这段区间的长度相等，那么就有解，否则就无解。原因：如果不这样，那么经过一些次交换操作之后，这个错误的区间仍然连续。

如果有解，那么如果两个树上的兄弟子树中，左边的子树的最小值大于右边的子树的最小值，那么需要将左边和右边两个区间交换。

时间复杂度 $O(n)\sim O(n\log n)$。

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int N = 3e5 + 10;
int a[N], n, cnt = 0;

struct Node
{
  int l, r;
  int mi, mx;
  Node()
  {
    l = r = mx = 0;
    mi = 1e18;
  }
  void init(int p)
  {
    l = r = p;
    mx = mi = a[p];
  }
} z[N << 2];

Node operator + (const Node &lhs, const Node &rhs)
{
  Node res;
  res.l = lhs.l;
  res.r = rhs.r;
  res.mi = min(lhs.mi, rhs.mi);
  res.mx = max(lhs.mx, rhs.mx);
  return res;
}

void build(int l, int r, int rt)
{
  if (l == r)
    z[rt].init(l);
  else
  {
    int mid = l + r >> 1;
    build(l, mid, rt << 1);
    build(mid + 1, r, rt << 1 | 1);
    z[rt] = z[rt << 1] + z[rt << 1 | 1];
  }
}

// true : 满足条件
// false : 不满足条件
bool dfs1(int l, int r, int rt)
{
  if (l == r)
    return false;
  int mid = l + r >> 1;
  // [l, mid]; [mid + 1, r]
  if (dfs1(l, mid, rt << 1) || dfs1(mid + 1, r, rt << 1 | 1))
    return true;
  int qmi = z[rt].mi, qmx = z[rt].mx;
  int len = r - l + 1;
  int ql = qmx - qmi + 1;
  if (ql == len)
    return false;
  return true;
}

int dfs2(int l, int r, int rt)
{
  if (l == r)
    return 0;
  else
  {
    int mid = l + r >> 1;
    int res = dfs2(l, mid, rt << 1) + dfs2(mid + 1, r, rt << 1 | 1);
    int mi1 = z[rt << 1].mi, mi2 = z[rt << 1 | 1].mi;
    if (mi1 > mi2)
      res ++;
    return res;
  }
}

signed main()
{
  int T;
  cin >> T;
  while (T --)
  {
    cnt = 0;
    cin >> n;
    for (int i = 1; i <= n; i ++)
      cin >> a[i];
    build(1, n, 1);
    if (dfs1(1, n, 1))
      cout << "-1\n";
    else
      cout << dfs2(1, n, 1) << '\n';
  }
  return 0;
}

```

[AC](https://www.luogu.com.cn/record/89658178)


---

## 作者：ChenYanlin_20 (赞：0)

### 思路：
题目只能交换子树变为漂亮二叉树。不难发现，当子树之间为 3，1，4，2 时只能交换  $ 3 \operatorname{and} 1$  或 $4 \operatorname{and} 2$ 或 $ 3,1 \operatorname{and} 4,2 $ 。2 与 1 不在同一小子树内，永远无法交换得到漂亮二分树。从叶子节点开始，不断验证交换两个子树，如果两个相邻的子树中的数字并不相接，则该树永远无法得到漂亮二叉树。
### CODE：
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=3e5+10;
int a[N];
signed main(){
//	freopen("D.in","r",stdin);
//	freopen("D.out","w",stdout);
	int t;
	cin>>t;
	while(t--){
		int m;
		cin>>m;
		for(int i=1;i<=m;i++){
			cin>>a[i];
		}
		bool flag=1;
		int cnt=0;
		for(int i=0;pow(2,i)<=m/2;i++){
			int x=pow(2,i);
			for(int j=1;j<=m;j+=x*2){
				if(abs(a[j]-a[j+x])==x){
					if(a[j]>a[j+x]){
						swap(a[j],a[j+x]);
						cnt++;
					} 
				}
				else{
//					cout<<x<<' ';
					flag=0;
					break;
				} 
			}
			if(flag==0)
				break;
		}
		if(flag==0) cout<<-1<<'\n';
		else cout<<cnt<<'\n';
	}
	return 0;
}
```

---

## 作者：RainWetPeopleStart (赞：0)

# 思路
由于本题要进行操作的对象是一棵树，所以考虑分治，但因为判断是否交换或无解只需要区间最大值和最小值（原因后面解释），则可以考虑将返回值定义为结构体，以达到返回最大值和最小值的目的。

接着考虑交换或无解的条件，不难发现，在正确的交换后，左子串的最大值小于右子串最小值，则左子串的最小值大于右子串最大值时需要交换；如果交换后左子串的最大值大于右子串最小值，则无解，在左子串的最小值小于右子串最大值和左子串的最大值大于右子串最小值时可以判定。时间复杂度为$O(n\log(n))$，不会超时。
# 代码
~~码风不好勿喷~~
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,t,a[500000],b[1000000],ans=0,l0,l1;
struct k{
	int mmax,mmin;
};
k kkk(int l,int r){
    if(l==r){
	k aa;
	aa.mmax=a[l];
	aa.mmin=a[r];
        return aa;
    }
    int mid=(l+r)/2;
    k t1=kkk(l,mid);
    k t2=kkk(mid+1,r);
    long long mmax1=t1.mmax,mmax2=t2.mmax,mmin1=t1.mmin,mmin2=t2.mmin;
    if(mmax1>mmin2&&mmin1>=mmax2&&ans!=-1){
	ans++;
	k aa;
	aa.mmax=mmax1;
	aa.mmin=mmin2;
	return aa;
    }if(mmax1>mmin2&&mmin1<mmax2){
	k aa;
    	aa.mmax=0;
	    aa.mmin=0;
        ans=-1;
	return aa;
    }
    k aa;
    aa.mmax=mmax2;
    aa.mmin=mmin1;
    return aa;
}
string g1,g2;
signed main(){
    scanf("%d",&t);
    while(t--){
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>a[i];
        	
	}
		
	int qq=1,f=0,ii=0,cnt=0;
	ans=0;
	kkk(1,n);
		
	cout<<ans<<endl;
    	
        for(int i=1;i<=n;i++){
        	a[i]=0;
        }
    }
    return 0;
}
```


---

