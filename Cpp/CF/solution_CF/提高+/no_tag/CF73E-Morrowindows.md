# Morrowindows

## 题目描述

Vasya plays The Elder Trolls III: Morrowindows. He has a huge list of items in the inventory, however, there is no limits on the size of things. Vasya does not know the total amount of items but he is sure that are not more than $ x $ and not less than $ 2 $ items in his inventory. A new patch for the game appeared to view inventory in $ n $ different modes. Displaying in mode $ i $ is a partition of all inventory items on pages, each of which (except for maybe the last one) shows exactly $ a_{i} $ items. In addition, each mode shows how many pages $ b_{i} $ is in a complete list. Great! Perhaps this information will be enough for Vasya to find the required number. Moreover, it is very interesting, what is the fewest number of modes in which Vasya can see inventory to determine the number of items in it?

Vasya cannot use the information that was received while looking on inventory in some mode for selection of next actions. I. e. Vasya chooses some set of modes first, and then sees all the results and determines the size.

Knowing the number of $ a_{i} $ , $ x $ and assuming that Vasya is very smart, check whether he can uniquely determine the number of items in his inventory, and how many modes he will need to do that if he knows numbers $ a_{i} $ , $ x $ and he is able to know number $ b_{i} $ after viewing items in mode $ i $ .

## 说明/提示

In the second example Vasya is not able to determine items count uniquely because 3 items, as well as 4 items, can be displayed on two pages.

## 样例 #1

### 输入

```
2 4
2 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
1 4
2
```

### 输出

```
-1
```

# 题解

## 作者：strlen_s_ (赞：0)

根据题目，我们可以发现以下性质：

倘若 $a$ 中有 $1$，则一定有解。

对于一个 $x$ 不为 $2$ 的情况，且 $a$ 中无 $1$，那么 $a$ 中必须要有一个 $2$，否则无法区分 $2,3$。

既然必有一个 $2$，那么当 $i$ 为奇数时，$i$ 与 $i+1$ 是无法区分的，那么 $i$ 就必须被一个选了的数整除，这样才能体现出差别。

于是可以得出结论：选了的数一定是一段以 $2$ 开头的连续的质数。

考虑归纳证明：

当 $x > 2$ 时，$2$ 这个素数必选。

假设现在选了 $k$ 个质数，现在遇到了一个最小的 $i$，使它不能被这 $k$ 个质数整除，那么它也是一个质数，且是第 $k$ 个质数后最小的一个质数。

那么最后只需要判断它们在 $a$ 中是否出现即可。因为需要 $10^5$ 个素数，所以线性筛筛 $10^7$ 以内的素数就行了。

时间复杂度：$O(V+n\log n)$。

code:

```
#include<bits/stdc++.h>
#define in inline
#define re register
//#define int long long
using namespace std;
const int N=1e5+10,M=1e7+10;
map<int,int>mp;
int n,x,a[N],cnt;
int prm[M],vis[M],tot;
void prep(){
	for(int i=2;i<=M-10;i++){
		if(!vis[i])prm[++tot]=i;
		for(int j=1;j<=tot&&prm[j]*i<=M-10;j++){
			vis[i*prm[j]]=1;
			if(i%prm[j]==0)break;
		}
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	prep();
	cin>>n>>x;
	if(x==2){
		cout<<0<<'\n';
		return 0;
	}
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]==1){
			cout<<1<<'\n';
			return 0;
		}
		mp[a[i]]=1;
	}
	if(!mp[2]){
		cout<<-1<<'\n';
		return 0;
	}
	cnt=1;
	for(;x>prm[cnt+1]&&mp[prm[cnt+1]];cnt++);
	if(x>prm[cnt+1])cout<<-1<<'\n';
	else cout<<cnt<<'\n';
	return 0;
}
```

---

## 作者：loser_seele (赞：0)

$ x=2 $ 的时候答案显然为 $ 0 $。否则如果存在 $ a_i $ 为 $ 1 $ 则答案为 $ 1 $。

我们设 $ f(x,y) $ 表示 $ \lfloor \frac{x}{y} \rfloor $，则显然 $ y $ 固定的时候 $ f(x,y) $ 有单调性，则如果 $ a<b $，且 $ f(a,y)=f(b,y) $，则显然有 $ f(a,y)=f(a+1,y) $。
则显然 $ a $ 的选取必须满足从 $ 2 $ 到 $ x-1 $ 都至少存在一个 $ a_i $ 使得其能被整除。那么 $ a $ 显然应该包含 $ [2,x-1] $ 全部的素数，否则这个素数和它 $ +1 $ 的数不能被区分。反过来，用全部的素数显然根据上面的证明可以区分出所有数。

于是筛出所有素数之后判断是否至少出现一次即可。但观察到 $ x $ 很大，这样不能通过。

但是因为 $ x $ 以内的素数级别是 $ \frac{x}{\ln{x}} $ 级别的，打表可以发现 $ x > 2 \times 10^7 $ 的时候素数个数已经超过 $ n $，显然无解。于是筛到 $ 2 \times 10^7 $ 即可。

时间复杂度上面已经分析了，瓶颈在筛子的实现。

代码：

```cpp
#import <bits/stdc++.h>
using namespace std;
const int maxn=2e7+20;
int prime[maxn],a[maxn];
bool vis[maxn];
int tot=0;
void pre(int n) 
{
	for (int i=2;i<n;i++) 
	{
		if(!vis[i])
		    prime[tot++]=i;
		for (int j=0;j<tot;++j) 
		{
			if(i*prime[j]>n)
			    break;
			vis[i*prime[j]]=1;
			if(i%prime[j]==0)
			    break;
		}
	}
}
inline int read() 
{
	int x=0,f=1;
	char ch=getchar();
	while (ch<'0'||ch>'9') 
	{
		if (ch=='-') f=-1;
		ch=getchar();
	}
	while (ch>='0'&&ch<='9') 
	{
		x=x*10+ch-48;
		ch=getchar();
	}
	return x*f;
}
unordered_map<int,int>p;
signed main() 
{
	int n=read(),x=read();
	pre(2e7);
	if(x==2) 
	{
		puts("0");
		return 0;
	} 
	else 
	{
		for (int i=1;i<=n;i++)
		a[i]=read(),p[a[i]]++;
		if(p[1]) 
		{
			puts("1");
			return 0;
		} 
		else if(x>20*n) 
		{
			puts("-1");
			return 0;
		} 
		else 
		{
			bool ok=1;
			int ans=0;
			for (int i=0;i<tot;i++)
			if(prime[i]>=x)
			break; 
			else if(!p[prime[i]])
			ok=0; 
			else
			ans++;
			if(!ok)
			cout<<-1; 
			else
			cout<<ans;
		}
	}
}
```


---

