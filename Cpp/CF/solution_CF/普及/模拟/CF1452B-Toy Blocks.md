# Toy Blocks

## 题目描述

你被叫去照看你的一个喜欢以一种奇怪方法玩积木的侄子。

你的侄子有 $n$ 个盒子，第 $i$ 个盒子中有 $a_i$ 个积木。他的游戏由两步组成：

1. 随机选择一个盒子 $i$ ；

2. 将第 $i$ 个盒子中的所有积木转移到其他盒子中。

两步操作后，如果他可以使其他 $n-1$ 个盒子中积木的数量相同，他就会高兴，否则他将伤心。注意：你的侄子只能将积木从被选中的盒子中转移到其他盒子；他不能从其他盒子中移动积木。你不想让你的侄子伤心，所以你打算在一些盒子中额外放几个积木，使得不论你的侄子选择任何盒子，他都不会伤心。求出最少额外放入的积木数。

## 说明/提示

在第一个测试点中，你可以在第一个盒子中放 $1$ 个积木。

在第二个测试点中，你不需要放积木。

在第三个测试点中，你可以在第一个盒子中放 $2$ 个积木，在第三个盒子中放 $1$ 个积木。

## 样例 #1

### 输入

```
3
3
3 2 2
4
2 2 3 2
3
0 3 0```

### 输出

```
1
0
3```

# 题解

## 作者：Qiiiiiii_ (赞：6)

观察样例，首先得到一个结论，所有数的总和必须是 $n-1$ 的倍数，这是本题的第一个限制条件。接下来考虑第二个限制条件，我们如何让每个数达到相同，思考极端情况，最麻烦的情况，就是还剩一个最大值的情况，即，我们至少要将其他数全部变为这个最大值，而一旦满足这个条件，其他条件都非常好实现。因此，我们取满足这两个条件的最小值即可。

```cpp
#include<bits/stdc++.h>
#define re register
#define ll long long
#define LL inline ll
#define I inline int
#define V inline void
#define B inline bool
#define FOR(i,a,b) for(re int i=(a),i##i=(b);i<=i##i;++i)
#define ROF(i,a,b) for(re int i=(a),i##i=(b);i>=i##i;--i)
#define gc getchar()
using namespace std;
const int N=1e5+10;
LL read(){
	ll p=0; bool w=0; char ch=gc;
	while(!isdigit(ch)) w=ch=='-'?1:0,ch=gc;
	while(isdigit(ch)) p=p*10+ch-'0',ch=gc;
	return w?-p:p;
}
int T,n;
ll ans,mx,a[N],sum;
int main(){
	T=read();
	while(T--){
		n=read(),mx=0,sum=0;
		FOR(i,1,n) a[i]=read(),sum+=a[i],mx=max(mx,a[i]);
		if(sum%(n-1)) ans=(sum/(n-1)+1)*(n-1);
		else ans=sum;
		ans=max(ans,mx*(n-1));
		cout<<ans-sum<<endl;
	}
	
	return 0;
}
 
```


---

## 作者：WitheredZeal (赞：2)



# 题意  
你有$n$个盒子，第$i$个盒子里有$a_i$个积木，你需要给每个盒子里加上一些积木，使得：  
任意取一个盒子，都可以把这里面的积木拿出来，然后分到其他的几个盒子里，使其他几个盒子中的积木数量一样。  

# 题解  
考虑最后的情况，有设最后情况的数组为$\{A_i\}$  
令
$$sum=\sum_{i=1}^na_i,Sum=\sum_{i=1}^nA_i,A_{max}=\max_{i=1}^nA_i,a_{max}=\max_{i=1}^na_i$$  
那么有
$$Sum=(n-1)\times A_{max}$$  
这个式子有什么用呢？  
我们已经做完了。  
因为答案就是$Sum-sum$  
考虑到这个东西不能为负，我们逐渐加$a_{max}$直到$Sum\ge  sum$  
```cpp
signed main()
{
	int T;
	cin>>T;
	while (T--)
	{
		int sum=0;
		cin>>n;
		for (int i=1;i<=n;i++) cin>>a[i];
		if (n==2)
		{
			cout<<0<<endl;
		}
		else
		{
			sort(a+1,a+n+1);
			for (int i=1;i<=n;i++) sum+=a[i];
			int Sum=sum;
			a[n]=sum/(n-1);
			while (sum>a[n]*(n-1))
			{
				a[n]++;
			}
			cout<<a[n]*(n-1)-Sum<<endl;
		}
			
	}
}
```
这个东西时间复杂度是错的~~因为我被$\color{red}{\text{Hack}}$了~~  

