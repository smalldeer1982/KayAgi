# Stack Sorting

## 题目描述

Let's suppose you have an array $ a $ , a stack $ s $ (initially empty) and an array $ b $ (also initially empty).

You may perform the following operations until both $ a $ and $ s $ are empty:

- Take the first element of $ a $ , push it into $ s $ and remove it from $ a $ (if $ a $ is not empty);
- Take the top element from $ s $ , append it to the end of array $ b $ and remove it from $ s $ (if $ s $ is not empty).

You can perform these operations in arbitrary order.

If there exists a way to perform the operations such that array $ b $ is sorted in non-descending order in the end, then array $ a $ is called stack-sortable.

For example, $ [3,1,2] $ is stack-sortable, because $ b $ will be sorted if we perform the following operations:

1. Remove $ 3 $ from $ a $ and push it into $ s $ ;
2. Remove $ 1 $ from $ a $ and push it into $ s $ ;
3. Remove $ 1 $ from $ s $ and append it to the end of $ b $ ;
4. Remove $ 2 $ from $ a $ and push it into $ s $ ;
5. Remove $ 2 $ from $ s $ and append it to the end of $ b $ ;
6. Remove $ 3 $ from $ s $ and append it to the end of $ b $ .

After all these operations $ b=[1,2,3] $ , so $ [3,1,2] $ is stack-sortable. $ [2,3,1] $ is not stack-sortable.

You are given $ k $ first elements of some permutation $ p $ of size $ n $ (recall that a permutation of size $ n $ is an array of size $ n $ where each integer from $ 1 $ to $ n $ occurs exactly once). You have to restore the remaining $ n-k $ elements of this permutation so it is stack-sortable. If there are multiple answers, choose the answer such that $ p $ is lexicographically maximal (an array $ q $ is lexicographically greater than an array $ p $ iff there exists some integer $ k $ such that for every $ i<k $ $ q_{i}=p_{i} $ , and $ q_{k}>p_{k} $ ). You may not swap or change any of first $ k $ elements of the permutation.

Print the lexicographically maximal permutation $ p $ you can obtain.

If there exists no answer then output -1.

## 样例 #1

### 输入

```
5 3
3 2 1
```

### 输出

```
3 2 1 5 4 ```

## 样例 #2

### 输入

```
5 3
2 3 1
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
5 1
3
```

### 输出

```
3 2 1 5 4 ```

## 样例 #4

### 输入

```
5 2
3 4
```

### 输出

```
-1
```

# 题解

## 作者：Error_Eric (赞：9)

### 前言

哇紫题！

### 正文

我们定义 $f_{l,r}$一个可以用栈排序的数列，其中 $[l,r]$ 中的数都出现了恰好一次。

~~众所周知~~,$f_{l,r}$ 满足以下性质：

- 长度为 $r-l+1$ .

- 设其第一个数为 $x$ 那么 $f_{l,r}=[x]+f_{l,x-1}+f_{x+1,r} $.

- 字典序最大的 $f_{l,r}$ 为 $[r,r-1...l+1,l]$.

题目就可以转化为求字典序最长的 $f_{1,n}$ ，使得其前缀为给定的 $k$ 个数字。

那么可以递归解决。

举个例子:

input

```
5 3
3 2 1
```
sol:
```
 f[1][5]
=[3]+f[1][2]+f[4][5]
=[3]+([2]+f[1][1])+f[4][5]
=[3]+([2]+[1])+f[4][5]
=[3]+[2,1]+[5...4]
=[3,2,1]+[5,4]
=[3,2,1,5,4]
```

### Code

```cpp
#include<iostream>
#include<algorithm>
#include<stdio.h>
using namespace std;
#define rei register int
#define il inline
void readln(int&I){//快读不解释
	I=0;char C=getchar();
	while(!isdigit(C))C=getchar();
	while( isdigit(C))I=I*10+C-'0',C=getchar();
}
int n,k,p[200005];
void f(int b,int l,int r){//从 b 开始的最大的 f[l][r]
	if(l>r)return;//不存在这个l...r(上一个函数中p[b]==l)
	if(l==r)//区间缩小至1了,p[b]必然为l/r.
		if(p[b] and p[b]!=l)putchar('-'),putchar('1'),exit(0);//出现矛盾，无解。
		else return(void)(p[b]=l);//赋值，返回。
	if(p[b])//如果x已经给定
		if(l<=p[b] and p[b]<=r)f(b+1,l,p[b]-1),f(b+1+(p[b]-l),p[b]+1,r);//利用 f 的性质递归解决。
		else putchar('-'),putchar('1'),exit(0);//矛盾，无解。
	else for(rei i=0;i<=(r-l);i++)p[b+i]=r-i;//如果没有给定x，那么后面的也没有给定x，可以直接取字典序最大的。
}
int main(){
	readln(n),readln(k);
	for(rei i=1;i<=k;i++)readln(p[i]);//输入不解释
	f(1,1,n);//从一开始，构造最大的f[1][n]
	for(rei i=1;i<=n;i++)printf("%d ",p[i]);//输出不解释
} 
```

