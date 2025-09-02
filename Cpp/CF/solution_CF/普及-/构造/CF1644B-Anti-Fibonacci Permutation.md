# Anti-Fibonacci Permutation

## 题目描述

Let's call a permutation $ p $ of length $ n $ anti-Fibonacci if the condition $ p_{i-2} + p_{i-1} \ne p_i $ holds for all $ i $ ( $ 3 \le i \le n $ ). Recall that the permutation is the array of length $ n $ which contains each integer from $ 1 $ to $ n $ exactly once.

Your task is for a given number $ n $ print $ n $ distinct anti-Fibonacci permutations of length $ n $ .

## 样例 #1

### 输入

```
2
4
3```

### 输出

```
4 1 3 2
1 2 4 3
3 4 1 2
2 4 1 3
3 2 1
1 3 2
3 1 2```

# 题解

## 作者：沉石鱼惊旋 (赞：6)

### 题目翻译

我们定义对于所有 $i$ ($3 \leq i \leq n$)， $p_{i-2}+p_{i-1} \ne p_i$  这样的数列称之为 **反斐波那契数列** ，给定一个 $n$ ，请输出 $n$ 个长度为 $n$ 的不同的反斐波那契数列。

### 题目思路

只要 $p_{i-2}$ 和 $p_{i-1}$ 中任意一个数大于 $p_i$ ，那么肯定为反斐波那契数列。

所以构造一个**降序**的数列，然后每次把最后一个数往前挪，肯定能构成一个反斐波那契数列。

### 题目代码

```cpp
void solve()
{
	int n;
	cin>>n;
	int f=n;//记录最小位置
	int a[n+1];
	for(int i=1;i<=n;i++)a[i]=n-i+1;//创造降序数组
	for(int nn=0;nn<n;nn++)//n个数列
	{
		for(int i=1;i<=n;i++)cout<<a[i]<<" ";
		cout<<endl;
		swap(a[f],a[f-1]);//每次把最小往前
		f--;//更新最小位置
	}
}
```

多组数据，代码未全。请勿copy，当心踩坑。



---

## 作者：cqbztz2 (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF1644B)

