# Xor of 3

## 题目描述

You are given a sequence $ a $ of length $ n $ consisting of $ 0 $ s and $ 1 $ s.

You can perform the following operation on this sequence:

- Pick an index $ i $ from $ 1 $ to $ n-2 $ (inclusive).
- Change all of $ a_{i} $ , $ a_{i+1} $ , $ a_{i+2} $ to $ a_{i} \oplus a_{i+1} \oplus a_{i+2} $ simultaneously, where $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)

 Find a sequence of at most $ n $ operations that changes all elements of $ a $ to $ 0 $ s or report that it's impossible.We can prove that if there exists a sequence of operations of any length that changes all elements of $ a $ to $ 0 $ s, then there is also such a sequence of length not greater than $ n $ .

## 说明/提示

In the first example, the sequence contains only $ 0 $ s so we don't need to change anything.

In the second example, we can transform $ [1, 1, 1, 1, 0] $ to $ [1, 1, 0, 0, 0] $ and then to $ [0, 0, 0, 0, 0] $ by performing the operation on the third element of $ a $ and then on the first element of $ a $ .

In the third example, no matter whether we first perform the operation on the first or on the second element of $ a $ we will get $ [1, 1, 1, 1] $ , which cannot be transformed to $ [0, 0, 0, 0] $ .

## 样例 #1

### 输入

```
3
3
0 0 0
5
1 1 1 1 0
4
1 0 0 1```

### 输出

```
YES
0
YES
2
3 1
NO```

# 题解

## 作者：dottle (赞：58)

容易发现，在操作前后，三个数的异或和不变。因此有解有一个必要条件：所有数的异或和为 $0$。

先考虑 $n$ 为奇数的情形，我们依次在 $n-2,n-4,...,1$ 执行一次此操作，此时 $a_1=0$（即所有数的异或和），其余 $a_{2k}=a_{2k+1}$；然后我们再依次执行 $1,3,...,n-2$，这样每次执行都是将一个 $0$ 和两个相同的数变为了 $0$。

对于 $n$ 为偶数的情形，我们则需要找到一个长为奇数的前缀，使得其异或和为 $0$，然后依次对这个前缀和剩余部分执行奇数的操作即可。

---

## 作者：NobodyThere (赞：18)

提供一种比较好想好写，不容易错的方法。~~教你将 \*2500 的题做成 \*1500~~