---

## 作者：BIGBUG (赞：6)

### 题目大意
一个排列有$n$个数，经过一个栈调整顺序之后能够按$1-n$顺序输出。给出它的前$k$个数，要补全整个排列，且使其字典序最大。

------------

这里我们由一个数据开始探究：

```
10 6
1 3 2 9 4 7
```
根据题意，给出的会是排列的前$k$个数，所以直接输出。

可以对给出的$k$个数进行处理，把可以整理的数直接整理。

模拟输入之后可以发现$1-4$已经整理好了，栈中剩下两个数`9 7`。

如果这时候栈中不是一个下降的序列，可以发现此时无解，直接输出`-1`。

对于数据来说，还有$5-10$没有输出。

此时要把$7$给移除的话，必须先输出$5-6$，又要求字典序最大，此时可以从大到小输出。

于是你发现一个规律，然后你可以用一个生动形象的图来表示它：

![](https://cdn.luogu.com.cn/upload/image_hosting/42bhy5qj.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

于是我们得出了代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
int n,k,i,j,a[N],b[N],p,d;
bool f=0;
int main(){
	scanf("%d%d",&n,&k);
	for(i=1;i<=k;++i){
		scanf("%d",&a[i]);
		b[++p]=a[i];
		while(b[p]==d+1) ++d,--p;
	}
	for(i=2;i<=p;++i)
		if(b[i]>b[i-1]) f=1;
	if(f) printf("-1");
	else{
		b[p+1]=d;
		for(i=1;i<=k;++i) printf("%d ",a[i]);
		for(i=p;i>=1;--i)
			for(j=b[i]-1;j>b[i+1];--j) printf("%d ",j);
		for(i=n;i>b[1];--i) printf("%d ",i);
	}
	return 0;
}
```

---

## 作者：_Rainlzy (赞：3)

### ~~一道恐怖如斯的**构造**题~~

让我们定义 $f(a,b)$ 为取值范围从 $a$ 到 $b$ 的合法数列，那么 $f(a,b)=x+f(a,x-1)+f(x+1,b)$。

如何证明呢？我们可以操作为在字符串 $s$ 中加入 $x$，再把 $f(a,x-1)$ 加入字符串 $s$，然后把 $f(a,x-1)$ 和 $x$ 分别加入 $a$，最后把 $f(x+1,a)$ 加入 $a$，这样就构造出了一个合法的。

然后**贪心**一下，假设当前区间没有**任何限制**，那么 $b$ 到 $a$ **倒着**填数，否则就填当前限定的数。如果当前无法填数，则不存在合法解，输出 `-1`。

主要代码如下：

```
void solve(const int &d,const int &e,const int &l,const int &r){//d为a，e为b
	if(l>r){
		for(int i=e;i>=d;i--)//倒着
			b[++b[0]]=i;
		return ;
	}
	int &x=b[++b[0]]=a[l];
	if(x<d||x>e){//无法填数
		puts("-1");
		exit(0);
	}
	solve(d,x-1,l+1,min(l+x-d,r));
	solve(x+1,e,l+x-d+1,r);
}
```


---

## 作者：Dovе (赞：3)

## 题目大意

&#8195;&#8195;给定 $k$ 个数，构造长度为 $n-k$ 的入栈顺序，使得 $n$ 个数可以实现 $1~...~n$ 的出栈顺序。如果不能 则输出 $-1$

## 大致思路

&#8195;&#8195;不难发现，如果在降序排列的过程中出现了转折，而且当降序排列的最小值以下还有应该更早输出的数没有输出时，就不能构造成功

&#8195;&#8195;举个例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/9q9y9o1h.png)

&#8195;&#8195;因为$1$，$2$ 在之后虽然成功出栈了，但是想要将 $3$ 弹出，需要先弹出 $7$ ，就会被 "困" 死

&#8195;&#8195;那么，该如何实现呢？

&#8195;&#8195;在前 $k$ 给定的数字中,先记录该数字已经存在，扔进栈中，并检查是否无解

```cpp
if(last>now) return !printf("-1\n");
```

&#8195;&#8195;如果不存在，我们需要将中间空缺的先出栈。

&#8195;&#8195;如上图中 $3$ 与 $5$ 中数字 $4$ ，发现在 $k$ 个给定的数中不存在，那么就需要先 $4$ 入栈并弹出，在进行后续操作

```cpp
 for(register int i=now;i>=last;--i)
            if(v[i]==0) Ans[++tot]=i,v[i]=1;
// v[i]：表示 i 是否已经处理过（出过栈了）
```

&#8195;&#8195;最后，在处理完给定的 $k$ 个数字之后，只需要把剩下的按照降序输出即可

## $Code$

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+50;
int n,k;
int a[maxn],v[maxn];
int Ans[maxn],tot=0;
int need=1;
stack<int> s;
int main()
{
    scanf("%d%d",&n,&k);
    for(register int i=1;i<=k;++i)
    {
        scanf("%d",&a[i]);
	    v[Ans[++tot]=a[i]]=1;//记录数字存在
        s.push(a[i]);
        while(!s.empty() && s.top()==need) s.pop(),++need;
        // 将可以弹出的先弹出
	}
	
    int last=1,now; // last 是上一个数字 now 是当前的数字
    while(!s.empty())
	{
		now=s.top(); s.pop();
        if(last>now) return !printf("-1\n"); // 无解
        
        for(register int i=now;i>=last;--i)
            if(v[i]==0) Ans[++tot]=i,v[i]=1; //填补空缺
        
        last=now;
    }
    
    for(register int i=n;i>=last;--i)
	  if(v[i]==0) Ans[++tot]=i; //剩余的降序输出
	  
    for(register int i=1;i<=tot;++i) printf("%d ",Ans[i]);
    return 0;
}
```

---

## 作者：TernaryTree (赞：2)

题意：给定一个 $1\sim n$ 全排列的前 $k$ 项，你需要将其补全，使得其可以按栈调整顺序输出，并且其字典序最大。

既然题目已经给你前 $k$ 个了，那么直接输出就好了。

剩下的怎么处理呢？

不难想到先对前 $k$ 个元素模拟栈。

当然，处理完前 $k$ 个数，栈里可能还有元素。

根据栈的先进后出后进先出的定义，可以知道模拟完栈里的元素如果不下降那么无解，输出 `-1`。

我们如何补元素使得这些元素可以顺序输出并且字典序最大呢？

比如说现在输入是

```
10 6
3 2 1 8 4 6
```

经过栈处理之后，$1\sim 4$ 都被处理完了，栈里剩下

```
8 6
```

这时候 $5\sim 10$ 还没处理。我们如何补 $5,7,9,10$ 使得其能顺序输出并且字典序最大呢？

首先，$6$ 后面只能是 $5$，因为一旦不下降就无解了。

然后对于 $8$ 后面，同样只能放 $7$。

最后把 $10$ 和 $9$ 按从大到小的顺序输出。

可以发现，对于栈里剩下长度为 $n'$ 的序列 $s$，有输出的序列为

$$s_{n'}-1\to z+1,s_{n'-1}- 1\to s_{n'}+1,\dots ,n\to s_1+1$$

```cpp
#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5 + 1;

int n, m;
int a[maxn];
int vis[maxn];
int b[maxn], t;
stack<int> s;
int cnt = 1;

int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> a[i];
        s.push(a[i]);
        vis[a[i]] = 1;
        while (!s.empty() && s.top() == cnt) {
            s.pop();
            cnt++;
        }
    }
    bool flag = false;
    if (!s.empty()) {
        int last = s.top();
        b[++t] = last;
        s.pop();
        while (!s.empty()) {
            if (s.top() < last) {
                flag = true;
                break;
            }
            last = s.top();
            b[++t] = last;
            s.pop();
        }
    }
    if (flag) {
        cout << "-1" << endl;
        return 0;
    }
    for (int i = 1; i <= m; i++) {
        cout << a[i] << " ";
    }
    for (int i = 1; i <= t; i++) {
        int k = b[i] - 1;
        while (!vis[k] && k >= 1) {
            cout << k << " ";
            vis[k] = 1;
            k--;
        }
    }
    int k = n;
    while (!vis[k] && k >= 1) {
        cout << k << " ";
        vis[k] = 1;
        k--;
    }
    return 0;
}
```

---

## 作者：尹昱钦 (赞：1)

## 题目理解
给你一个栈和一个序列，让你在这个序列的末尾加入剩下的元素，要求能够利用这个栈使弹出顺序符合 $1\to n$ 的顺序。

## 思路
我们不难发现：
-  栈内元素清空后，剩下的元素从大到小放入答案序列尾部。
-  比栈顶元素小的元素在栈底则无解。

把给定的元素全部压入栈中，压入栈的过程中同时**能弹出就弹出**（要符合字典序，即从 $1$ 开始），然后对剩下的元素进行处理——

对每一个栈顶元素 $k$，**比 $k$ 小的元素一定要比 $k$ 先出栈**，所以应把**从 $k-1$ 到上一个栈顶元素之间的数字**放到答案序列中（**倒序**的目的是使答案字典序最大），最后弹出此栈顶元素。若发现这些数字有的已经在栈中了，则**无解输出 $-1$**。

清空完栈后，按照结论 $1$，把剩下的元素从大到小放入答案序列尾部即可。

实际上，这个栈就类似一个**单调栈**。

## 代码
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<iomanip>
#include<cmath>
#include<stack>
using namespace std;
const int maxn=200005;
int n,k,cnt=1; 
int vis[maxn],a[maxn];
stack<int> s;
int main(){
	cin>>n>>k;
	for(int i=1;i<=k;i++){
		scanf("%d",&a[i]);
		vis[a[i]]=1;
		s.push(a[i]);
		while(!s.empty()&&s.top()==cnt){
			cnt++;
			s.pop();
			continue;
		}
	}
	while(!s.empty()){
		for(int i=s.top()-1;i>=cnt;i--){
			if(vis[i]){
				cout<<-1;
				return 0;
			}
			a[++k]=i;
			vis[i]=1;
		}
		cnt=s.top()+1;
		s.pop();
	}
	for(int i=n;i>=cnt;i--){
		a[++k]=i;
	}
	for(int i=1;i<=n;i++){
		cout<<a[i]<<" ";
	}
    return 0;
}
```


---

## 作者：jucason_xu (赞：0)

如果一个排列 $A$、一个栈 $S$ 和一个空序列 $B$ 可以通过依次交错进行“从 $A$ 的头部弹出入栈”和“从栈弹出到 $B$ 的尾部”得到一个有序序列 $B$，则称这个序列 $A$ 是可以栈排序的。

现在给出序列 $A$ 的前 $k$ 项，求输出字典序最大的可以栈排序的序列 $A$。

容易发现，无论任何时候，我们都必须满足栈中的元素从栈顶到栈底递增。否则大的数一定会在小的数之前进入序列。

那么先对前 $k$ 项维护这个栈。为了让它尽可能的单调，对于栈顶的每一个元素，只要它是可以出栈的（恰好是 $B$ 序列尾部的值 $+1$），我们就让它出栈。如果最后这个栈不是单调的，就可以直接输出 $-1$，否则一定有解。

接下来考虑如何根据当前的栈确定接下来的 $A$ 排列。

我们考虑当前栈顶的数是 $x$，$B$ 末尾的数是 $y$，那么为了让 $x$ 出栈，开区间 $(y,x)$ 中的所有数都需要先入栈。那么考虑它们的入栈顺序。那么字典序最大的方案是什么呢？肯定是从 $y-1$ 到 $x+1$ 逆序加入。这样一定可以吗？一定可以，我们可以把它们都加入栈中然后再弹出。

这样，我们就可以得到一个做法：先处理出栈，判断单调性，然后每次对于栈顶的数，把它和序列尾部的数倒序压入 $A$ 中，弹栈，直到 $[1,n]$ 全部入栈即可。

复杂度是线性，$O(n)$。

```cpp
#define rp(i,n) for(int i=1;i<=n;i++)
#define vt vector
#define pb push_back
int n,k,a[200005],d;
int cnt[200005],lst=0;
vt<int>v,s;
bool cmp(int a,int b){
	return a>b;
}
bool chk(){
	int lst=0;
	rp(i,k){
		while(s.size()&&s.back()==lst+1)s.pop_back(),lst++;
		s.pb(a[i]);
	}
	while(s.size()&&s.back()==lst+1)s.pop_back(),lst++;
	return is_sorted(s.begin(),s.end(),cmp);
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n>>k;
	rp(i,k)cin>>a[i];
	if(!chk()){
		cout<<-1<<endl;
		return 0;
	}
	rp(i,k)cnt[a[i]]=1;
	cnt[n+1]=1;
	rp(i,n+1){
		if(cnt[i]){
			reverse(v.begin(),v.end());
			for(auto j:v)a[++k]=j;
			v.clear();
		}else v.pb(i);
	}
	rp(i,n)cout<<a[i]<<" ";
	cout<<endl;
	return 0;
}
//Crayan_r

```


---