[不会更好的阅读体验](https://www.luogu.com.cn/blog/493271/solution-cf1644b)

# Thinking

发现倒序排列一定是**反菲波拉契排列**，所以第一组解即为倒序排列。

考虑剩下的解法。

当 $ n $ 出现在排列的中间时，若 $ n $ 为偶数，无论如何排列中的 $ n $ 的前的两个数的和都不会为 $ n $（ 奇数 + 偶数 = 奇数 ≠ 偶数）。所以我们的 $ n $ 种方法即为 $ n $ 在 $ n $ 种不同位置，其余数字倒序即可。

但是当 $ n $ 为奇数时，若排列中的 $ n $ 的前的两个数为 $ a $ 与 $ a+1 $ 且 $ \dfrac{n-1}{2}=a $ 时，$ a+(a+1)=n $ ，这样就不符合条件了，于是这种排列删除。 这样我们就有了 $ n-1 $ 组解。

接着发现最后的 $ 1 $ 与 $ 2 $ 后面并没有数字，所以交换 $ 1 $ 与 $ 2 $ 也没有关系，所以 $ n $ 为奇数的最后一组解即为倒序排列，$ 1 $ 与 $ 2 $ 交换位置即可。
# Coding

```cpp
  #include<bits/stdc++.h>
  using namespace std;
  int t,n,ans[55],now;
  bool check(){
      for(int i=3;i<=n;i++) if(ans[i]==ans[i-1]+ans[i-2]) return false;
      return true;
  }
  signed main(){
      cin>>t;
      while(t--){
          now=2;
          cin>>n;
          if(n==1) cout<<1<<endl;
          else if(n%2==1){
              for(int i=n;i>=1;i--) ans[n-i+1]=i;
              for(int i=1;i<=n;i++){
                  if(check()==true){
                      for(int j=1;j<=n;cout<<ans[j++]<<" ");
                      cout<<endl;				
                  }
                  swap(ans[now],ans[now-1]);
                  now++;
              }
              for(int i=n;i>=3;i--) cout<<i<<" ";
              cout<<1<<" "<<2<<endl;
          }
          else{
              for(int i=n;i>=1;i--) ans[n-i+1]=i;
              for(int i=1;i<=n;i++){
                  for(int j=1;j<=n;cout<<ans[j++]<<" ");
                  swap(ans[now],ans[now-1]);
                  now++;
                  cout<<endl;
              }
          }
      }
      return 0;
  }
```


---

## 作者：Engulf (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1644B)

[更好的阅读体验](https://www.luogu.com.cn/blog/t-m-j-y-h-0-9/solution-cf1644b)

## 题意简述

给定 $n$，找出任意 $n$ 个长度 $n$ 的排列 $p$，满足 $\forall i\in [3,n],p_i\neq p_{i-1}+p_{i-2}$。

## 分析

数据很小，可以使用 dfs 解决。

因为要满足 $p_i\neq p_{i-1}+p_{i-2}$，搜索时约束一下即可。

注意是输出**任意 $n$ 个**。

## 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;

inline int read(){
	int x=0,f=0;char ch=getchar();
	while(!isdigit(ch))f^=!(ch^45),ch=getchar();
	while(isdigit(ch))x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return f?-x:x;
}
inline void write(int x){
	if(x<0)x=-x,putchar('-');
	if(x>=10)write(x/10);
	putchar(x%10+'0');
}
inline void writeln(int x){write(x);puts("");}
int n;
int a[55];
bool used[55];
int num;
void dfs(int dep){
	if(num==n)return;
	if(dep>n){
		for(int i=1;i<=n;i++)write(a[i]),putchar(' ');
		num++;
		puts("");
		return;
	}
	for(int i=1;i<=n;i++){
		if(!used[i]){
			if(dep>2)if(a[dep-1]+a[dep-2]==i)continue;
			used[i]=true;
			a[dep]=i;
			dfs(dep+1);
			if(num==n)return;
			used[i]=false;
		}
	}
}

int main(){
	int T=read();
	while(T--){
		n=read();
		memset(used,0,sizeof used);
		num=0;
		dfs(1);
	}
	#ifndef ONLINE_JUDGE
	system("pause");
	#endif
	return 0;
}
```

---

## 作者：pandaSTT (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1644B)

[不会更好的阅读体验](https://www.luogu.com.cn/blog/557117/solution-cf1644b)

# Thinking

一道构造好题。

容易发现，如果 $ a_{i-2} > a_i $ 或 $ a_{i-1} > a_i $ 的话，这三个数字不会形成斐波拉契数列。

因此我们只需要将大的数字移至小数的前面即可。

所以我们先构造出第一组解，即 $ n $ 到 $ 1 $ 从大到小排列。随后每一种解法，将 $ n $ 向前移动一位即可，这样就保证了除 $ n $ 外，大的数字都在小数前面，但是 $ 1 $ 的位置不会改变，因此 $ n-1 $ 不可能与 $ 1 $ 组成 $ n $。

但是我们又发现，这样的算法样例二过不了。

过不了的原因是，若 $ n $ 为奇数，则 $ n $ 可以分解为 $ \dfrac{n+1}{2} $ 和 $ \dfrac{n-1}{2} $ ，而这两个数的差为 $ 1 $ ，所以在 $ n $ 移动的过程中，$ n $ 会移动到$ \dfrac{n+1}{2} $ 和 $ \dfrac{n-1}{2} $ 的后面，这种方法就不可行的。

因此我们对于 $ n $ 为奇数的情况，将每种构造出的方法进行一个检查，发现这样不可行的方法就不输出。这样我们就少数出了一个解。

发现将放在最后 $ 1 $ 与 $ 2 $ 的位置交换不会产生任何影响，因此最后一组解为从大到小输出 $ 1 $ 到 $ n $ ，但最后的 $ 1 $ 与 $ 2 $ 交换位置即可。

第一次这么快打出 CF 的 B 题耶~

# Coding

```cpp
  #include<bits/stdc++.h>
  using namespace std;
  int t,n,ans[55],now;
  bool check(){
      for(int i=3;i<=n;i++){
          if(ans[i]==ans[i-1]+ans[i-2]){
              return false;
          }
      }
      return true;
  }
  signed main(){
      cin>>t;
      while(t--){
          memset(ans,0,sizeof ans);
          now=2;
          cin>>n;
          if(n==1){
              cout<<1<<endl;
          }
          else if(n%2==1){
              for(int i=n;i>=1;i--){
                  ans[n-i+1]=i;
              }
              for(int i=1;i<=n;i++){
                  if(check()==true){
                      for(int j=1;j<=n;j++){
                          cout<<ans[j]<<" ";
                      }
                      cout<<endl;				
                  }
                  swap(ans[now],ans[now-1]);
                  now++;
              }
              for(int i=n;i>=3;i--){
                  cout<<i<<" ";
              }
              cout<<1<<" "<<2<<endl;
          }
          else{
              for(int i=n;i>=1;i--){
                  ans[n-i+1]=i;
              }
              for(int i=1;i<=n;i++){
                  for(int j=1;j<=n;j++){
                      cout<<ans[j]<<" ";
                  }
                  swap(ans[now],ans[now-1]);
                  now++;
                  cout<<endl;
              }
          }
      }
      return 0;
  }
```


---

## 作者：ryanright (赞：1)

当我们从大到小 dfs 枚举时，是很容易生成反斐波那契数列的，因为前面的两个数加起来会比第三个数大很多。

但这也并不意味着倒着枚举就能 AC。比如说当 $n=6$ 时，就有

```
6 5 4 3 2 1
6 5 4 3 1 2
6 5 4 2 3 1
6 5 4 2 1 3
6 5 4 1 3 2
6 5 4 1 2 3
```
看到最后一个 `6 5 4 1 2 3`，最后三个数就满足了 $1+2=3$。

所以我们要加一点点特判，当数列不是反斐波那契数列时就跳过（当然这种情况不会太多，所以速度比较快，尽管还有更快的）。如此便可以了。见代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[55],t,n,tot;
bool used[55];
void dfs(int x)
{
	if(tot==n) return;
	if(x==n+1)
	{
		bool flag=1;
		for(int i=1;i<n-1;i++)//特判
			if(a[i]+a[i+1]==a[i+2])
			{
				flag=0;
				break;
			}
		if(!flag) return;
		for(int i=1;i<=n;i++) printf("%d ",a[i]);
		puts("");
		tot++;
		return;
	}
	for(int i=n;i>0;i--)//从大到小枚举
		if(!used[i])
		{
			used[i]=1;
			a[x]=i;
			dfs(x+1);
			used[i]=0;
		}
}
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		memset(used,0,sizeof(used));
		tot=0;
		dfs(1);
	}
	return 0;
}
```

---

## 作者：_Fatalis_ (赞：1)

翻译已交，直接上正解。

### Solution

显然，直接 dfs 生成排列-测试会超时。

想到可以在 dfs 过程中进行测试（判断下一个放置的数字是否满足反斐波那契序列的条件）。

于是代码就长这样：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
bool flag[10001];
int ans[10001];
int tot;

void dfs(int now)
{
	if(now==n+1)
	{
		tot++;
		for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
		puts("");
	}
	for(int i=1;i<=n;i++)
		if(!flag[i]&&(now==1||now==2||ans[now-2]+ans[now-1]!=i))   //剪枝
		{
			flag[i]=true;
			ans[now]=i;
			dfs(now+1);
			if(tot==n) return;
			flag[i]=false;
		}
}

int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		tot=0;
		memset(flag,0,sizeof(flag));
		cin>>n;
		dfs(1);
	}
}
```
46ms，AC。

But，你认为这就结束了吗？

### Solution++

以上方法时间复杂度玄学（不想算，反正有 $O(n)$，系数还蛮大），但通过数学分析可以降至裸 $O(n)$。~~并且代码量少很多~~

将排列降序。任意选择第 $i$ 位数，那么这个数就是 $n-i+1$。向前数两个数，分别是 $n-i+2$ 和 $n-i+3$。显然，$1\le i\le n$。

将前两个数字相加，关于 $i$ 的方程 $(n-i+3)+(n-i+2)=n-i+1$ 的解为 $i=n+4$。

![](https://cdn.luogu.com.cn/upload/image_hosting/d8niqm9c.png)

若不是反斐波那契数列，就应该满足 $i=n+4$。与 $1\le i\le n$ 相矛盾。说明逆序排列是反斐波那契数列。

那么，如果我们调换一下前后相邻的两个数的顺序？

那么，序列就会变成：

$$

(n-i+4),(n-i+3),(n-i+1),(n-i+2),(n-i+0),(n-i-1)
$$

事实上，可能没有 $n-i-1$，但没有可以不用管这个数字了，所以不会有问题。

如果有的话，调换顺序会波及到这些数字。

一一列出方程，解就完事了！

$(n-i+4)+(n-i+3)=(n-i+1)$

$i=n+3$，不成立。

$(n-i+3)+(n-i+1)=(n-i+2)$

$i=n+2$，不成立。

$(n-i+1)+(n-i+2)=(n-i+0)$

$i=n+3$，不成立。

$(n-i+2)+(n-i+0)=(n-i-1)$

$i=n+3$（想必你能猜到是这个吧），不成立。

都不成立，说明在倒序的基础上对调数字，都满足反斐波那契数列。

所以，总共可以调转 $(n-1)$ 次，加上原来的逆序 $1$ 次，就有 $n$ 次了。

$O(n)$ 满足了题目条件。

这也就为什么题目上会有 $\textsf{It can be shown that it is always possible to find n different anti-Fibonacci permutations of size n under the constraints of the problem.}$ 的原因吧。

附：中间为什么会有一个 $i=n+2$ 的解呢？

理性的认识，中间的两个数对调，移项了，所以有两点贡献，相比逆序的解应该少 $2$。

这下，其他的解为 $i=n+3$ 应该也不难理解了吧。

```cpp
#include<bits/stdc++.h>
using namespace std;

