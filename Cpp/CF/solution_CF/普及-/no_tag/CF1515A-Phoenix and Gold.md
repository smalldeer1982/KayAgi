# Phoenix and Gold

## 题目描述

Phoenix has collected $ n $ pieces of gold, and he wants to weigh them together so he can feel rich. The $ i $ -th piece of gold has weight $ w_i $ . All weights are distinct. He will put his $ n $ pieces of gold on a weight scale, one piece at a time.

The scale has an unusual defect: if the total weight on it is exactly $ x $ , it will explode. Can he put all $ n $ gold pieces onto the scale in some order, without the scale exploding during the process? If so, help him find some possible order.

Formally, rearrange the array $ w $ so that for each $ i $ $ (1 \le i \le n) $ , $ \sum\limits_{j = 1}^{i}w_j \ne x $ .

## 说明/提示

In the first test case, Phoenix puts the gold piece with weight $ 3 $ on the scale first, then the piece with weight $ 2 $ , and finally the piece with weight $ 1 $ . The total weight on the scale is $ 3 $ , then $ 5 $ , then $ 6 $ . The scale does not explode because the total weight on the scale is never $ 2 $ .

In the second test case, the total weight on the scale is $ 8 $ , $ 9 $ , $ 11 $ , $ 14 $ , then $ 18 $ . It is never $ 3 $ .

In the third test case, Phoenix must put the gold piece with weight $ 5 $ on the scale, and the scale will always explode.

## 样例 #1

### 输入

```
3
3 2
3 2 1
5 3
1 2 3 4 8
1 5
5```

### 输出

```
YES
3 2 1
YES
8 1 2 3 4
NO```

# 题解

## 作者：Ninelife_Cat (赞：5)

~~我知道这题是构造，但我就是要乱搞，诶，就是玩~~。

提供一种乱搞做法：每次随机打乱给出的序列，进行模拟，判断是否合法。

至于无解嘛…只要重复进行多次操作还不能得出答案，那我们就可以认为它是无解的。

我们可以使用一个玄学的东西 ```random_shuffle```，这个东西的作用就是随机打乱一段序列，用法和 ```sort``` 差不多。

