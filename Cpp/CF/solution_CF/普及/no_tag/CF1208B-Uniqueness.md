# Uniqueness

## 题目描述

给你一个n(1≤n≤2000)个数的序列A1,A2...An(1≤Ai≤1e9)，我们要删除一个子串，使得数列中余下的数两两不重复，问删除字串的最短长度。

## 样例 #1

### 输入

```
3
1 2 3
```

### 输出

```
0
```

## 样例 #2

### 输入

```
4
1 1 2 2
```

### 输出

```
2
```

## 样例 #3

### 输入

```
5
1 4 1 4 9
```

### 输出

```
2
```

# 题解

## 作者：Awdrgysxc (赞：3)

[Manthan, Codefest 19 (open for everyone, rated, Div. 1 + Div. 2)A-F](https://blog.csdn.net/zyn_615/article/details/100185305)
## 【Analysis】
就是把一个序列分成首尾两段，而且没有重复的数字；可以$TwoPointers$,详见$Code$
总复杂度$O(NlogN)$

## 【Code】
```cpp
const int M = 2019;
 
int A[M];
 
int n, l, r, ans;
 
std::set <int> s;
 
int main(void)
{
	n = read();
	for (int i = 1;i <= n; ++i)
		A[i] = read();
	ans = n, r = n + 1;
	while (r >= 2 && !s.count(A[r - 1]))
		s.insert(A[--r]);
	for (l = 1;r <= n + 1; ++r)
	{
		while (!s.count(A[l]))
			s.insert(A[l++]);
		ans = std::min(ans, r - l);
		if (ans == 0) break;
		s.erase(A[r]);
	} print(ans), printc('\n'); output(); return 0;
}
```

---

## 作者：世末OIer (赞：3)

读+想+写6分钟一边过，手速、、

---

```cpp
#include<bits/stdc++.h>
#define ll long long
#define mp make_pair
using namespace std;
int n,x,y;
int a[100005];
map<int,int>use;
int main(){
	cin>>n;
	for(int i=1;i<=n;++i)cin>>a[i];
	int ans=512345;   //赋上最大值
	for(int i=1;i<=n;++i){             //设删除的是i-j这一段
		use.clear();  //清空离散
		for(int j=1;j<i;++j){
			if(use[a[j]])goto ed;  //前面的都用了，有重复的就不可取
			use[a[j]]=1;
		}
		for(int j=n;j>=i-1;--j){
			ans=min(ans,j-i+1);  //不断取min
			if(j==i-1)break;
			if(use[a[j]])break;  //用过了，这个数必须删除
			use[a[j]]=1;
		}
		ed:;
	}
	cout<<ans<<endl;
}
```

---

## 作者：foreverlasting (赞：1)

[推销博客](https://foreverlasting1202.github.io/2019/08/27/CF1208%E9%A2%98%E8%A7%A3/)

### B Uniqueness

题意：给一个长度为$n$的序列，最多可以去掉一个区间$[l,r]$，需要去掉之后满足每个数只出现一次，求$r-l+1$的最小值。$1\leq n\leq 2000,1\leq a_i\leq 10^9$

做法：枚举左端点，单调扫过右端点，用$map$维护一下一个数的出现次数，为$1$就合法，复杂度$O(n^2logn)$。

code:
```cpp
//2019.8.24 by ljz
//email 573902690@qq.com
//if you find any bug in my code
//please tell me
#include<bits/stdc++.h>
using namespace std;
#define res register int
#define LL long long
#define inf 0x3f3f3f3f
#define INF 0x3f3f3f3f3f3f3f
#define unl __int128
#define eps 5.6e-8
#define RG register
#define db double
#define pc(x) __builtin_popcount(x)
typedef pair<int,int> Pair;
#define mp make_pair
#define fi first
#define se second
#define pi acos(-1.0)
#define pb push_back
#define ull unsigned LL
#define gc getchar
//inline char gc() {
//    static char buf[100000],*p1,*p2;
//    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
//}
inline int read() {
    res s=0,ch=gc();
    while(ch<'0'||ch>'9')ch=gc();
    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=gc();
    return s;
}
//inline int read() {
//    res s=0,ch=gc(),w=1;
//    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=gc();}
//   while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=gc();
//    return s*w;
//}
//inline LL Read() {
//    RG LL s=0;
//    res ch=gc();
//    while(ch<'0'||ch>'9')ch=gc();
//    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=gc();
//    return s;
//}
//inline LL Read() {
//    RG LL s=0;
//    res ch=gc(),w=1;
//    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=gc();}
//    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=gc();
//    return s*w;
//}
//inline void write(RG unl x){
//    if(x>10)write(x/10);
//    putchar(int(x%10)+'0');
//}
inline void swap(res &x,res &y) {
    x^=y^=x^=y;
}
//mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
//clock_t start=clock();
//inline void ck(){
//    if(1.0*(clock()-start)/CLOCKS_PER_SEC>0.1)exit(0);
//}
const int N=2e3+10;
namespace MAIN{
    int n;
    int a[N];
    map<int,int> buc,vis;
    int ans=inf;
    inline void MAIN(){
        n=read();
        for(res i=1;i<=n;i++)a[i]=read();
        for(res l=1;l<=n;l++){
            res ret=0;
            for(res i=1;i<=n;i++)buc[a[i]]=vis[a[i]]=0;
            for(res i=1;i<=n;i++)buc[a[i]]++;
            for(res i=1;i<=n;i++)if(buc[a[i]]>=2&&!vis[a[i]])ret++,vis[a[i]]=1;
//            printf("%d\n",ret);
            if(!ret){puts("0");return;}
            for(res r=l;r<=n;r++){
                buc[a[r]]--;
                if(buc[a[r]]==1)ret--;
                if(!ret){ans=min(ans,r-l+1);break;}
            }
        }
        printf("%d\n",ans);
    }
}
int main(){
//    srand(19260817);
//    freopen("signin.in","r",stdin);
//    freopen("signin.out","w",stdout);
    MAIN::MAIN();
    return 0;
}
```

---

## 作者：引领天下 (赞：1)

这个题实际上可以two-pointers或者二分答案

很明显，后者好写一些。

于是我们二分删掉的区间长度，枚举区间开始的端点，再$O(n)$判断。

5min写出了下面的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[2005],l,r,mid,ans=1<<30;
map<int,bool> mp;
bool flag;
inline bool check(int d){
    for (int i=1;i<=n;i++){
        flag=1;
        mp.clear();
        for (int j=1;j<i;j++)if(mp[a[j]])flag=0;
        else mp[a[j]]=1;
        for (int j=i+d;j<=n;j++)if(mp[a[j]])flag=0;
        else mp[a[j]]=1;
        if(flag)return true;
    }
    return false;
}
int main(){
    scanf("%d",&n);
    for (int i=1;i<=n;i++)scanf("%d",&a[i]);r=n-1;
    while(l<=r){
        mid=(l+r)>>1;
        if(check(mid))ans=min(ans,mid),r=mid-1;
        else l=mid+1;
    }
    printf("%d\n",ans);
}
```

我使用了map判重，然后输入输出也没有注意，所以#10T了。

那么怎么优化呢？

我们发现效率瓶颈是map，然而我们数字的个数不多，实际上离散化一下完全可以桶解决。

于是有了离散化的代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N =2005;
int n,a[N],sum[N][N],tot,l,r,mid;
struct Node{
	int id,val;
    inline bool operator < (const Node&p)const{return val<p.val;}
}num[N];
bool flag;
inline bool check(int d){
	for (int l=1;l+d-1<=n;l++){
        flag=1;
		int r=l+d-1;
		for(int j=1;j<=n&&flag;j++)if(sum[n][j]-sum[r][j]+sum[l-1][j]>1)flag=0;//利用前缀和优化判断
		if(flag)return true;
	}
	return false;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>num[i].val,num[i].id=i;
	sort(num+1,num+1+n);//离散化
	num[0].val=-1;
	for(int i=1;i<=n;i++)if(num[i].val!=num[i-1].val)a[num[i].id]=++tot;
	else a[num[i].id]=tot;
	for(int i=1;i<=n;i++){
	    for(int j=1;j<=n;j++)sum[i][j]=sum[i-1][j];
		sum[i][a[i]]++;
	}
    r=n;
	while(l<=r){
		mid=(l+r)>>1;
		if(check(mid))r=mid-1;
		else l=mid+1;//二分
	}
	cout<<l<<endl;
	return 0;
}
```

---

## 作者：YFF1 (赞：0)

## 思路：
注意到数据范围很小，直接暴力枚举左右端点。枚举左端点时维护一下左端点前面的所有数都要是不重复的，右端点是在确定左端点的情况下枚举从后往前第一个重复的位置。详情见代码。
## 代码：
```
#include<bits/stdc++.h>
using namespace std;
int n,a[20005],num,k,ans=1e9;
map<int,int>mp;
int main () {
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++){
		if(mp[a[i]]!=0){
			num=i;//找左端点枚举范围 
			break;
		}
		mp[a[i]]++;
	}
	mp.clear();
	for(int i=1;i<=num;i++){
		for(int j=1;j<i;j++)mp[a[j]]++;//左端点前面的数 
		for(int j=n;j>=i;j--){
			if(mp[a[j]]!=0){
				k=j;//找右端点 
				break;
			}
			mp[a[j]]++;
		}
		ans=min(ans,k-i+1);//找长度 
		mp.clear();
	}
	if(ans==1e9)cout<<0;
	else cout<<ans;
	return 0;
} 
```

---

## 作者：Peaky (赞：0)

按照惯例，应该先有[传送门](https://www.luogu.com.cn/problem/CF1208B)。
### 题目大意
在原数组中删除一串数，使得删除后的数组任意两个元素都不相同。求删除的数长度最短是多少。
### 思路
我们设长度为 $ans$ 时可以满足条件，那么 $ans+1$ 也满足条件，于是就有了单调性，本题可以二分答案。  
那么如何判断这个长度是否满足长度呢？我们最优的情况肯定是把多余的数全部框起来，滑动这个框判断是否满足。这就是滑动窗口的思想，于是问题就迎刃而解了。
### AC code
```cpp
#include<bits/stdc++.h>
#define x first
#define y second
using namespace std;
const int N=2e5+10,inf=0x3f3f3f3f,mod=1e9+7;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef long long ll;
/*

*/
int n,a[N],cnt;
map<int,int> t,ck;
bool check(int x){
	int c=0;
	for(int i=1;i<=n;i++) ck[a[i]]=0;
	for(int i=1;i<x;i++){
		ck[a[i]]++;
		if(t[a[i]]>1&&ck[a[i]]<t[a[i]]) c++;
	}
	for(int i=x;i<=n;i++){
		ck[a[i]]++;
		if(t[a[i]]>1&&ck[a[i]]<t[a[i]]) c++;
		if(c==cnt) return 1;
		if(ck[a[i-x+1]]!=t[a[i-x+1]]) c--;
		ck[a[i-x+1]]--;
	}
	return 0;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i],t[a[i]]++;
		if(t[a[i]]>=2) cnt++;
	}
	if(!cnt) return cout<<0,0;
	int l=1,r=n,ans=n;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid)) ans=mid,r=mid-1;
		else l=mid+1;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：HUANGRUI11 (赞：0)

题目意思很简单，其实就是去掉其中一个区间。
### 方法一

读完题之后立马就想到了用 map 桶记一下，

再加二分答案删去区间的长度，循环找一下左端点

时间复杂度 
$O(n^2\log n)$。 绝对过了~~
 
###  方法二
或者考虑一下双指针 (可能比较难写）。

先从开头搜索一个没有重复数字的区间。

然后再从末尾搜索也没有重复数字的区间。

注意这两个区间之间也不能有重复
所以用 map 桶一下会比较方便

时间复杂度 $O(n \log n) $。

代码不展示。

---

## 作者：Big_Dinosaur (赞：0)

比较暴力的一种做法。

双重循环，先枚举左端点 $i$，直到 $[1,i]$ 中有重复元素位置。

对于每一个 $i$，从大到小枚举 $j$，直到 $[1,i]$ 与 $[j,n]$ 之间有重复元素或 $[j,n]$ 本身就有重复元素。计算长度，取最小值。

### 注意事项
考虑删除的区间左端点为 $1$ 或右端点为 $n$。代码为了避免这种情况，左端点从 $0$ 开始枚举，右端点从 $n+1$ 开始枚举。同时将 $a_0$ 设为 $0$，将 $a_{n+1}$ 设为 $-1$。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
namespace io {
	inline int r() {
		char Z=getchar();int Y=1,T=0;
		while(Z<'0'||Z>'9') {if(Z=='-')Y=-1;Z=getchar();}
		while(Z<='9'&&Z>='0') {T=(T<<1)+(T<<3)+(Z^48);Z=getchar();}
		return T*Y;
	}
	inline void PR(int Y) {
		if(Y<0) {putchar('-');Y=-Y;}
		if(Y==0)return;
		PR(Y/10);putchar(48+Y%10);
	}
	inline void wln(int A) {if(A==0)putchar('0');else PR(A);putchar('\n');}
	inline void ww(int A) {if(A==0)putchar('0');else PR(A);putchar(' ');}
	inline void w(int A) {if(A==0)putchar('0');else PR(A);}
}
using namespace io;
namespace dIn0 {
	int n,a[114514],mi=1919810;
	map<int,int>mp1,mp2;
	inline void _() {
		n=r();
		for(int i=1; i<=n; ++i)a[i]=r();
		a[n+1]=-1;
		for(int i=0,j; i<=n; ++i) {
			mp2.clear();
			++mp1[a[i]];
			if(mp1[a[i]]==2)break;
			for(j=n+1; j>i; --j) {
				++mp2[a[j]];if(mp1[a[j]]||mp2[a[j]]==2)break;
			}
			mi=min(mi,j-i);
		}
		wln(mi);
	}
}
signed main() {
	dIn0::_();
}
```

---

## 作者：Erotate (赞：0)

### Solution

我的思路是用二分 + 桶来解决。但是看到 $1\leq a_i \leq 10^9$ 的数据范围，首先就要先写一个离散化：

```cpp
for(int i=1;i<=n;++i){
   scanf("%lld",&a[i]);
   b[i]=a[i];
}
sort(b+1,b+n+1);
int len=unique(b+1,b+n+1)-b-1;
for(int i=1;i<=n;++i) a[i]=lower_bound(b+1,b+len+1,a[i])-b;
```

然后来一个特判，如果剩下的数字本来就没有重复，那就输出 $0$：

```cpp
//这里 cnt 数组是桶
for(int i=1;i<=n;++i) cnt[a[i]]++;
int flag=0;
for(int i=1;i<=n;++i)
   if(cnt[i]>1){
     flag=1;
     break;
   }
if(!flag){
  printf("0");
  return 0;
}
```

接下来我们枚举左端点，再二分答案要删除的序列的长度：

```cpp
for(int i=1;i<=n;++i){
   int l=1,r=n-i+1,ans=114514;
   while(l<=r){
     int mid=l+r>>1;
     if(check(i,mid)){//表示从第 i 个数开始，向后删除 mid 个数。
       	r=mid-1;
       	ans=mid;
     }else l=mid+1;
   }
   st=min(lst,ans);//lst 记录下最终答案
}
```

然后 check 函数里要从新开一个桶，每次将初始时每种数字出现的次数（即上文提到的 $cnt$ 数组）赋值过去。然后执行删除操作，删除之后在判断每一个数是否有重复：

```cpp
//tmp 为新的桶 
bool check(int st,int x){
   for(int i=1;i<=n;++i) tmp[i]=cnt[i];
   for(int i=st;i<=st+x-1;++i) tmp[a[i]]--;
   for(int i=1;i<=n;++i)
      if(tmp[i]>1) return 0;
    return 1;
}
```

时间复杂度 $O(n^2 log n)$，可以通过。

---

## 作者：Gogococoyoyo (赞：0)

转换一下题意：

最小化删除的区间(l,r) <==> 最大化选取的区间(1,l-1)(r+1,n)长度之和

枚举左右端点即可 因为a的大小所以需要离散化一下再存入记录数组中

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,sum;
bool used[2005];

struct node{
	int num,val;
};
node a[2005];

bool cmp1(node p,node q){
	return p.val<q.val;
}

bool cmp2(node p,node q){
	return p.num<q.num;
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d",&a[i].val);
		a[i].num=i;
	}
	//离散化
	sort(a+1,a+n+1,cmp1);
	int cnt=0;
	for(int i=1;i<=n;++i){
		++cnt;
		while(a[i].val==a[i+1].val){
			a[i].val=cnt;
			++i;
		}
		a[i].val=cnt;
	}
	sort(a+1,a+n+1,cmp2);
	//枚举左端点
	for(int l=0;l<=n;++l){
		if(used[a[l].val])
			break;
		used[a[l].val]=true;
		//枚举右端点
		int r=n+1;
		while(l<r){
			--r;
			if(used[a[r].val])
				break;
			used[a[r].val]=true;
		}
		sum=max(sum,l+n-r);
		//清除枚举右端点时打的标记
		for(int i=r+1;i<=n;++i)
			used[a[i].val]=false;
	}
	printf("%d\n",n-sum);
}
```

---

## 作者：兮水XiShui丶 (赞：0)


显然可以发现这个区间长度满足单调性(设$len1>len2$,那么如果$len2$满足条件,$len1$一定满足条件.).所以我们可以考虑二分答案.   
我们设$buck[i][j]$数组来表示前$i$个数中,$j$这个数字出现了多少次(就是一个前缀和).但是这样的话我们会发现数据的权值是$10^9$范围的,直接开一个桶会挂掉(开$map$会$TLE$,,,不要问我咋知道的),所以我们考虑先对数据离散化.然后对于每一次二分,我们可以$O(n)$枚举区间,然后枚举权值,对于每个枚举的区间可以$O(n)$check每种权值,总复杂度为$O(n^2log_2n)$  

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N =2005;
int n;
int num[N];
struct Node{
	int pos;
	int val;
}lisanhua[N];
inline bool cmp(Node x,Node y){
	return x.val < y.val;
}
int buck[N][N];
inline bool check(int len){
	bool flag=1;
	for (int l=1;l+len-1<=n;l++){
		int r=l+len-1;
		bool ff=1;
		for(int j=1;j<=n;j++){
			if(buck[n][j]-buck[r][j]+buck[l-1][j] > 1){
				ff=0;
				break;
			}
		}
		if(ff)
			return true;
	}
	return false;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>lisanhua[i].val;
		lisanhua[i].pos=i;
	}
	sort(lisanhua+1,lisanhua+1+n,cmp);
	int idx=0;
	lisanhua[0].val=-1;
	for(int i=1;i<=n;i++){
		if(lisanhua[i].val != lisanhua[i-1].val)
			num[lisanhua[i].pos]=++idx;
		else
			num[lisanhua[i].pos]=idx;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)
			buck[i][j]=buck[i-1][j];
		buck[i][num[i]]++;
	}
	int l=0,r=n;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid))
			r=mid-1;
		else
			l=mid+1;
	}
	cout<<l<<endl;
	return 0;
}
```  


---

## 作者：弦巻こころ (赞：0)

题目大意是给你 一个 有n个数的序列$a_1$,$a_2$……$a_n$,然后 让你删去最少的连续的序列,使得这个剩下的序列没有重复的数字

其实思路还是挺好想的.二分答案枚举删去区间长度,再$O(n)$ check 一下 就完了.

check 就 开一个桶记录一下有每个数值有多少个数.然后每次 check的时候就将桶减去删去的数值.然后还要记得还原

但发现了一个问题 $a_i$<=$10^9$ 桶开不下

所以如果我们要实现check的话 就必须要离散化一下,所以还需要再打一个离散化.

细节详见代码

```cpp
#include<bits/stdc++.h>
using namespace std;
struct fh
{
	long long x,s;
	int ls;
}a[5005];
int n;
int num[2005];
int tot=1;
int ans;
bool cmp1(fh a,fh b)
{
	return a.x<b.x;
}
bool cmp2(fh a,fh b)
{
	return a.ls<b.ls;
}
bool check(int len)
{
	bool pd=0;
	for(int i=1;i<=n-len+1;i++)
	{
		pd=0;
		for(int j=i;j<=i+len-1;j++)//删去数列
		{
			num[a[j].s]--;
		}
		for(int j=1;j<=tot;j++)//如果还有重复就不合法
		{
			if(num[j]>=2)
			{
				pd=1;
				break;
			}
		}
		for(int j=i;j<=i+len-1;j++)//还原
		{
			num[a[j].s]++;
		}
		if(pd==0)//如果没有重复了
		{
			return 1;
		}
	}
	return 0;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i].x);
		a[i].ls=i;
	}
	sort(a+1,a+n+1,cmp1);
	a[1].s=1;
	num[1]=1;
	for(int i=2;i<=n;i++)//离散化
	{
		if(a[i].x!=a[i-1].x)
		{
			a[i].s=++tot;
			num[a[i].s]++;
		}else
		{
			a[i].s=a[i-1].s;
			num[a[i].s]++;
		}
	}
	sort(a+1,a+n+1,cmp2);//记得还原原顺序
	int l=0,r=n,mid;
	while(l<r)//二分答案
	{
		mid=(l+r)>>1;
		if(check(mid)==1)
		{
			r=mid;
		}else
		{
			l=mid+1;
		}
	}
	cout<<l;
	return 0;
}
```


---