int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n;
		for(int j=n;j>=1;j--) printf("%d ",j);puts("");
		for(int i=n;i>=2;i--)
		{
			for(int j=n;j>=1;j--)
			{
				if(j==i) printf("%d %d ",j-1,j),j--;  //交换
				else printf("%d ",j);
			}
			puts("");
		}
	}
	return 0;
}
```

### Solution+$\infty$

事实上，这道题有许多方法，最终原理就是 **逆序排列永远满足反斐波那契数列**。

#### 方法1

逆序后，将任意一个数提前，也是 $(n-1)$ 种。

#### 方法2

逆序后，调换间隔一个数的两个数。（猜测）

$\cdots\cdots$

附上 Translate。

### Translate

反斐波那契数列（anti-Fibonacci）定义为 $1\sim n$ 的排列中不满足 $p_{i-2}+p_{i-1}\ne p_i$ 的排列。

输入 $t$ 数据，每组数据给定序列长度 $n$。

对于每组数据，只需任意输出 $n$ 个长度为 $n$ 的反斐波那契数列。每行一个序列，用空格分隔。（不允许输出多个相同的序列。**易证长度为 $n(n\ge 3)$ 的反斐波那契数列数量必定大于等于 $n$。**）

其中 $3\le n\le 50,1\le t\le 48$。


---

## 作者：BetaCutS (赞：1)

## 题目大意

每次输入一个 $n$，你要构造 $n$ 个 $1-n$ 的排列 $a$，并且对于每个 $a$ 的任意 $\sum\limits_{i=3}^na_i$，存在 $a_{i-2}+a_{i-1}\ne a_i$。输出这 $n$ 个排列 $a$。

## 算法

深搜，每次从 $1$ 到 $n$ 枚举并判断符不符合题意。搜索 $n$ 层后，输出 $a$ ，当输出了 $n$ 次以后，就可以结束搜索了。

## 代码

```cpp
int T,n,cnt,a[N],used[N];
//a是当前的答案，used是标记每个数有没有被选过，cnt是输出次数
void dfs(int k)
{
	if(k>n)//输出答案
	{
		cnt++;
		for(int i=1;i<=n;i++)
			printf("%d ",a[i]);
		puts("");
		return;
	}
	for(int i=1;i<=n;i++)//枚举每一个数
	{
		if(cnt>=n)
			return;
		if(!used[i]&&(k<3||a[k-2]+a[k-1]!=i))//如果i没被选过，并且前面两个数不等于这个数，也就是i，k<3是为了防RE
		{
			used[i]=1;//标记
			a[k]=i;
			dfs(k+1);//继续搜索
			a[k]=used[i]=0;//恢复现场
		}
	}
}
int main()
{
	T=read();
	while(T--)
	{
		n=read();
		cnt=0;//记得初始化
		dfs(1);
	}
	return 0;
}

