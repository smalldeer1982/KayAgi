# Make a Permutation!

## 题目描述

### 题目大意

给出含有 $n$ 个数的序列，每个数的范围是 $1\sim n$。请你改变其中的一些数使这个序列成为一个 $1\sim n$ 的全排列，若有多种变化方案，取改变次数最少且字典序最小的方案。

## 样例 #1

### 输入

```
4
3 2 2 3
```

### 输出

```
2
1 2 4 3 
```

## 样例 #2

### 输入

```
6
4 5 6 3 2 1
```

### 输出

```
0
4 5 6 3 2 1 
```

## 样例 #3

### 输入

```
10
6 8 4 6 7 1 6 3 4 5
```

### 输出

```
3
2 8 4 6 7 1 9 3 10 5 
```

# 题解

## 作者：风中の菜鸡 (赞：3)

题意简化

给你一个数列，问你把这个数列改成全排列需要的操作次数和操作后的数列，且此时的序列在所有只进行了同样次数的合法序列中字典序最优。

思路

将要改的打上标记，再把缺失的用一个数组存起来，一个一个改即可。需要注意的是，为保证字典序最小，我们需要在操作次数最少的情况下，把越前面的数字改成一个比它小且在所有能改成的数字中最小的值。因此我们需要一个 $bj$ 数组，来标记本应该改，但因为字典序不是最小而没改的数，在下一次碰到这个数时，就必须改它了。

代码

思路看起来可能有点抽象，但代码还是比较好理解的。（有详细注释）

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,numcl,ans;
int a[200001],vis[200001],cl[200001],bj[200001];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		vis[a[i]]++;//出现次数 
	}
	for(int i=1;i<=n;i++){
		if(vis[i]==0){
			cl[++numcl]=i;//需要添加进原数列里的数 
		}
	}	
	int now=1;//先加小的（保证字典序最优） 
	for(int i=1;i<=n;i++){
	//	cout<<vis[a[i]]<<' ';
		if((vis[a[i]]>1&&a[i]>cl[now])||(vis[a[i]]>1&&bj[a[i]]==1)){//需要更改 上一个没被更改或字典序最优 
			vis[a[i]]--;//出现次数减一 
			a[i]=cl[now];//更改 
			now++;//指针右移 
			ans++;	//操作次数加一 
		}
		if(vis[a[i]]>1&&a[i]<cl[now]){//字典序不一定最优且要被更改 
			bj[a[i]]=1;//打上标记 
		}
	} 
	cout<<ans<<endl;
	for(int i=1;i<=n;i++){
		cout<<a[i]<<' ';
	}
	return 0;
} 
```


---

## 作者：Soshine_溯闪 (赞：1)

我 **第十次** 传题解。    
马上要到我生日了，预祝我生快！
# 整体思路
1. 数组含义    
$vis[i]$  代表是 $i$ 出现的次数。    
$v[i]$ 代表的是处理到现在，仍没出现过的数。     
$t[i]$ 代表的是处理到现在 $i$ 出现次数，前提示 $i$ 没有改变。    
2. 重点部分处理（程序 26 到 37 行）    
**提前说些东西：**  
按字典序最小的全排列是 1 2 3 4 …… n-1 n ,规律是 $a[i]=i$  。   
**正题**    
如果这个数出现了至少两次（ $vis[i]>1$ )那么这个数就要来处理了      
如果 $t[i]$  ≥ 1，那么这个数无论如何都要改变。     
如果这个数减它所在的 $i$ 大于等于能用的数减 $i$ ,那么变比没变好。   
**why？**    
因为前面说过最小的全排列的一种方法，$a[i]=i$,也就是这个数最好等于这个数的位置，那么两者取差值越 **接近0** 越好，所以明白了吧。
# 思考思考，上程序
```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <cmath>
#include <cstdio>
#include <queue>
#include <map>
#include <iomanip>
using namespace std;
const int maxn=200005;
int n,a[maxn],vis[maxn],ans,v[maxn],num=1,t[maxn];		//定义，不多说 
int main(){
	cin>>n;		//输入 
	for(int i=1;i<=n;i++) {
		cin>>a[i];
		vis[a[i]]++;		//初始化vis数组 
	}	
	for(int i=1;i<=n;i++) 
		if(vis[i]==0) {		//如果没出现过 
			v[num]=i;		//存进v数组 
			num++;		//下标往后移 
		}
	num=1;		//重置v数组下标 
	//重点 
	for(int i=1;i<=n;i++){
		if(vis[a[i]]>1){		//需要处理 
			if((a[i]-i)>=(v[num]-i)||t[a[i]]>=1){		//需要改变 
				vis[a[i]]--;		//这个数的出现次数减1 
				a[i]=v[num];		//将改变的数存进a数组 
				vis[v[num]]++;		//这个数的出现次数加1 
				num++;		//下标后移 
				ans++;		//需要改变数加1 
			}
			t[a[i]]++;		//t数组加1 
		} 
	}
	cout<<ans<<endl;		 
	for(int i=1;i<=n;i++) cout<<a[i]<<" ";		//输出 
	return 0;		//AC 
}
```
跪求管理员给过，谢谢！

---

## 作者：Graphcity (赞：1)

翻译里面没有说的一点是输出的序列要在保证修改次数最少的时候 **字典序最小** 。

我们可以先开一个 `vis` 数组统计哪些数没有在原序列里面出现过，如果没有出现就把它放在一个 vector 中。由于我们可以按大小顺序查找，vector 中为了保证字典序最小的排序操作其实可以省略。

需要修改的次数就是 vector 的大小。

接着，修改数组的时候，分三种情况讨论：

- 这个数在原序列中出现的次数超过了两次

1. 如果当前 vector 里面的数字比这个数大，没必要替换，直接输出。

2. 如果小一些，为了使得字典序最小，就需要替换了。注意要把 `vis` 数组中这个数字的出现次数 -1 。

- 这个数已经在新序列中出现过了

我们可以用 `res` 数组标记每个数在新序列中出现的次数。全排列中每个数字出现的次数只有一次，直接替换。

- 其它情况

不用替换，直接输出即可。记得要把 `res` 数组中它的值加上 1.

总时间复杂度 $O(n)$ 。

**Code**:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int Maxn=int(2e5);

int n,tot,a[Maxn+5];
int vis[Maxn+5],res[Maxn+5];
vector<int> v;

int main()
{
	scanf("%d",&n);
	for(register int i=1;i<=n;++i)
	{
		scanf("%d",&a[i]);
		vis[a[i]]++;
	}
	for(register int i=1;i<=n;++i)
		if(!vis[i]) v.push_back(i);
	printf("%d\n",v.size());
	//sort(v.begin(),v.end());
	for(register int i=1;i<=n;++i)
	{
		if(vis[a[i]]>1 && v[tot]<a[i])
		{
			printf("%d ",v[tot]);
			tot++,vis[a[i]]--;
		}
		else if(res[a[i]])
		{
			printf("%d ",v[tot]);
			++tot;
		}
		else
		{
			res[a[i]]++;
			printf("%d ",a[i]);
		}
	}
	return 0;
}
```