[题目链接](https://www.luogu.com.cn/problem/CF1572B)

### 思路

显然，当存在奇数个 $1$ 时，原式无解。

证明：设对 $a_i,a_{i+1},a_{i+2}$ 进行操作，记 $a_i\oplus a_{i+1}\oplus a_{i+2}=sum$，则操作之后三数的异或和为 $sum\oplus sum\oplus sum=sum$，不变。由此可得，所有数的异或和，经任意次操作后不变。故要求初始状态的所有数异或和为 $0$。

更进一步地，记 $s_i=\bigoplus\limits_{k=1}^ia_k$，我们有 $s_0,s_1,\cdots,s_{i-1}$ 以及 $s_{i+2},s_{i+3},\cdots,s_n$ 均不发生变化。此时只有 $s_i,s_{i+1}$ 变化了。设 $x=s_{i-1}$，我们此时又有 $s_i=x\oplus sum,s_{i+1}=s_i\oplus sum=x,s_{i+2}=s_{i+1}\oplus sum=x\oplus sum$。所以，操作后 $s_{i-1}=s_{i+1},s_i=s_{i+2}$。我们又知道 $s_{i-1},s_{i+2}$ 均不变，所以原题转化成了：

给定 $s_0,s_1,\cdots s_n$，保证 $s_0=s_n=0$，每次操作可以选定一个数 $i\in[1,n-2]$，使得 $s_{i+1}\gets s_{i-1},s_i\gets s_{i+2}$，要求 $n$ 次操作后最终所有数变为 $0$。

这就很好做了。显然每次赋值都只能在下标奇偶性相同的相邻位置上进行，且不能给 $s_0,s_n$ 赋值，那么只需要分下标的奇偶即可。下标为偶数的位置显然无论如何都可以被赋值成 $0$，那么先考虑奇数位置：找到数值为 $0$ 的位置，然后向两边赋值即可，找不到即无解。

### 代码实现

```cpp
#include <cstdio>
int T, n, a[200007], s[200007], ans[200007], tot, idx;
int main() {
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++)
			scanf("%d", &a[i]);
		for(int i = 1; i <= n; i++)
			s[i] = s[i - 1] ^ a[i];
		if(s[n]) {
			puts("NO"); continue;
		}
		tot = 0, idx = 0;
		for(int i = 1; i <= n; i += 2) {
			if(!s[i]) {
				idx = i; break;
			}
		}
		if(!idx) {
			puts("NO"); continue;
		}
		for(int i = idx - 2; i >= 1; i -= 2)
			ans[++tot] = i;
		for(int i = idx + 2; i < n; i += 2)
			ans[++tot] = i - 1;
		for(int i = 2; i < n; i += 2)
			ans[++tot] = i - 1;
		puts("YES");
		printf("%d\n", tot);
		for(int i = 1; i <= tot; i++)
			printf("%d ", ans[i]);
		puts("");
	}
	return 0;
}
```

---

## 作者：enucai (赞：7)

### 前言：立志写一篇清晰、简洁的题解。

----

### 题意：

给你一个由 $0$ 和 $1$ 组成的序列 $a$ ，要求你对这个序列进行不超过序列长度 $n$ 次的如下操作：

选定一个 $i$ ，满足 $1\le i \le n-2$ ，将 $a_i,a_{i+1},a_{i+2}$ 三个元素的值都更改为 $a_i\bigoplus a_{i+1}\bigoplus a_{i+2}$ 的值。问你如何操作使得 $a$ 中所有元素的值都变成 $0$ 。如果可行，输出任意方案，否则输出 `NO` ，表示无解。

### 思路：

蒟蒻根本不会巨佬们的方法，于是进行了普通的分类讨论。

第一部肯定要将 $a_1$ 变成 $0$ 。

-	如果 $a_1=0$ ，直接跳开着一步。

-	如果 $a_1=1$ ，那么分情况：

	-	如果前三个数分别是 $1,1,0$ 或者 $1,0,1$ ，那么直接将前面三个数字进行操作即可。
    
    -	如果前三个数分别是 $1,1,1$ 或者 $1,0,0$ ，那么发现没办法直接将第一个元素变为 $0$ ，那么就要先改变后面的（第二、三个）元素。如果二、三个元素同时改变，那么改变后他们的值也一定相同，异或后也一定是 $0$ ，并无法改变第一个元素的值。因此只能在第三个元素上做文章。
    
    	如果第三个元素的后面两个元素（即第四、五个元素）异或的结果为 $1$ ，那么他们就能改变第三个元素的值，进而能将第一个元素改变为 $0$ 。如果不能，那么就继续往后找，找到为之，再往前一组组进行操作。如果找到最后也找不到，那么一定是 `NO` 了。
        
现在第一个元素已经变为 $0$ 了。

好，接下来我们假设数组前面已经有了一堆连续的 $0$ （至少一个），接下来分4种情况讨论（以下情况均令第一个 $1$ 的位置为 $i$ ，且满足 $1\le i \le n-2$ ）：

-	序列为： $0,0\dots 0,1,0,0$ 。

	操作方法：将 $i,i+1,i+2$ 三个位置进行一次操作，变成 $0,0\dots 0,1,1,1$ ，再将 $i-1,i,i+1$ 三个位置进行一次操作，变成 $0,0\dots 0,0,0,1$ 。
    
    2次操作在序列后面多了2个 $0$ 。

-	序列为： $0,0\dots 0,1,0,1$ 。
	
    操作方法：将 $i,i+1,i+2$ 三个位置进行一次操作，变成 $0,0\dots 0,0,0,0$ 。
    
    1次操作在序列后面多了1个 $0$ 。

-	序列为： $0,0\dots 0,1,1,0$ 。

	操作方法：将 $i,i+1,i+2$ 三个位置进行一次操作，变成 $0,0\dots 0,0,0,0$ 。
    
    1次操作在序列后面多了1个 $0$ 。

-	序列为： $0,0\dots 0,1,1,1$ 。

	操作方法：将 $i-1,i,i+1$ 三个位置进行一次操作，变成 $0,0\dots 0,0,0,1$ 。
    
    1次操作在序列后面多了2个 $0$ 。
    
最后，经过操作，能保证序列的前 $n-2$ 个元素都是 $0$ 。

至于最后两个元素：

-	为 $0,0$ ，不用动。

-	为 $1,0$ ，无解，输出 `NO` 。

-	为 $0,1$ ，无解，输出 `NO` 。

-	为 $1,1$ ，将 $n-2,n-1,n$ 三个元素进行一次操作即可。

最后，统计操作次数时发现，每次操作均摊下来，要么能是序列后面多1个 $0$ ，要么能是序列后面多1.5个 $0$ 。至于前面的将第一个元素变为 $0$ 的操作来看，假如他最后搜到了第 $pos$ 个元素才能找到能行的操作，那么退回来的操作次数不会超过 $\frac{pos}{2}$ 次，然而继续往后增加 $0$ 的那个操作，操作到 $pos$ 位置的操作次数也不会超过 $\frac{pos}{2}$ 次。因此，最终的操作次数一定是小于等于 $n$ 次的。因此就不用担心操作次数的问题了qwq。

一些细节还是看代码吧：

```cpp
int n,a[200010];
vector<int> ans;//存储操作方法
void work(){
    ans.clear();//多测清空
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);//不想写快读
    }
    if(a[1]==1){
        int i=1;
        while(1){
            if(i+2>n){//找不到能行的位置，直接NO
                puts("NO");
                return;
            }
            if(a[i+1]^a[i+2]==1){//找到的能行的位置
                break;
            }
            i+=2;
        }
        while(i>=1){//回撤操作
            a[i]^=a[i+1]^a[i+2];
            a[i+1]=a[i+2]=a[i];
            ans.push_back(i);
            i-=2;
        }
    }
    for(int i=2;i<=n-2;i++){//逐渐往后加0
        if(a[i]==0){
            continue;
        }
        if(a[i]==1&&a[i+1]==1&&a[i+2]==0){//四种情况
            ans.push_back(i);
            a[i]=a[i+1]=0;
        }else if(a[i]==1&&a[i+1]==0&&a[i+2]==1){//四种情况
            ans.push_back(i);
            a[i]=a[i+2]=0;
        }else if(a[i]==1&&a[i+1]==1&&a[i+2]==1){//四种情况
            ans.push_back(i-1);
            a[i]=a[i+1]=0;
        }else if(a[i]==1&&a[i+1]==0&&a[i+2]==0){//四种情况
            ans.push_back(i);
            ans.push_back(i-1);
            a[i]=0;
            a[i+2]=1;
        }
    }
    if(a[n-1]==1&&a[n]==0){//判断最后两个元素的情况
        puts("NO");
        return;
    }else if(a[n-1]==0&&a[n]==1){
        puts("NO");
        return;
    }else if(a[n-1]==1&&a[n]==1){
        ans.push_back(n-2);
    }
    puts("YES");
    printf("%d\n",(int)ans.size());//输出答案
    for(auto p:ans){
        printf("%d ",p);
    }puts("");
}
```

**完结散花！**

---

## 作者：王熙文 (赞：5)

昨天做题做到的套路今天就又遇到了。

## 思路

注意到一次操作三个数的异或和不变，考虑对序列求异或前缀和 $a$，并观察操作在 $a$ 上是什么样的。

因为异或和不变，所以一次操作 $i$ 只会改两个数，$a_i$ 和 $a_{i+1}$。因为原序列操作后 $i+1$ 与 $i+2$ 位置上的数相同，且 $i$ 与 $i+1$ 位置上的数相同，所以一次操作后 $a_i \gets a_{i+2},a_{i+1} \gets a_{i-1}$。

考虑如果 $a_x=a_y=0$，中间全是 $1$，区间是否可以覆盖为 $0$。当 $x$ 与 $y$ 同奇偶时，因为每一次操作赋值的两边都是同奇偶的，所以与 $x,y$ 不同奇偶的位置不可能被覆盖到，无解。否则，可以先从前到后用 $a_x$ 把与 $x$ 同奇偶的位置覆盖为 $0$，那么在最后一定有 $a_{y-1}=a_y=0$，再覆盖回去即可。

比如 `011110`，先操作 $2$，变成 `010110`，再操作 $4$，变成 `010000`，再操作 $2$，变成 `000000`，实现清零。

还可以发现如果 $a_n \ne 0$，则无法操作使它变为 $0$，一定无解。那么，当 $n$ 为奇数时，直接按照上面的方式操作 $x=0,y=n$ 即可。

如果 $n$ 为偶数，如果序列中没有一个奇数的位置为 $0$，一定无解，因为奇数位置不可能被覆盖到。否则，设位置为 $i$，先操作 $x=0,y=i$，再操作 $y=i,x=n$ 即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[200010];
int tot,ans[200010];
void output(int l,int r)
{
	if(l+1==r) return;
	int now=l;
	while(now<r-3) ans[++tot]=now+1,now+=2;
	while(now>=l) ans[++tot]=now+1,now-=2;
}
int main()
{
	int t; cin>>t; while(t--)
	{
		cin>>n;
		for(int i=1; i<=n; ++i) cin>>a[i],a[i]^=a[i-1];
		if(a[n]!=0) { cout<<"NO\n"; continue; }
		if(n%2==1)
		{
			cout<<"YES\n";
			tot=0,output(0,n);
			cout<<tot<<'\n';
			for(int i=1; i<=tot; ++i) cout<<ans[i]<<' '; cout<<'\n';
		}
		else
		{
			bool flag=0;
			for(int i=1; i<=n; i+=2)
			{
				if(a[i]==0)
				{
					cout<<"YES\n";
					tot=0,output(0,i),output(i,n);
					cout<<tot<<'\n';
					for(int i=1; i<=tot; ++i) cout<<ans[i]<<' '; cout<<'\n';
					flag=1;
					break;
				}
			}
			if(!flag) cout<<"NO\n";
		}
	}
	return 0;
}
```

---

## 作者：ltdj (赞：4)

很不错的一道构造

[题目传送门](https://codeforces.com/contest/1573/problem/D)

-----

### 题意
给定一个01序列， 每次可以选择相邻的三个数，将他们异或起来，并让这三个数都等于异或结果。

每次操作用一个数x表示，表示将 $x$ ,$x+1$ ,$x+2$ 异或起来
求一个长度不超过n的操作序列使得操作后，序列中每个数都等于0，或者输出无解。

保证只要能让所有数都等于0，则存在合法操作序列长度小于n。

### 题解

首先我们考虑有奇数个1，那么显然无解。

这时候我们考虑从第一个1开始，每次消掉第一对1（最前面两个1）。

--这时候对于每一对1分两种情况：

-- · 中间有奇数个0
比如10001、101 , 这种可以直接消掉

假设第一个1位置为x，那么可以进行$x$, $x+2$, $x+4$.....，使得变成中间只有一个0

10001 -> 11101

然后消掉最后三个，再一直往前消即可。

-- · 中间有偶数个0。

这种显然无法直接整个消掉，可以让他先全部变成1，这时候如果左边或右边有一个0，就可以消掉，否则无解。

比如1001 -> 1111 假设原序列是10010,右边有一个0,那么现在11110可以消掉。

------
### 实现
还是不好实现的，这里给出我的实现

如果第一个数是0，直接往后消， 奇数直接消，偶数前面有0能消。

否则第一个数是1，如果第一对是奇数情况，直接消掉，变第一种情况。

否则第一对是偶数，暂时不管第一对，先把后面的消了，这时候后面就有了0， 再消第一对。

如果后面消不掉，那么显然无解。

具体不懂看代码
$solve(x)$ 表示将x及以后的全消掉， return 1表示能消掉， 否则不能.
```cpp
**#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

int read(){
	int num=0, flag=1; char c=getchar();
	while(!isdigit(c) && c!='-') c=getchar();
	if(c=='-') flag=-1, c=getchar();
	while(isdigit(c)) num=num*10+c-'0', c=getchar();
	return num;  
}

const int N = 200505;
int T, n;
int a[N], nex[N];

vector<int> ans;
int solve(int x){
	if(x > n) return 0;
	if(nex[x] == 0) return 1;
	if( a[x] == 0 || (nex[x]-x-1)%2 ){
		if(a[x]==0) x = nex[x];
		while(x){
			if((nex[x]-x-1)%2){
				int i;
				for(i=x; i+2<nex[x]; i+=2){
					ans.push_back(i);
				}
				for(; i>=x; i-=2){
					ans.push_back(i);
				}
				
			}else{
				for(int i=x; i+2<nex[x]; i+=2){
					ans.push_back(i);
				}
				for(int i=x-1; i+2<=nex[x]; i+=2){
					ans.push_back(i);
				}
			}
			
			x = nex[nex[x]];
		}return 1;
	}else{
		if(solve(nex[x]+1)){
			for(int i=x; i+2<nex[x]; i+=2){
					ans.push_back(i);
			}
			for(int i=nex[x]+1; i-2>=x; i-=2){
				ans.push_back(i-2);
			}
			return 1;
		}else return 0;
	}
}

int main(){
	T=read();
	while(T--){
		n = read();
		for(int i=1; i<=n; i++) a[i] = read();
		int las = 0;
		int cnt = 0;
		for(int i=n; i>=1; i--){
			nex[i] = las;
			if(a[i]) las = i, cnt++;
		}
		if(cnt % 2) {
			printf("NO\n");
			continue;
		}
		ans.clear();
		if(solve(1)){
			printf("YES\n%d\n", ans.size());
			for(int i=0; i<ans.size(); i++) {
				printf("%d ", ans[i]);
			}printf("\n");
		} else printf("NO\n");
	}
	return 0;
}
**
```

---

## 作者：UncleSam_Died (赞：1)

### 解题思路
首先我们知道，当序列中有奇数个 $1$ 的时候无解，因为每次操作只会增加或减少 $2$ 或 $0$ 个 $1$，当序列中有奇数个 $1$ 的时候，一定会存在一个 $1$ 无法被消除。因此，在这种情况下，直接输出 `NO` 即可。

不难发现，序列的异或和为一定值，证明如下：
- 令 $sx$ 表示每一次操作选取的三个数的异或和，令 $s$ 表示整个序列的异或和；
- 每次操作可以看作删去三个数、添加三个数，不妨设这三个数分别为 $x_1,x_2,x_3$，那么在删去三个数的时候，$s\gets s\oplus (x_1\oplus x_2\oplus x_3)$，替换一下可得 $s\gets s\oplus sx$，新添入三个 $sx$ 后 $s\gets (s\oplus sx)\oplus sx\oplus sx\oplus sx$，打开括号后可得 $s\gets s$，异或和不变。

显然直接从左往右扫一次是可以更新形如 `011110` 和 `10111` 的段的，但是序列中显然还可能存在形如 `01000010` 的段，这种情况下直接扫描是无法更新的。我们考虑将后面的段转化为前面的段。由于每次操作最多会产生 $2$ 的影响，我们可以每次枚举 $i=2\cdot k+1,k\in \mathbb N$ 的位置，这样对于最终的答案是没有影响的。由于序列前面某一段可能需要倒序更新，而后面的段只需要直接暴力修改，那么我们考虑找到第一段需要倒序修改的段，由于从 $1$ 开始的一段连续的 $0$ 不管是否修改都没有影响，那么一段需要修改的段一定不能只包括 $0$。同理，由一段中需要有偶数个 $1$ 才能被消除，那么第一段中也应该包含偶数个 $1$。由此，我们需要找到第一段包含偶数个 $1$ 的且右端为奇数的段，直接枚举即可。

在全部转化后，再从左往右扫一次就可以得到答案了。

总共需要 $O(n)$ 次操作，可以通过本题。

### AC 代码
```cpp
#include<vector>
#include<stdio.h>
#include<stdlib.h>
#define N 200005
int n,a[N],sum[N];
inline void work(){
    scanf("%d",&n);std::vector<int> ans;int _1=0;
    for(register int i=1;i<=n;++i) scanf("%d",&a[i]);
    for(register int i=1;i<=n;++i) if(a[i]==1) ++_1;
    if(_1&1){puts("NO");return;}
    for(register int i=1;i<=n;++i) sum[i]=sum[i-1]+a[i];
    int pos=0;for(register int i=1;i<=n;++i)
        if((i&1)&&sum[i]%2==0){pos=i;break;}
    if(!pos){puts("NO");return;}
    for(register int i=pos-2;i>=1;i-=2) ans.push_back(i);
    for(register int i=pos+1;i<=n-2;i+=2) ans.push_back(i);
    for(register int i=1;i<=n-2;i+=2) ans.push_back(i);
    puts("YES"); printf("%d\n",ans.size()); if(ans.empty()) return;
    for(auto now:ans) printf("%d ",now); putchar('\n');
}signed main(){int T;scanf("%d",&T);while(T--) work();}
```

---

## 作者：zhanghengrui (赞：1)



官方题解的做法太神仙了，我这种菜鸡想不到就只能大力分类讨论了（

---

首先考虑，每一次操作不会使序列的异或和改变，因此原序列如果异或和不为 $0$ （有奇数个 $1$）一定得不到全 $0$，直接排除

考虑 $\cdots, 1, \underbrace{
0, \cdots, 0}_{\text{none or some 0}}, 1, 0, \cdots$ 这样一段，设两个 $1$ 的位置为 $p_1, p_2$，我们可以通过依次在 $p_2 - 2$ 和 $p_2 - 1$ 两个位置各进行一次操作把问题转化成 $(p_1, p_2 - 2)$ 的问题  
![_这里应该有张图_](https://i.loli.net/2021/09/24/c8T6AY5EDX3NGhb.png) 
边界条件是 $(p_1, p_1 + 1)$ 和 $(p_1, p_1 + 2)$，都是在 $p_1$ 位置进行一次操作即可把两个 $1$ 变成 $0$  
对于左边有 $0$ 的情况同理  
容易得到，对于每一对 $(p_1, p_2)$，这样操作需要的操作次数为 $\lceil \frac{p_2 - p_1}{2} \rceil \times 2 - 1$，不超过 $p_2 - p_1$，即小于区间长度

现在我们把原序列中所有的 $1$ 每两个分成一组  
前面已经把奇数个 $1$ 的情况处理掉了，这里必然能分完  
如果存在两个相邻的组，左边的右端和右边的左端之间存在至少一个 $0$，那么我们从可以用这两组入手，左边的往左推，右边的往右推  
注意整个序列左端或右端有 $0$ 也是可以利用的，通过加入两组 $(0, 0), (n + 1, n + 1)$ 可以把这两种情况也顺便处理了，具体见代码  
由于每次需要的操作数小于区间长度，因此总操作数小于 $n$，满足要求

考虑我们现在还没处理的情况：每两组之间和原序列头尾都没有 $0$，也就是原序列是若干段 $1, \underbrace{0, \cdots, 0}_{\text{none or some 0}}, 1$  
如果某一段内部有奇数个 $0$（$p_1 \equiv p_2 \pmod{2}$），那么可以通过操作序列 $p_1, p_1 + 2, \cdots, p_2 - 4, p_2 - 2, p_2 - 4, \cdots, p_1$ 把这段的两个 $1$ 变成 $0$（这里推荐自己动手模拟一下）
，就转化成上一种情况的问题了  
这里消耗的操作次数同样小于区间长度，也是满足条件的

现在只剩一种情况了：原序列是若干段 $1, \underbrace{0, \cdots, 0}_{\text{none or some 0}}, 1$，并且每段内部有偶数个 $0$  
可以证明（大概是枚举每次操作的三个位置的所有 $8$ 种情况），这种情况无论如何都不能转化为其他情况，不可能变全 $0$

至此，所有情况已讨论完毕

---

Code:

```python
global operations


# direction = true 向左，否则向右
def solve(p1: int, p2: int, direction: bool):
    if p2 - p1 == 2:
        operations.append(p1)
        return
    if direction:
        if p2 - p1 == 1:
            operations.append(p1)
        else:
            operations.append(p2 - 2)
            operations.append(p2 - 1)
            solve(p1, p2 - 2, True)
    else:
        if p2 - p1 == 1:
            operations.append(p1 - 1)
        else:
            operations.append(p1)
            operations.append(p1 - 1)
            solve(p1 + 2, p2, False)


for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    if a.count(1) % 2 == 1 or a.count(1) == n:
        print('NO')
    elif a.count(1) == 0:
        print('YES')
        print(0)
    else:
        pos = [(0, 0)]
        last = -1
        for i in range(n):
            if a[i] != 1:
                continue
            if last == -1:
                last = i
            else:
                pos.append((last + 1, i + 1))
                last = -1
        pos.append((n + 1, n + 1))
        operations = []
        for i in range(1, len(pos)):
            if pos[i][0] - pos[i - 1][1] > 1:
                for j in range(i - 1, 0, -1):
                    solve(pos[j][0], pos[j][1], True)
                for j in range(i, len(pos) - 1):
                    solve(pos[j][0], pos[j][1], False)
                break
        if len(operations) > 0:
            print('YES')
            print(len(operations))
            print(' '.join(map(str, operations)))
        else:
            for i in range(1, len(pos) - 1):
                if pos[i][0] % 2 == pos[i][1] % 2:
                    for j in range(pos[i][0], pos[i][1] - 2, 2):
                        operations.append(j)
                    for j in range(pos[i][1] - 2, pos[i][0] - 2, -2):
                        operations.append(j)
                    for j in range(i - 1, 0, -1):
                        solve(pos[j][0], pos[j][1], True)
                    for j in range(i + 1, len(pos) - 1):
                        solve(pos[j][0], pos[j][1], False)
                    break
            if len(operations) > 0:
                print('YES')
                print(len(operations))
                print(' '.join(map(str, operations)))
            else:
                print('NO')
```

---

## 作者：tzc_wk (赞：1)

> 摘自我的 [贪心/构造/DP 杂题选做Ⅱ](https://www.cnblogs.com/ET2006/p/greedy-construction-dp2.html) 中的第 $36$ 题

提供一个大分类讨论做法，~~大家看着玩玩嘲讽嘲讽这个 sb 就好了~~

首先，如果 $1$ 的个数为奇数，那么由于每次操作不会改变序列中 $1$ 的个数的奇偶性，因此肯定无法将序列中所有元素均变为 $0$。

而如果 $1$ 的个数为偶数，也不一定存在合法解，详情见样例的第三组数据（

那么我们如何判定是否存在合法解以及构造出符合要求的解呢？首先特判掉全部为 $1$ 的情况，此时必然不存在合法解。而对于更普适的情况，我们先求出每个全部由 $1$ 组成的连续段，假设为 $[l_1,r_1],[l_2,r_2],\cdots,[l_m,r_m]$，那么我们考虑从左到右依次消除每个连续段，分情况讨论：

- 如果我们待消除的这个连续段 $[l_i,r_i]$ 长度为偶数，那么如果 $l_i\ne 1$，直接依次执行 $l_i-1,l_i+1,l_i+3,\cdots,r_i-1$ 即可搞定这个连续段，否则依次执行 $r_i-1,r_i-3,\cdots,l_i$ 也可搞定这个连续段。由于 $a_i$ 不全为 $1$，所以 $l_i=1$ 与 $r_i=n$ 不同时成立，因此构造合法。
- 如果我们待消除的连续段长度为奇数，这部分比较麻烦。设 $d$ 为当前连续段右端点与下个连续段左端点的距离，继续分情况讨论：
  - 如果 $d$ 为偶数，那么我们依次执行 $r_i,r_i+2,\cdots,l_{i+1}-4,l_{i+1}-2,l_{i+1}-4,l_{i+1}-6,\cdots,l_i+2,l_i$ 即可将 $[l_i,r_i]$ 全部变为 $0$，同时将下一连续段的长度减一。
  - 如果 $d$ 为奇数，继续分类讨论：
    - 如果这一段左端点不是 $1$，那么依次执行 $l_i-1,l_i+1,l_i+3,\cdots,r_i-3,r_i,r_i+2,\cdots,l_{i+1-3},r_i-1,r_i+1,r_i+3,\cdots,l_{i+1}-2$，这样也可达到将 $[l_i,r_i]$ 全部变为 $0$，同时将下一连续段的长度减一的效果。
    - 如果这一段左端点是 $1$，那么我们会选择用下一段去消当前这一段，分情况讨论：
      - 如果 $r_{i+1}=n$，那么无解。
      - 如果 $r_{i+1}-l_{i+1}+1$ 为奇数，那么我们依次执行 $r_i,r_i+2,\cdots,l_{i+1}-3,r_{i+1}-1,r_{i+1}-3,\cdots,l_i$，这样可以将两段同时消没。
      - 如果 $r_{i+1}-l_{i+1}+1$ 为偶数，那么我们依次执行 $r_i,r_i+2,\cdots,l_{i+1}-3$，这样可将两段合并起来，作为新的 $[l_{i+1},r_{i+1}]$。

~~于是这道思维题成功被我做成了一道大分类讨论题（大雾~~

时间复杂度线性。

```cpp
const int MAXN=2e5;
int n,a[MAXN+5];vector<int> res;
void oper(int x){
	int sum=a[x]^a[x+1]^a[x+2];
	a[x]=a[x+1]=a[x+2]=sum;
	res.pb(x);
}
void solve(){
	scanf("%d",&n);int sum=0,flg=1;res.clear();
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),sum+=a[i],flg&=a[i];
	a[n+1]=0;if((sum&1)||flg) return puts("NO"),void();
	int msk=0;vector<pii> vec;bool rev=0;
	for(int l=1,r;l<=n;l=r){
		if(a[l]){
			r=l;while(a[r]) ++r;
			vec.pb(mp(l,r-1));
		} else r=l+1;
	}
	for(int i=0;i<vec.size();i++){
		if((vec[i].se-vec[i].fi+1)&1){
//			printf("%d %d\n",vec[i].fi,vec[i].se);
			if(i==(int)(vec.size())-1) assert(0);
			if(~(vec[i+1].fi-vec[i].se)&1){
				for(int j=vec[i].se;j<vec[i+1].fi;j+=2) oper(j);
				for(int j=vec[i+1].fi-4;j>=vec[i].fi;j-=2) oper(j);
				vec[i+1].fi++;
			} else {
				if(vec[i].fi!=1){
					for(int j=vec[i].se;j<vec[i+1].fi-1;j+=2) oper(j);
					for(int j=vec[i].fi-1;j<vec[i+1].fi;j+=2) oper(j);
					vec[i+1].fi++;
				} else if(vec[i+1].se!=n){
					for(int j=vec[i].se;j<vec[i+1].fi-1;j+=2) oper(j);
					if((vec[i+1].se-vec[i+1].fi+1)&1){
						for(int j=vec[i+1].se-1;j>=vec[i].fi;j-=2) oper(j);
						vec[i+1]=mp(1,0);
					} else vec[i+1]=mp(vec[i].fi,vec[i+1].se);
				} else return puts("NO"),void();
			}
		} else {
			if(vec[i].se==n) for(int j=vec[i].fi-1;j<vec[i].se;j+=2) oper(j);
			else for(int j=vec[i].se-1;j>=vec[i].fi;j-=2) oper(j);
		}
	} printf("YES\n%llu\n",res.size());
	for(int x:res) printf("%d ",(rev)?(n-1-x):x);printf("\n");
}
int main(){
	int qu;scanf("%d",&qu);
	while(qu--) solve();
	return 0;
}
/*
1
9
1 0 0 0 1 0 1 0 1

1
8
0 1 1 1 0 0 1 0

1
6
1 0 1 1 0 1

1
10
1 0 0 1 0 0 1 0 0 1
*/
```

---

## 作者：lfxxx (赞：0)

好题。

操作比较奇怪，我们在前缀异或序列上考虑问题，不难发现操作相当于 $pre_i \gets pre_{i+2},pre_{i+1} \gets pre_{i-1}$。

奇数位置偶数位置相对独立，然后你发现偶数位置的 $pre$ 可以从 $pre_0$ 处借来一个 $0$，所以不妨先考虑处理奇数位置，最后再操作 $1,3,5,\dots$ 来将偶数位置全部变成 $0$。

显然奇数位置必须有一个 $0$，然后就可以通过操作来将这个 $0$ 向前或者向后移动了。

注意到 $pre_n$ 没法改变，所以必须是 $0$，这个特判。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5+114;
int a[maxn];
int n;
void work(){
    cin>>n;
    int st=1;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        a[i]^=a[i-1];
        if(i%2==1) st&=a[i];
    }
    if(a[n]==1){
        cout<<"NO\n";
        return ;
    }
    if(st==1){
        cout<<"NO\n";
        return ;
    }
    cout<<"YES\n";
    vector<int> opt;
    int key=1;
    for(int i=1;i<=n;i++){
        if(i%2==1&&a[i]==0) key=i;
    }
    for(int i=key-2;i>=1;i-=2){
        if(a[i]==1) opt.push_back(i),a[i]=0;
    }
    for(int i=key+2;i+1<=n;i+=2){
        if(a[i]==1) opt.push_back(i-1),a[i]=0;
    }
    for(int i=1;i+2<=n;i+=2){
        opt.push_back(i);
    }
    cout<<opt.size()<<'\n';
    for(int x:opt) cout<<x<<" ";
    cout<<'\n';
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;
    cin>>t;
    while(t--) work();
    return 0;
}
```