```


---

## 作者：zhicheng (赞：1)

### 题意简述

找出 $n$ 个长度为 $n$ 的反斐波那契数列 $p$，且 $p$ 为 $1-n$ 的一个排列。

【反斐波那契数列】指：对于每一个 $i$ $(3 \leq i \leq n)$，$p_{i-2}+p_{i-1} \ne p_i$。

### 分析

因为 $n$ 很小，因此直接模拟就可以了。需要加一点小 **trick**。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int a,x[55];
bool fun(){
	for(int i=3;i<=a;i++){
		if(x[i-2]+x[i-1]==x[i]){
			return 0;
		}
	}
	return 1;
}
int main(){
	int n,sum;
	cin>>n;
	while(n--){
		sum=0;
		cin>>a;
		for(int i=1;i<=a;i++){
			x[i]=i;  //初始化
		}
		x[2]=3;//小优化。
		x[3]=2;//因为开头为“1,2,3”的数列一定不满足，因此换成“1,3,2”。
		while(sum<a){
			if(fun()){
				sum++;
				for(int i=1;i<=a;i++){
					printf("%d ",x[i]);
				}
				printf("\n");
			}
			next_permutation(x+1,x+a+1);  //c++福利，用此函数获得下一个排列。
		}
	}
}
```

[亲测能过](https://codeforces.com/contest/1644/submission/147570313)

---

## 作者：_ajthreac_ (赞：0)

给出一种构造方式。

观察反斐波那契排列的定义，感性理解一下，大概是前面的越大越好。那么我们直接倒序排列 $n\sim1$，这个数列显然是反斐波那契排列。

但是题目要求 $n$ 个，我们注意到只要两项元素中有一个比后一项大就行，所以可以依次把最后面的数拿到最前面，这样我们一共获得了 $n-1$ 个排列（因为全拿完就变成 $1\sim n$，不符合条件）。剩下的一个可以随便构造一下，比如固定 $1$ 和 $n$，中间翻转之类的。

注意小数据，我的构造方式在 $n=3$ 时需要特判。

```cpp
const int N=100;
int T,n,vis[N],a[N];
int main(){
  Read(T);
  while(T--){
    Read(n);
    if(n==3){
      printf("3 2 1\n1 3 2\n3 1 2\n");
      continue;
    }
    for(int i=1;i<=n;i++){
      if(i==n){
        printf("%d ",n);
        for(int j=2;j<n;j++)printf("%d ",j);
        puts("1");break;
      }
      for(int j=n-i+1;j<=n;j++)printf("%d ",j);
      for(int j=n-i;j;j--)printf("%d ",j);
      puts("");
    }
  }
  KafuuChino HotoKokoa
}
```

---

## 作者：joy2010WonderMaker (赞：0)

### 题目大意

这题是让你求出以 $1\sim n$ 每个数作为开头，求出任意一组对于任意的 $i$，$p_{i-2}+p_{i-1}\not=p_i$的序列。

### 题目分析

这题虽然可以暴力搜索，但是有没有更巧妙的方法呢？我们可以贪心。

1. 先输出 $i$。

1. 我们将除了 $i$ 以外的所有都加进一个双端队列里。

1. 先选择双端队列的尾部，再选择双端队列的头部，重复直到双端队列为空。

这种方法的正确性很明显，因为两个连续的数的和 $\ge n$ 。即使 $=n$ ，$n$ 也一定已经被输出过了。

### 正确代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){
    char c=getchar();
	int x=0;
	bool f=0;
    for(;!isdigit(c);c=getchar())
		f^=!(c^45);
    for(;isdigit(c);c=getchar())
		x=(x<<1)+(x<<3)+(c^48);
    if(f)
		x=-x;
	return x;
}
void write(int x){
	if(x<0)
		putchar('-'),x-=x*2;
	if(x>9)
		write(x/10);
	putchar(x%10+'0');
}
int t,n,cnt;
deque<int>q;
int main(){
	t=read();
	for(;t--;){
		n=read();
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++)
				if(i!=j)
					q.push_back(j);
			write(i),putchar(' '),cnt=0;
			while(!q.empty()){
				++cnt;
				if(cnt&1){
					write(q.back()),putchar(' ');
					q.pop_back();
				}else{
					write(q.front()),putchar(' ');
					q.pop_front();
				}
			}
			puts("");
		}
	}
	return 0;
}