这样单次复杂度最大是$O(v)$的  
考虑这样一组数据：  
```
3
1000000000 1000000000 1000000000
```
你需要加$1e9$次。  
我们对于$a_{max}$，不需要逐渐加，可以二分它要加多少  
或者直接$O(1)$  
$(n-1)\times A_{max}\ge sum \Leftrightarrow A_{max}\ge\dfrac{sum}{n-1} $  
$A_{max}=\max\{\lceil \dfrac{sum}{n-1} \rceil,a_{max}\}$  

然后做完了  
```cpp
signed main()
{
	int T;
	cin>>T;
	while (T--)
	{
		int sum=0;
		cin>>n;
		for (int i=1;i<=n;i++) cin>>a[i];
		if (n==2)
		{
			cout<<0<<endl;
		}else
		{
			sort(a+1,a+n+1);
			for (int i=1;i<=n;i++) sum+=a[i];
			a[n]=max(a[n],((sum+n-2)/(n-1)));
			cout<<a[n]*(n-1)-sum<<endl;
		}
			
	}
}
```

---

## 作者：JiuZhE66666 (赞：0)

# 题解

首先，题目**没有问我们应该怎么放**，而是**问总共要放几个**。

因此，我们可以先考虑放几个，再考虑放这么多个是否合法。

设放入积木前，总的积木数为 $S$，放入 $k$ 个积木，则 $S+k$ 必须是 $n-1$ 的倍数。

设初始状态下，拥有最多积木的盒子的积木数为 $M$，则 $S+k$ 还需满足 $S+k$ 至少为 $M \times (n-1)$，因为如果没有选择拥有最多积木的盒子，其他盒子的数量至少为 $M$。

因此，我们需要找到一个数 $k$，它满足：

+ $S+k \geq M \times (n-1)$。

+ $S+k$ 是 $n-1$ 的倍数。

+ $k$ 要尽量小（即 $S+k$ 要尽量小）。

因此 $S+k$ 为 $[\max(M\times (n-1),S),M\times n]$ 内，最小的 $n-1$ 的倍数。

# code

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[100005];
signed main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;

        int mx=0;
        int sum=0;
        for(int i=1;i<=n;i++) 
        {
            cin>>a[i];
            mx=max(mx,a[i]);
            sum+=a[i];
        }

        int line=max(mx*(n-1),sum);
        cout<<(line/(n-1ll)+(line%(n-1ll)!=0))*(n-1ll)-sum<<'\n';
    }
    return 0;
}
```

---

## 作者：_zhx (赞：0)

# CF1452B Toy Blocks 题解

## 题目大意

1. 随机选择一个盒子 $i$；

2. 将第 $i$ 个盒子中的所有积木转移到其他盒子中。

两步操作后，使其他 $n-1$ 个盒子中积木的数量相同，为了满足要求，你需要额外放几块积木，求最少放几块积木。

### 题目思路

观察样例，能发现：

1. 如果所有数的总和 $\bmod(n-1)$ 不是零,那么答案就是$(n-1)-$ 所有数的总和 $\bmod(n-1)$。

2. 如果所有数的总和是 $n-1$ 的倍数,那么答案就零。

3. 如果最大的数乘以 $n-1$ 大于所有数的总和，那么答案就是最大的数乘以 $n-1$ 减去所有数的总和。

code：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[100005],x=0,s=0;int t,n;
int main()
{	
	cin>>t;
	while(t--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%lld",&a[i]);
			x=max(a[i],x);
			s+=a[i];
		}	
		if(x*(n-1)>s) cout<<x*(n-1)-s<<'\n';
		else
		{
			if(s%(n-1)==0) cout<<"0\n";
			else cout<<(n-1)-s%(n-1)<<'\n';
		}
		x=s=0;
	}
	return 0;
}
```


---