---

## 作者：RockyYue (赞：0)

#### 1572B

给定 $a_{1\dots n}$（原题描述为 $01$ 序列，其实非负整数序列即可），每次可以选择相邻三个数（无循环）将其全部替换为这三个数异或和，求一种 $n$ 次操作内将所有数变为 $0$ 的构造，要求 $O(n)$。

#### Sol

- 这种一次操作前几个数的题，考虑在前缀和/差分（类似的如前缀异或同样）序列上操作，可能同样只影响一部分，且可以简化操作。
- 知道每次操作后整体异或和不变，故要求初始异或和为 $0$。
- 取 $s$ 为 $a$ 前缀异或，发现操作 $i,i+1,i+2$ 对 $s$ 的影响为 $s_i:=s_{i+2},s_{i+1}:=s_{i-1}$，于是在 $s$ 上操作，有条件 $s_0=s_n=0$。
- 发现赋值是在奇/偶下标位内部分别进行的，故初始奇偶下标位都需要有 $s$ 为 $0$，先不考虑另一个将其中一个内部全赋为 $0$，接下来不需要考虑这个将另一个赋为 $0$ 即可，每次操作赋一位，可以实现。
- 对于偶数位有 $s_0=0$，找一个奇数位为 $0$，设为 $s_x$，对 $s_{x-2,x-4,\dots 1}$ 依次操作使这些位为 $0$，再对 $s_{x+1,x+3,\dots n-2/n-1}$ 依次操作，使这些位的后一位为 $0$，然后考虑偶数，对所有偶数位从小到大操作。