```


---

## 作者：windflower (赞：0)

简要题意：
>构造 n 个不同的由 $1\cdots n$ 组成的反斐波那契额数列，即对任意 $a_i(i>2)$ 满足 $a_i\neq a_{i-1}+a_{i-2}$ 。   

那么其实只要我们能想出一种策略来构造即可。  
首先显然递减数列一定满足题意，那就在递减数列的基础上进行微调来构造出其余 $n-1$ 个数列。  
我们可以构造一个 $n,n-1,\cdots ,i,1,i-1,i-2,\cdots,2$ 这样的一个数列，即将递减数列的1依次左移获得新的 $n-1$ 个数列，易知这 $n-1$ 个数列都满足题意。   
那么代码实现就很简单了:  
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++){
			int t=n;
			for(int j=n;j>=1;j--)
				if(j==i)printf("%d ",1);
				else printf("%d ",t--);
			printf("\n");
		}
	}
	return 0;
}
```


---

## 作者：happy_dengziyue (赞：0)

### 1 思路

首先我们构造从 $n$ 到 $1$ 的数列，很明显这是一个反斐波那契数列。

然后，无论将 $1$ 挪到那个地方，只要其余数字相对位置完全不变，都能保证它是反斐波那契数列。

例如，当 $n=4$ 时，输出如下 $4$ 个数列：