---

## 作者：Φρανκ (赞：0)

题意：给定 $a_1\sim a_n$ 满足 $1\le a_i\le n$，求至少更改几个数可以达到全排列，以及这样修改后可能得到的全排列中字典序最小者。

核心思想：贪心

解：

令 $f(i)$ 表示 $i$ 出现的次数，则从左到右依次访问每个数，若出现次数大于 $1$ 则可以用最小的小于它的未出现过的数替代之。若没有这样的数，可以记录对应的 $g(i)=1$，这样下次遇到就必须修改。

代码：
```
#include <bits/stdc++.h>
using namespace std;
long long n, a[200001], b[200001], c[200001], flag=1, res;
int main()
{
	cin>>n;
	for(int i=1; i<=n; i++)
	{
		cin>>a[i];
		b[a[i]]++;
	}
	for(int i=1; i<=n; i++)
	{
		while(b[flag]!=0)
			flag++;//查询下一个未出现过的数
		if(b[a[i]]>1)
			if(flag<a[i] || c[a[i]]==1)//满足条件的数存在或者必须修改
			{
				b[a[i]]--;
				b[flag]++;
				a[i]=flag;
				res++;//修改
			}
			else
				c[a[i]]=1;//修改g
	}
	cout<<res<<endl;
	for(int i=1; i<=n; i++)
		cout<<a[i]<<" ";
	return 0;
}
```

---

## 作者：xin700 (赞：0)

这个题目我们的首先一定会想到我们要使这个序列不重不漏。

那么我们就可以**使用一个 $q$ 数组来记录哪些数字我们还没有填入**

但是我们的难题就在如何保证**字典序最小**

这个我们可以考虑在替换的时候，比较一下 $q$ 数组在当前指针的值和当前序列的值。

如果 $q$ 数组的值比较小，那么替换，否则我们要记录下来新序列当中的每个数字出现的次数。

如果已经出现过了，那么我们就一定要替换了。
```cpp
#include<bits/stdc++.h>
using std::cout; using std::endl;
#define try(i,a,b) for(register signed i=a;i<=b;++i)
#define throw(i,a,b) for(register signed i=a;i>=b;--i)
#define go(i,x) for(register signed i=head[x],y=edge[i].ver;i;i=edge[i].next,y=edge[i].ver)
namespace xin_io
{
	#define file(a) FILE *FI = freopen(#a".in","r",stdin); FI = freopen(#a".out","w",stdout)
	#define sb(x) cout<<#x" = "<<x<<' '
	#define jb(x) cout<<#x" = "<<x<<endl
	#define debug cout<<"debug"<<endl
	#define gc() p1 == p2 and (p2 = (p1 = buf) + fread(buf,1,1<<20,stdin),p1 == p2) ? EOF : *p1++
	#define scanf ak = scanf
	char buf[1<<20],*p1 = buf,*p2 = buf; int ak; typedef long long ll; typedef unsigned long long ull;
	class xin_stream{public:template<typename type>inline xin_stream &operator >> (type &s)
	{
		register int f = 0;s = 0; register char ch = gc();
		while(!isdigit(ch)) {f |= ch == '-'; ch = gc();}
		while( isdigit(ch)) s = (s << 1) + (s << 3) + (ch  xor 48),ch = gc(); return s = f ? -s : s,*this;
	}}io;
}
using namespace xin_io;static const int maxn = 1e6+10,inf = 1e9+7;const ll llinf = 1e18+7;
#define int long long
auto max = [](int x,int y) -> int{return x > y ? x : y;}; auto min = [](int x,int y) -> int{return x < y ? x : y;};
namespace xin
{
	int n;
	int a[maxn],vis[maxn],app[maxn];
	int q[maxn],zhi = 0;
	int ans = 0;
	inline short main()
	{
		io >> n;
		try(i,1,n) io >> a[i],vis[a[i]]++;
		try(i,1,n) if(!vis[i]) q[++zhi] = i;
		zhi = 1;
		try(i,1,n) 
		if(vis[a[i]] > 1 and a[i] > q[zhi])
		{
			vis[a[i]] --;
			ans ++;
			a[i] = q[zhi++];
		}
		else if(app[a[i]])
			a[i] = q[zhi++],ans++;
		else app[a[i]]++;
		printf("%lld\n",ans);
		try(i,1,n) printf("%lld ",a[i]);
		return 0;
	}
}
signed main() {return xin::main();}
```

---