---

## 作者：shinkuu (赞：0)

简单题，认为自己的方法较简短，所以分享一下。

首先显然 $1$ 的个数为奇数无解，然后发现如果有一个长度为偶数的极长 $1$ 段 $[l,r]$，则可以通过操作 $l-1,l+1,l+3,\cdots$ 或 $r-1,r-3,r-5,\cdots$ 来全部置 $0$。

如果长度为奇数怎么办？发现可以通过操作 $r,r+2,r+4,\cdots$ 不断往后面加两个 $1$。如果这个段和后面的极长 $1$ 段接上了，那么将 $r$ 往后移，否则如果 $a_{r+2}=1$，则可以操作 $r$，使得前面和后面极长 $1$ 段的长度 $-1$，变成偶数，就可以消掉了。

不断找到一个极长 $1$ 段往下做即可。细节不多。要注意，如果 $l=1,r=n$，说明此时 $a$ 全为 $1$，就不可能消掉了，也要特判。

为什么操作次数 $<n$？因为当一个 $1\to 0$ 后，不会再 $0\to 1$。每次又会改变两个数，所以上界为 $\dfrac{2\times n}{2}=n$。

code：

```cpp
int n,m,a[N];
vector<int> ans;
void Yorushika(){
	scanf("%d",&n);
	int s=0;
	rep(i,1,n)scanf("%d",&a[i]),s+=a[i];
	if(s&1)return puts("NO"),void(0);
	a[n+1]=a[n+2]=0,ans.clear();
	rep(i,1,n){
		if(!a[i])continue;
		int r=i;
		while(a[r+1])r++;
		while((r-i+1)&1){
			while(r<=n-2&&!a[r+1]&&!a[r+2])ans.eb(r),a[r+1]=a[r+2]=1,r+=2;
			if(a[r+1]){
				while(a[r+1])r++;
			}else if(r>n-2)break;
			else a[r]=a[r+2]=0,ans.eb(r--);
		}
		if((r-i+1)&1)return puts("NO"),void(0);
		if(i==1&&r==n)return puts("NO"),void(0);
		if(i==1){
			for(int j=r-1;j>=i;j-=2)ans.eb(j);
			i=r+1;
		}else{
			while(i<r)ans.eb(i-1),i+=2;
			i--;
		}
	}
	puts("YES");
	printf("%d\n",(int)ans.size());
	for(int i:ans)printf("%d ",i);
	if(ans.size())puts("");
}
signed main(){
	int t=1;
		scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

## 作者：wmy_goes_to_thu (赞：0)

首先，我的想法是用 $n-2$ 推出 $n$：

1. 把最后三个数做一次操作，即使得 $a_n=a_{n-1}$。

2. 把前面 $n-2$ 个数变成全 $0$。

3. 把最后三个数再做一次操作。

代码可以在[这里](https://www.luogu.com.cn/paste/ukm5fvrl)查看。

你会发现，当 $\sum\limits_{i=1}^{n}a_i$ 为奇数时一定无解，在我的代码里显然也会被判断为无解。

当 $n$ 为奇数时这样做会使得奇偶性不变，循环到 $n=3$ 时一定也是正确的，所以这需要考虑 $n$ 为偶数的情况。

你会发现，我这个代码会被 `1 0 0 1 0 0` 这样的数据 hack 掉，所以我们最好先打表。

你会发现，当 $a_1=0$ 或 $a_n=0$ 时可以转化为 $n$ 为奇数的情况，一定正确。

当 $a_1=a_n=1$ 时，如果 $a_{2k}=a_{2k+1}(\forall k)$ 的话，一定不行，因为会在这里一直转圈。

否则，一定可以，可以一个一个破，可以看看我的[代码](https://www.luogu.com.cn/paste/5yvq71lh)。

---