```
4 3 2 1
4 3 1 2
4 1 3 2
1 4 3 2
```

证明：

对于任意的 $i(3\le i\le n)$，设这个数列为 $a$，可得：

$$a[i-2]+a[i-1]\not=a[i]$$

按照上面的方法，可分为 $4$ 种情况：

+ 当 $a[i-2]=1$：

$$\because a[i-1]=a[i]+1$$

$$\therefore a[i-2]+a[i-1]=a[i]+2\not=a[i]$$

+ 当 $a[i-1]=1$：

$$\because a[i-2]=a[i]+2$$

$$\therefore a[i-2]+a[i-1]=a[i]+3\not=a[i]$$

+ 当 $a[i]=1$：

$$\because a[i-2]>1\operatorname{and}a[i-1]>1$$

$$\therefore a[i-2]+a[i-1]\not=a[i]$$

+ 当 $a[i-2]\not=1\operatorname{and}a[i-1]\not=1\operatorname{and}a[i]\not=1$

$$\because a[i-2]=a[i]+2\operatorname{and}a[i-1]=a[i]+1$$

$$\therefore a[i-2]+a[i-1]=a[i]\times2+3\not=a[i]$$

综上：

$$a[i-2]+a[i-1]\not=a[i]$$

### 2 代码与记录

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
int t;
int n;
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1644B_1.in","r",stdin);
	freopen("CF1644B_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;++i){
			for(int j=1;j<=n;++j){
				if(j<i)printf("%d ",n-j+1);
				if(j==i)printf("1 ");
				if(j>i)printf("%d ",n-j+2);
			}
			printf("\n");
		}
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/69929552)

By **dengziyue**

---

## 作者：miao5 (赞：0)

如果一个长度为 $n$ 的排列数组 $a$ 中没有任何两个相邻的数的和等于他们的下一个数，即如果 $a_{i-2}+a_{i-1}\ne a_i$ 对于所有 $i(3\le i \le n)$ 都成立，那么称排列数组 $a$ 是反斐波那契的。

现在给你 $t$ 个 $n$，对于每个 $n$ 求出 $n$ 个反斐波那契排列数组。

我们首先观察性质，一个形如 $n,n-1,n-2,\dots,1$ 的排列数组一定是反斐波那契的，因为它的每一项大于之后的所有项。

我们根据上面的数组向一般扩展，我们发现，形如 $n,n-1,\dots,i,1,i-1,\dots,2$ 的一个排列数组一定也是反斐波那契的，我们发现除了数组中间的 $1$ 以外，它的每一位也都大于后面的任何一位，而 $1$ 是最小的正整数，不能被其他的数加出来，所以这样的数组是满足条件的。

可以看出 $1$ 在数组中可能的位置一定是 $n$ 个，题目让你求的排列数组个数也是 $n$ 个。输出所有这样的排列数组，就可以解决这个问题了。
```
#include<iostream>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		for(int i=1;i<=n;i++){
			for(int j=n;j>i;j--) cout<<j<<' ';
			cout<<1<<' ';
			for(int j=i;j!=1;j--) cout<<j<<' ';
			cout<<endl;
		}
	}
}
```

---

## 作者：zhongcy (赞：0)