```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define ri register
#define int long long
#define inf 2147483647
#define mp(x,y) make_pair((x),(y))
#define reset(x,y) memset((x),(y),sizeof((x)))
using namespace std;
inline int read()
{
	int x=0;bool f=false;char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') f=true;c=getchar();}
	while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+(c^'0');c=getchar();}
	return f?-x:x;
}
int t,n,m,a[101];
signed main()
{
	t=read();
	while(t--)
	{
		n=read();m=read();
		for(ri int i=1;i<=n;++i)
			a[i]=read();
		ri bool flag=0;//flag记录答案是否合法
		for(ri int i=1;i<=1000;++i)//重复操作
		{
			random_shuffle(a+1,a+n+1);
			ri int cnt=0,f=0;
			for(ri int j=1;j<=n;++j)
				cnt+=a[j],cnt==m&&(f=1);
              		//如果不合法,就舍去
			if(!f) {flag=1;break;}
		}
		if(flag)
		{
			cout<<"YES\n";
			for(ri int i=1;i<=n;++i)
				cout<<a[i]<<" ";
			cout<<endl;
		}
		else cout<<"NO\n";
	}
	return 0;
}

---

## 作者：_easy_ (赞：2)

## 题意简述
给你一个数组，让你改变数的顺序，让他没有任何一项的前缀和为给定的 $x$，不能则输出 $NO$。
## 思路
此题可分为两种情况讨论：
- 在数组总和为 $x$ 时，无论如何都不可能完成，直接输出 $NO$。
- 其余全部输出 $YES$，然后遍历一遍，遇到前缀和为 $x$ 的就交换并输出。
## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int t,n,x,a[105],sum;
int main(){
	cin>>t;
	while(t--){
		cin>>n>>x;
		sum=0;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			sum+=a[i];
		}
		if(sum==x){
			cout<<"NO"<<endl;
			continue;
		}
		cout<<"YES"<<endl;
		sum=0;
		for(int i=1;i<=n;i++){
			sum+=a[i];
			if(sum==x){
				swap(a[i+1],a[i]);
				cout<<a[i]<<" "<<a[i+1]<<" ";
				i++;
				sum+=a[i];
			}else{
				cout<<a[i]<<" ";
			}
		}
		cout<<endl;
	}
    return 0;
}
```
[AC记录](https://www.luogu.com.cn/record/56300758)

---

## 作者：feicheng (赞：1)

## Description

给定序列 $a$ 和整数 $x$，重排序列使得 $a$ 的任何一个前缀和都不等于 $x$，求一种方案，无解输出 `NO`。多测。

**限制**：$1\le t\le10^3,1\le n\le100,1\le x\le10^4$

## Solution

这个做法十分的玄学。

首先我们要使任意一个前缀和不等于 $x$，肯定是要想将尽可能大的数放在前面而让前缀和超过 $x$，但是加的过程不能产生 $x$，所以算法的思路就诞生了。

1. 将序列从大到小排序。
2. 从前往后遍历序列，加到答案数组里，如果加出 $x$，则跳过该数。
3. 将所有跳过的数加在答案数组尾端。
4. 检验是否有前缀和等于 $x$。

时间复杂度 $\mathcal{O}(Tn\log n)$

## Code

```cpp
inline void solve() {
    v.clear() ;
    memset(vis,0,sizeof vis) ;
    memset(a,0,sizeof a) ;
    cin >> n >> x;
    for(int i = 1;i <= n;++i) cin >> a[i];
    std::sort(a+1,a+1+n,[](const int p,const int q) {return p > q;}) ;
    int sum = 0 ;
    for(int i = 1;i <= n;++i) {
        if(sum > x) break ;
        if(sum + a[i] != x) {
            sum += a[i] ;
            v.push_back(a[i]) ;
            vis[i] = 1 ;
        }
    }
    sum = 0 ;
    for(int i = 1;i <= n;++i) {
        if(!vis[i]) v.push_back(a[i]) ;
    }
/*  for(auto it : v) cout << it << " ";
    cout << endl ;*/
    for(auto it : v) {
        sum += it ;
        if(sum == x) return cout << "NO\n",void() ;
    }
    cout << "YES\n" ;
    for(auto it : v) cout << it << " " ;
    cout << endl ;
}
```

---

## 作者：pragma_GCC (赞：0)

# 题目大意
给定 $n$ 个数 $w[1],w[2],w[3]…w[n]$ 与 $x$，试构造 $w$ 数组的一排列，使得此排列的**任意一前缀和**均不等于 $x$。  
# 思路
一道分类讨论的经典思维题。  
考虑这 $n$ 个数的总和 $num$。  
- 若 $num < x$：此时输出 $w$ 的任意一排列均可。
- 若 $num = x$：此时无解。
- 若 $num > x$：此时，我们边输出边记录输出数的总和 $t$。若 
$$t+w[i]=x$$
则因为w数组里的数互不相同，只需 $ \operatorname{swap}(w[i],w[n])$ 即可。  
### 附上[ACcode](https://www.luogu.com.cn/record/122551102)
```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#pragma GCC target("sse,sse2,sse3,sse4,popcnt,abm,mmx,avx,avx2")
using namespace std;
int n,t,w[1001],x;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>t;
	while(t--){
		cin>>n>>x;
		int num=0;
		for(int i=1;i<=n;i++){
			cin>>w[i];
			num+=w[i];
		}
		if(num<x){
			/*直接输出*/
			cout<<"YES\n";
			for(int i=1;i<=n;i++){
				cout<<w[i]<<' ';
			}
			cout<<"\n";
		}else if(num==x){
			/*无论如何均不能使前缀和不为num*/
			cout<<"NO\n";
		}else{
			int t=0;
			cout<<"YES\n";
			for(int i=1;i<=n;i++){
				if(w[i]+t==x){
					/*如果前缀和为x,那就交换w[i]与w[n]*/
					swap(w[i],w[n]);
				}
				cout<<w[i]<<' ';
				t+=w[i];
			}
			cout<<'\n';
		}
	}
	return 0;
}
```

---

## 作者：zzy_zhouzhiyuan (赞：0)

#### 题目大意
给定一个长度为 $n$ 的数组 $w$ 和一个数 $x$。问能否改变数组的排列顺序使得数组的每个前缀和不等于 $x$。
#### 思路分析
先思考无解的情况。当数组所有元素之和为 $x$ 时无解，输出 `NO`。其它情况都有解。因为题目中提到“数组中的数**各不相同**”，所以有解的情况可以使用随机化解决。不停地将原数组打乱重新排列，用前缀和判断当前数组是否满足条件。满足就输出 `YES`，并输出数组。

随机化数组使用 `random_shuffle` 函数。
#### AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,x;
int a[105],s[105];
int pd(){
	int k=0;
	for(int i=1;i<=n;i++){
		k+=a[i];
		if(k==x)return 0;
	}
	return 1;
}
int main(){
	cin>>t;
	while(t--){
		cin>>n>>x;
		int u=0;
		for(int i=1;i<=n;i++)cin>>a[i],u+=a[i];
		if(u==x){
			cout<<"NO\n";
			continue;
		}
		cout<<"YES\n";
		int q=100;
		while(q--){
			random_shuffle(a+1,a+n+1);
			if(pd()){
				for(int i=1;i<=n;i++)cout<<a[i]<<' ';
				break;
			}
		}
		cout<<"\n";
	}
}
```


---

## 作者：_VEGETABLE_OIer_xlc (赞：0)

[点我返回题目](https://www.luogu.com.cn/problem/CF1515A)

## 题意

给定一个长度为 $n$ 的数组 $w$，和一个数 $x$，要求改变数组的顺序，使数组的任何一项的前缀和不等于 $x$，问能不能做到。如果能，**还要输出改变后的数组**。

## 思路

很明显，当整个数组的和为 $x$ 时，是不能做到的。

其余情况都可以做到。

遍历一遍数组，如果遇到前缀和为 $x$ 的，交换相邻两个数，其余直接输出就行了。

话不多说，上代码！

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,x,a[110];
int main(){
	cin>>t;
	while(t--)
	{
		cin>>n>>x;
		int sum=0;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			sum+=a[i];
		}
		if(sum==x)
		{
			cout<<"NO"<<endl;
			continue; 
		}
		sum=0;
		cout<<"YES"<<endl;
		for(int i=1;i<=n;i++)
		{
			if(sum+a[i]==x)
				swap(a[i],a[i+1]);
			cout<<a[i]<<" ";
			sum+=a[i];
		}
		cout<<endl;
	}
	return 0;
} 
```


---

## 作者：_Extroversion (赞：0)

[进入博客获得更好阅读体验](https://www.luogu.com.cn/blog/alandy/cf1515a-phoenix-and-gold-ti-xie)
## 题目大意：
- 给定一个长度为 $n$ 的数组和一个数 $x$，数组中的数互不相同，要求重新排列这一个数组，使得排列后数组的每一个前缀和都不等于 $x$。


------------

不难发现，只要某个前缀和 $>x$，那么它后面的所有前缀和都不等于 $x$。

于是我们考虑一个做法，先将数组升序排序，按照顺序遍历，只要前缀和不等于 $x$，就不改变排列顺序，直接将数输出，如果排序后数组的某个前缀和等于 $x$，不妨设 $a_1 \sim a_i$ 的和等于 $x$，那么 $a_1 \sim a_{i-1}$ 的和加上 $a_{i+1}$ 一定 $>x$，那么将数组中 $a_i$ 的位置放到最后，所得序列一定每一个前缀和都不等于 $x$。

因为只会进行一次更改顺序，所以我们用一个变量记录放在最后的输出的 $a_i$，再将其他数按序输出即可。注意打上标记，保证该变量只被更新一次。

例：
```
5 3
1 2 3 4 8
```
用此做法所得序列为：
```
1 3 4 8 2
```
至于无解的情况，那就是当 $a_1 \sim a_i$ 的和等于 $x$ 时，不存在 $a_{i+1}$，即数组中所有元素的和等于 $x$，此时无论如何排列，都会计算 $a_1 \sim a_n$ 这个前缀的和。

所以我们可以先判断是否有解，无解直接输出并结束对此组数据的处理，有解就进行排序，按上述方法构造序列。
## Code:
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define N 110
using namespace std;
int T,n,a[N],cnt,x,p;//cnt累加前缀和 
int main(){
	scanf("%d",&T);
	while(T--){
		cnt=0;
		scanf("%d%d",&n,&x);
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			cnt+=a[i];
		}
		if(cnt==x){
			printf("NO\n");//特判，如果数组中所有元素的和等于x,那么直接输出NO。 
			continue;
		}
		printf("YES\n");//否则一定有解 
		sort(a+1,a+1+n);
		cnt=0;p=0;
		for(int i=1;i<=n;i++){
			cnt+=a[i];
			if(cnt>=x){//如果a[1]~a[i]的和<x，不做任何处理 
				p=a[i];//记录放在最后输出的数 
				i++;//跳过输出a[i]
				cnt=-0x3f3f3f3f;//由于后面也无需再改变顺序，将cnt设为负无穷，这样就不会再进入else里面了 
			}
			printf("%d ",a[i]);
		}
		if(p)//如果p的值不为0，即p进行过更新，才会输出p 
		printf("%d",p);
		printf("\n");
	}
	return 0;
}
```

求管理员通过qwq

---

## 作者：CQ_Bab (赞：0)

# 题目大意

给定你 $T$ 组数据，每组 $n$ 个数和一个数 $x$ 要求你，改变这个数组让这个数组的任何一项的前缀和都不等于 $x$，若不能则输出 NO。

# 思路

可以分为两种情况：

1. 若 $n$ 个数的总和为 $x$ 则直接输出 NO；
2. 其余全输出 YES，然后从 $1 \sim n$ 去遍历，前缀和为 $x$。则将第 $i$ 个数与第 $i+1$ 个数交换，因为题目中保证了 $n$ 个数各不相同所以前缀和也会随之变化。

# AC代码

```
#include<bits/stdc++.h>
using namespace std;
const int N=101;
int pre[N],a[N],n,x,t,sum;
int main() {
	cin>>t;//T组数据
	while(t--) {
		cin>>n>>x;//输入
		sum=0;//清零 
		for(int i=1; i<=n; i++) {
			cin>>a[i];//输入
			pre[i]=pre[i-1]+a[i];
			sum+=a[i];//求总和 
		}
		if(sum==x) {
			puts("NO");
			continue;
		}//特判
		for(int i=1;i<=n;i++){
			if(pre[i]==x){
				swap(a[i],a[i+1]);//交换 
				cout<<a[i]<<" "<<a[i+1]<<" ";
				i++;
			}else cout<<a[i]<<" ";
		} 
		puts("");
	}
	return 0;//结束自己罪恶的一生
}
```


---

## 作者：FutaRimeWoawaSete (赞：0)

构造好题。               

如果不是所有数相加为 m 的话就保证有解。                   

所有直接做前缀和，在 ```a[i]```非负的前提下，前缀和具有单调性，所以我们直接做前缀和，如果当前加到了 m 我们就直接交换一下前后两个数就行了。                

当然直接随机化一下这个序列也可以过，毕竟保证了所有数互不相同。               

~~根本卡不掉随机化啊。~~

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int Len = 1e2 + 5;
int n,m,a[Len];
int main()
{
	int t;scanf("%d",&t);
	while(t --)
	{
		scanf("%d %d",&n,&m);int sum = 0;
		for(int i = 1 ; i <= n ; i ++) 
		{
			scanf("%d",&a[i]);
			sum += a[i];
		}
		if((n == 1 && a[1] == m) || sum == m) 
		{
			puts("NO");
			continue;
		}
		while(1)
		{
			bool flag = true;
			random_shuffle(a + 1 , a + 1 + n);int xx = 0;
			for(int i = 1 ; i <= n ; i ++)
			{
				xx += a[i];
				if(xx == m) 
				{
					flag = false;
					break;
				}
			}
			if(flag) break;
		}	
		puts("YES");
		for(int i = 1 ; i <= n ; i ++) printf("%d ",a[i]); 
		puts("");
	}
	return 0;
}
```

---

## 作者：Light_snow (赞：0)

本文同步自[link](https://www.cnblogs.com/dixiao/p/14728152.html)

考虑判断是否存在一个前缀和不满足条件。

有后缀的话拉一个过来交换就行，否则就是没有方案。

```cpp
// code by fhq_treap
#include<bits/stdc++.h>
#define ll long long
#define N 300005
 
inline ll read(){
    char C=getchar();
    ll A=0 , F=1;
    while(('0' > C || C > '9') && (C != '-')) C=getchar();
    if(C == '-') F=-1 , C=getchar();
    while('0' <= C && C <= '9') A=(A << 1)+(A << 3)+(C - 48) , C=getchar();
    return A*F;
}
 
 
struct P{
	int to,next;
};
 
struct Map{
	P e[N << 1];
	int head[N],cnt;
	Map(){
		std::memset(head,0,sizeof(head));
		cnt = 0;
	}
	inline void add(int x,int y){
		e[++cnt].to = y;
		e[cnt].next = head[x];
		head[x] = cnt;
	}
};
 
ll t;
ll num[N];
ll n,k;
 
int main(){
	t = read();
	while(t -- ){
		n = read(),k = read();
		ll sum = 0,s = 0;
		for(int i = 1;i <= n;++i)
		num[i] = read(),s += num[i];
		if(s == k)
		puts("NO");
		else{
			puts("YES");
		for(int i = 1;i <= n;++i){
			sum += num[i];
			if(sum == k){
				std::cout<<num[i + 1]<<" "<<num[i]<<" ";
				++i;
			}
			else
			std::cout<<num[i]<<" ";
		}
			puts("");
		}
	}
}
```



---

## 作者：oimaster (赞：0)

显然如果所有金块的重量和等于 $x$，那么无论我们怎么放这个秤都会炸。

否则，我们按照正常顺序来进行放置。如果要放第 $i$ 块金子，但放上去后秤上重量和等于 $x$，我们就会暂时把它鸽掉，放完第 $i+1$ 块金子后再放第 $i$ 块。

这里就得说洛谷的题面坑，原题面：
> All weights are **distinct**.

distinct 在原题面中加粗提示您。如果前 $i$ 块的重量和等于 $x$，那么显然把第 $i$ 块替换成 $i+1$ 时重量会变化。

那么通过这个简单的方法，就可以写出代码：

```cpp
int n,k;
cin>>n>>k;
int a[n+1];
for(int i=1;i<=n;++i)
	cin>>a[i];
int sum=0;
for(int i=1;i<=n;++i)
	sum+=a[i];
if(sum==k){
	cout<<"NO"<<endl;
	return 0;
}
cout<<"YES"<<endl;
sum=0;
for(int i=1;i<=n;++i){
	if(sum+a[i]!=k){
		cout<<a[i]<<' ';
		sum+=a[i];
	}
	else{
		cout<<a[i+1]<<' '<<a[i]<<' ';
		sum+=a[i]+a[i+1];
		++i;
	}
}
cout<<endl;
```

---

## 作者：Meaninglessness (赞：0)

### A. Phoenix and Gold

**题目大意:**

> 给你 $n$ 个**互不相同的**数，将这 $n$ 个数排列，使得每个前缀和都不为 $x$。

***

**解题思路:**

分为三种情况来考虑。

①如果$\sum\limits_{i=1}^{n}w_i = x$ 输出NO。

②如果$\sum\limits_{i=1}^{n}w_i < x$ 输出YES，然后直接按顺序输出即可。

③如果$\sum\limits_{i=1}^{n}w_i > x$ 

输出YES。

将所有数按升序或降序排列，然后依次选前 $i$ 个数,如果此时的和为 $x$,就跳过这个数选下一个数，最后再选这个数。

***

**代码实现:[Code](https://www.luogu.com.cn/paste/6f9bluul)　时间复杂度:$O(Tn$ $log$ $n)$**

---

## 作者：LinkZelda (赞：0)

- **题意**：给定一个长度为 $n$ 序列 $w$（保证 $w_i$ 两两不同）和一个数 $x$，问是否可以将原序列重排后满足 $\forall i \in[1,n],\sum_{j=1}^{i}w_i\neq x$。若存在，输出一种方案。

- $Solution$:

思考怎么判断有无解，我们令 $Sum$ 表示序列中所有数的和，可以发现 $Sum<x$ 时，原序列任意一种排列方式都是合法的，直接输出原序列即可；当 $Sum=x$ 时，发现原序列任意一种排列方式都是不合法的，因为必定有 $\sum_{j=1}^n w_i=x$。

那么我们就考虑 $Sum>x$ 的构造方式。我们对原序列从小到大排序，然后求出前缀和，发现前缀和是单调上升的。那么我们直接暴力找出第一个位置满足这个位置的前缀和 $\geqslant x$。

如果这个位置的前缀和 $\neq x$，那么前面的所有前缀和和后面的所有前缀和必定也 $\neq x$，那直接输出该序列即可。

如果这个位置满足前缀和 $= x$，那我们可以将这个位置的数和 $w_n$ 交换（因为我们讨论的情况是 $Sum>x$ 的，那这个位置必定不是 $n$），因为题目保证 $w_i$ 两两不同，而且我们排序了，那么使得这个位置前缀和 $\neq x$ 后，原序列合法。

- [代码](https://www.luogu.com.cn/paste/da4mtfg1)

---

## 作者：BX_mot (赞：0)

## 1.  [题目](https://www.luogu.com.cn/problem/CF1515A)

## 2. 思路：

因为要**重新排列**，
所以**除 $\sum_{i=1}^n=x$ 之外，都是 YES** (记得输出)，
否则输出的 NO (记得换行)。

当 $\sum_{i=1}^p=x$ 时，应该重新排列 $a$ 数组，改变前缀和。

在这里，改变 $a_{i}$ 与 $a_{i+1}$ 即可改变，由于只有一个指定值 $x$，那么改变后前缀和就不会为 $x$($a_{i} \ne a_{i+1}$)。

## 3. 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
int t,n,x;
int a[888],q[888];
inline int read()//快读
{
	int x = 0, f = 1;
	char ch = getchar();
	while (!isdigit(ch))
	{
		if (ch == '-')
			f = -1;
		ch = getchar();
	}
	while (isdigit(ch))
	{
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * f;
}
signed main()
{
	cin>>t;
	while(t--){
		n=read();x=read();
		for(int i=1;i<=n;i++){
			a[i]=read();
			q[i]=q[i-1]+a[i];
		}
		if(q[n]!=x)
		{
			cout<<"Yes\n";//反例
			for(int i=1;i<=n;i++){
				if(q[i]==x)
				{
					swap(a[i+1],a[i]);
					cout<<a[i]<<' '<<a[i+1]<<' ';
					i++;
				}
				else cout<<a[i]<<" ";
			}
			cout<<'\n';
		}
		else
		{
			cout<<"No"<<'\n';//反例
		}
	}
}
```





---