[CF Problem](https://codeforces.com/problemset/problem/1644/B)

------------

给定一个正整数 $ n $，构造一个序列 $ p $ 满足 $ \forall i \in [3,n], p_i \ne p_{i-1}+p_{i-2} $。输出 $ n $ 个满足条件的 $ p $。

### Solution

------------

显然，对于 $ \forall i\in [1,n] $，都可以构造 $ p=[i,n,n-1,\dots,i+1,i-1,\dots,1] $ 满足要求。因为整个序列基本满足单调递减，而且 $ p_1+p_2=n+i\ne p_3 , \forall j \in [4,n],p_{j-1}+p_{j-2} > p_j $。



### Code

------------

时间复杂度 $ \Theta(tn^2) $。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int t;cin>>t;
	while(t--)
	{
		int n;cin>>n;
		for(int i=1;i<=n;i++)
		{
			cout<<i<<' ';
			for(int j=n;j>=1;j--)
				if(j!=i) //特判
					cout<<j<<' ';	
			cout<<'\n';//按照上述过程构造
		}
	}
	return 0;
}
```


---

## 作者：清烛 (赞：0)

题意：$T$ 组数据，给定 $n$，要求构造 $n$ 个“反斐波那契排列”，一个反斐波那契排列满足 $\forall i( 3\le i\le n)$，有 $p_{i-2}+p_{i-1}\ne p_i$。$t\le 48,n\le50$。

div 2 的 B 题，考虑从简单的形式开始思考如何构造。

我们发现，一个形如 $1,2,3,\cdots, n$ 的排列只存在一个地方不满足限制：$1+2=3$。那么只要将 $1$ 扔到排列尾部，$2,3,\cdots,n,1$ 显然是满足要求的排列，然后将前面的 $n-1$ 个元素循环移位一下，形如 $i,i+1,\cdots,n,1,\cdots,i-1,1$。就能构造出 $n-1$ 个满足题意的排列。

还剩下一个，怎么办呢，上面的排列都以 $2,3,\cdots, n$ 开头，这次我们考虑让 $1$ 开头。发现 $1, n, 2,3,\cdots, n -1$ 满足题意，直接输出即可。

```cpp
int main() {
    int T; read(T);
    while (T--) {
        int n; read(n);
        FOR(i, 2, n) {
            FOR(j, i, n) print(j, ' ');
            FOR(j, 2, i - 1) print(j, ' ');
            if (i != 1) print(1, ' ');
            putchar('\n');
        }
        print(1, n, ' ');
        FOR(j, 2, n - 1) print(j, ' ');
        putchar('\n');
    }
    return output(), 0;
}
```



---

## 作者：ttq012 (赞：0)

思维题。这里提供两种思路。

思路 $1$：用 `dfs` 暴力地查找出 $n$ 组满足条件的序列。

```cpp
#include <bits/stdc++.h>

using namespace std;

int a[53];
bool vis[53];
int n;
int top = 0;

void dfs(int u) {
    if (top == n) return ;
    if (u == n + 1) {
        for (int i = 1; i <= n; i ++)
            printf ("%d ", a[i]);
        puts("");
        top ++;
        if (top == n) return ;
    }
    for (int i = 1; i <= n; i ++) if (! vis[i] && (u < 3 || a[u - 2] + a[u - 1] != i)) {
        vis[i] = true;
        a[u] = i;
        dfs(u + 1);
        vis[i] = false;
    }
}

signed main() {
    int t;
    cin >> t;
    while (t --)
    {
        top = 0;
        cin >> n;
        dfs(1);
    }
    return 0;
}
```

思路 $2$：很容易发现，满足条件 $a_{i-2} + a_{i-1} = a_i$ 需要令 $a_i\gt a_{i-2}, a_{i-1}$。

由于题目只叫我们求 $n$ 组满足条件的，所以我们只需要让第一个数 $a_1$ 为区间 $[1, n]$ 中的任意的一个数，从 $a_2\sim a_n$ 单调递减。

构造出来按照上面条件构造的 $n$ 组序列即可。

```cpp
#include <bits/stdc++.h>

using namespace std;

int a[53];
bool vis[53];
int n;
int top = 0;

void dfs(int u) {
    if (top == n) return ;
    if (u == n + 1) {
        for (int i = 1; i <= n; i ++)
            printf ("%d ", a[i]);
        puts("");
        top ++;
        if (top == n) return ;
    }
    for (int i = 1; i <= n; i ++) if (! vis[i] && (u < 3 || a[u - 2] + a[u - 1] != i)) {
        vis[i] = true;
        a[u] = i;
        dfs(u + 1);
        vis[i] = false;
    }
}

signed main() {
    int t;
    cin >> t;
    while (t --)
    {
        top = 0;
        cin >> n;
        dfs(1);
    }
    return 0;
}

```


---

