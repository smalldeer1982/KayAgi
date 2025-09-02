# TWINSNOW - Snowflakes

## 题目描述

你可能听说过，没有两片雪花是相同的。你要写一个程序，判断这是不是真的。你的程序会读到一些有关于这些雪花的信息，找到一对完全相同的雪花。每片雪花有六个角。对于每个雪花，你的程序会获得每个角的长度。我们认为两片雪花相同，当且仅当它们各自从某一个角开始，逆时针或顺时针记录长度，能得到两个相同的六元组。

# 题解

## 作者：_Felix (赞：5)

首先友情提醒一下，~~搬题目的放漏了~~这题样例其实就是
```
input
2
1 2 3 4 5 6
4 3 2 1 6 5
output
Twin snowflakes found.
```

这题我做的很窝火，终于AC了，写篇题解添加点成就感。。。

------------

一开始我以为是简单题，打算先找到每朵雪花中最小的数，顺时针逆时针都算一下，找字典序最小的

然后愉快WA0。因为一个雪花的手臂长度可能有相同的，比如什么1 2 1 3 1 6这种，我的想法就炸了。

-----------
那怎么找到一个唯一的表示方法呢？

最小表示法，不知道的可以看[P1368](https://www.luogu.com.cn/problem/P1368)

[工艺的题解中这篇较详细](https://www.luogu.com.cn/blog/partychicken/zui-xiao-biao-shi-fa-yang-xie)

最小表示法有了，接下来咋办？不能用普通数组记录是否访问过，因为数据范围太大了。

有人会说hash。但是那太麻烦了~~其实是我不会~~。

懒人标配：map<pos,int>mp;

(pos是存雪花六个手臂的结构体）

```
struct pos{
	int a[10];
}snow[N];
```
太棒了！我们成功了！

以下是在**洛谷**AC代码，1.42s,我最多只能把它优化到1.05s。POJ无法AC，所以代码下面我会给出另一个稍有不同方法。

```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define debug printf("*");
//#define mo 1e9+7
#define inf 1e9+7
int n;
bool flag;
struct pos{
	int a[10];
	bool operator < (const pos xx) const{
		for(int i=1;i<=6;i++){
			if(xx.a[i]==a[i]) continue;
			return a[i]>xx.a[i];
		}
		return a[6]>xx.a[6];
	}
};
map<pos,int>mp;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int o[15],o2[15],it1=1,it2=2,l,ans;
		for(int j=1;j<=6;j++){
			scanf("%d",&o[j]);
			o2[7-j]=o2[7-j+6]=o[j+6]=o[j];
		}
		while(it1<=6&&it2<=6){
			l=0;
			while(l<=6&&o[it1+l]==o[it2+l]) l++;
			if(l==7){
				ans=it1;break;
			}
			if(o[it1+l]>o[it2+l]) it1=it1+l+1;
			else it2=it2+l+1;
			if(it1==it2) it2++;
		}
		ans=min(it1,it2);
		pos x,y;
		for(int j=ans;j<=ans+6-1;j++){
			x.a[j-ans+1]=o[j];
		}
		
		it1=1,it2=2;
		while(it1<=6&&it2<=6){
			l=0;
			while(l<=6&&o2[it1+l]==o2[it2+l]) l++;
			if(l==7){
				ans=it1;break;
			}
			if(o2[it1+l]>o2[it2+l]) it1=it1+l+1;
			else it2=it2+l+1;
			if(it1==it2) it2++;
		}
		ans=min(it1,it2);
		for(int j=ans;j<=ans+6-1;j++)
			y.a[j-ans+1]=o2[j];
		if(y<x){
			mp[x]++;
		}
		else mp[y]++;
		if(mp[x]>1||mp[y]>1) flag=1;
	}
	if(flag) printf("Twin snowflakes found.\n");
	else printf("No two snowflakes are alike.\n");
	return 0;
}
```
------------
兴高采烈地去老师的比赛提交——TLE*3

~~POJ机子很慢，4s时限我洛谷跑1.42s还过不去~~

咋办？都怪map常数大，那就换掉。

哈希？不太会。弄个简单版的。
```
int clac(pos emm){
	int sum=0;
	for(int i=1;i<=6;i++)
		sum=(sum+emm.a[i])%mo;
	return sum;
}
```

雪花手臂之和%99991即可。

> 为什么要取99991？因为接近n的大小。

哈希之后可能会碰撞，所以我们要把clac值相同的给存起来，遇到有相同的就看看是不是真的相等。

别的题解用的是链式前向星，但是我喜欢STL，所以用了vector，会慢一些。

下面这个代码洛谷780msAC，POJ3829ms,vjudge上是3907ms

~~（我也不知道为什么vjudge和poj差了一点~~

```
#include<iostream>
#include<vector>
#include<stdio.h>
using namespace std;
//const int N=,mo=;
//#define inf
//#define long long ll
const int mo=99991,N=100010;
int hs[mo+10],n;
struct pos{
	int a[10];
}snow[N];
vector<pos>vec[mo+10]; 
int ok(pos al,pos ar){
	for(int i=1;i<=6;i++){
		if(al.a[i]>ar.a[i]) return -1;
		if(al.a[i]<ar.a[i]) return 1;
	}
	return 0;
}
int clac(pos emm){
	int sum=0;
	for(int i=1;i<=6;i++)
		sum=(sum+emm.a[i])%mo;
	return sum;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int o[15],o2[15],it1=1,it2=2,l,ans;
		for(int j=1;j<=6;j++){
			scanf("%d",&o[j]);
			o2[7-j]=o2[7-j+6]=o[j+6]=o[j];
		}
		while(it1<=6&&it2<=6){
			l=0;
			while(l<=6&&o[it1+l]==o[it2+l]) l++;
			if(l==7){
				ans=it1;break;
			}
			if(o[it1+l]>o[it2+l]) it1=it1+l+1;
			else it2=it2+l+1;
			if(it1==it2) it2++;
		}
		ans=min(it1,it2);
		pos x,y;
		for(int j=ans;j<=ans+6-1;j++){
			x.a[j-ans+1]=o[j];
		}
		
		it1=1,it2=2;
		while(it1<=6&&it2<=6){
			l=0;
			while(l<=6&&o2[it1+l]==o2[it2+l]) l++;
			if(l==7){
				ans=it1;break;
			}
			if(o2[it1+l]>o2[it2+l]) it1=it1+l+1;
			else it2=it2+l+1;
			if(it1==it2) it2++;
		}
		ans=min(it1,it2);
		for(int j=ans;j<=ans+6-1;j++)
			y.a[j-ans+1]=o2[j];
		pos qwq;
		if(ok(x,y)==1) qwq=x;
		else qwq=y;
		snow[i]=qwq;
		int tmp=clac(qwq);
		for(int i=0;i<vec[tmp].size();i++){
			pos v=vec[tmp][i];
			if(ok(v,qwq)==0){
				printf("Twin snowflakes found.\n");
				return 0;
			}
		}
		vec[tmp].push_back(qwq);
	}
	printf("No two snowflakes are alike.\n");
	return 0;
}
```

---

## 作者：D2T1 (赞：2)

[$\color{blue}{\text {pwp }{\to\textbf{My blog}\gets}}\text{qwq}$](https://www.luogu.com.cn/blog/390770/blogcenter)

洛谷的翻译不太清楚，这里是acwing题目链接：[https://www.acwing.com/problem/content/139/](https://www.acwing.com/problem/content/139/)

## 题解

算法：`hash`+邻接表+（最小表示法）

过程：

- 读入雪花 $a$，进行 `hash`，得到一个值 $h$

- 如果邻接表中有 `hash` 值为 $h$ 的雪花，依次遍历这些雪花，与雪花 $a$ 进行比较是否相同（可以使用暴力或最小表示法）

- 如果相同输出 `Twin snowflakes found.`，否则继续读入

代码：

```cpp
//SP4354
#include <cstring>
#include <cstdio>
typedef long long ll;
const int N=100010,P=99991;
int n,Snow[N][6],Head[N],Next[N],tot,a[10];

int Hash(int *a){
	// Hash 函数
	// Hash(a) = sum(i=1->6){a[i]}+mul(i=1->6){a[i]}
	int sum=0,mul=1;
	for(int i=0; i<6; ++i)
		sum=(sum+a[i])%P, mul=(ll)mul*a[i]%P;
	return (sum+mul)%P;
}
bool isequal(int *a,int *b){
	//判断两片雪花是否相等
	//暴力枚举两片雪花的“起始角”
	//判断一下，第二片翻过来再判断一下 
	for(int i=0; i<6; ++i){
		for(int j=0; j<6; ++j){
			
			bool yes=true;
			for(int k=0; k<6; ++k) if(a[(i+k)%6]!=b[(j+k)%6]) yes=false;
			if(yes) return true;
			
			yes=true;
			for(int k=0; k<6; ++k) if(a[(i+k)%6]!=b[(j-k+6)%6]) yes=false;
			if(yes) return true;
			
		}
	}
	return false;
}
bool findandinsert(int *a){
	//链式前向星邻接表 
	
	int h=Hash(a);
	for(int i=Head[h]; i; i=Next[i])
		if(isequal(Snow[i],a)) return true;
		
	++tot;
	memcpy(Snow[tot],a,6*sizeof(int));
	Next[tot]=Head[h],Head[h]=tot;
	
	return false;
}

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; ++i){
		for(int j=0; j<6; ++j)
			scanf("%d",&a[j]);
		if(findandinsert(a))
			return puts("Twin snowflakes found.")&0;
	}
	return puts("No two snowflakes are alike.")&0;
}
//qwq~~
```

---

## 作者：mulberror (赞：2)

我来提供一个用指针（前向星存图）实现查询的题解。

---
# 关于超级暴力解法
首先我们考虑一种hash超级暴力，每次算出转好的数组的hash值，然后用map来映射，判断是否是出现过。  
**ps.** 这个时候我们不能用布尔变量来存储，而是要用数值来存储，因为可能一个数组转过后还是和自己是一样的，造成了我自己和我自己一样的错误答案。
```cpp
#include <cstdio>
#include <map>
#define N 100005
#define uLL unsigned long long 
#define Base 401
using namespace std;
inline char gc() {
    static char buf[1 << 16], *S, *T;
    if (S == T) {
        T = (S = buf) + fread(buf, 1, 1 << 16, stdin);
        if (T == S) return EOF;
    }
    return *S ++;
}
template <typename T>
inline void read(T &x) {
    T w = 1;
    x = 0;
    char ch = gc();
    while (ch < '0' || ch > '9') {
        if (ch == '-') w = -1;
        ch = gc();
    }
    while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gc();
    x = x * w;
}
template <typename T>
void write(T x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar(x % 10 + 48);
}
map<uLL,int>vis;
int n;
uLL a[N];
int main() {
    read(n);
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= 6; j ++) read(a[j]);
        for (int j = 1; j <= 6; j ++) {
            uLL hash = 0;
            int t = j + 1; 
            if (t == 7) t = 1;
            while (t != j) {
                hash = hash * Base + a[t];
                t ++; 
                if (t == 7) t = 1;
            }
            if (vis[hash] && vis[hash] != i) {
                printf("Twin snowflakes found.\n");
                return 0;
            }
            vis[hash] = i; 
            t = j - 1;
            hash = 0; 
            if (t == 0) t = 6;
            while (t != j) {
                hash = hash * Base + a[t];
                t --; 
                if (t == 0) t = 6;
            }
            if (vis[hash] && vis[hash] != i) {
                puts("Twin snowflakes found.");
                return 0;
            }
            vis[hash] = i;
        }
    }
    puts("No two snowflakes are alike.");
    return 0;
}
```
----
很明显，我们用map来映射这样做肯定会超时，而且会有很多相同的状态会让我们重复计算：如果有一个雪花是`1 1 1 1 1 1`，那么我们就会算12次，但是很明显我们只需要做一次就足够了。  
那么我们考虑优化暴力，map我们可以用前向星来存储，也就是我们将每一个雪花的哈希值当做一个节点，每次和之前的已经算出节点判断是否有相同的雪花。  
说的简单一点，就是将每一个雪花的hash用前向星串起来，避免map的巨大常数，这样也可以避免一个相同的状态计算多次。
代码
```cpp
#include <cstdio>
#include <map>
#include <cstring>
#define N 100005
#pragma GCC optimize(2)
#define Base 401
#define Mod 99991
using namespace std;
inline char gc() {
	static char buf[1 << 16], *S, *T;
	if (S == T) {
		T = (S = buf) + fread(buf, 1, 1 << 16, stdin);
		if (T == S) return EOF;
	}
	return *S ++;
}
template <typename T>
inline void read(T &x) {
	T w = 1;
	x = 0;
	char ch = gc();
	while (ch < '0' || ch > '9') {
		if (ch == '-') w = -1;
		ch = gc();
	}
	while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gc();
	x = x * w;
}
template <typename T>
void write(T x) {
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) write(x / 10);
	putchar(x % 10 + 48);
}
#define N 100005
int H[N];
int cnt, n;
struct edge {
	int s[10];
	int nt;
}E[N];
int Hash(int *a) {
	int res = 0, mul = 0;
	for (int i = 0; i < 6; i ++) {
		res = (res + a[i]) % Mod;
		mul = (1ll * mul * a[i]) % Mod;
	}
	return (res + mul) % Mod;
}
bool check(int *a, int *b) {
	for (int i = 0; i < 6; i ++) 
		for (int j = 0; j < 6; j ++) {
			bool fg = true;
			for (int k = 0; k < 6; k ++) 
				if (a[(i + k) % 6] != b[(j + k) % 6]) fg = 0;
			if (fg) return true;
			fg = true;
			for (int k = 0; k < 6; k ++) 
				if (a[(i + k) % 6] != b[(j - k + 6) % 6]) fg = 0;
			if (fg) return true;
		}
	return false;
} 
bool insert(int *a) {
	int hash = Hash(a);
	for (int e = H[hash]; e; e = E[e].nt) {
		if (check(E[e].s, a)) return true;
	}
	memcpy(E[++ cnt].s, a, 6 * sizeof(int));
	E[cnt].nt = H[hash];
	H[hash] = cnt;
	return false;
}
int main() {
//	freopen("snowflakes.in","r",stdin);
//	freopen("snowflakes.out","w",stdout);
	read(n);
	while (n --) {
		int a[10];
		for (int i = 0; i < 6; i ++) read(a[i]);
		if (insert(a)) {
			printf("Twin snowflakes found.\n");
			return 0;
		}
	}
	printf("No two snowflakes are alike.\n");
	return 0;
}


```

---

## 作者：Nowed (赞：2)

# 题目
 
http://poj.org/problem?id=3349

https://www.luogu.org/problemnew/show/SP4354


----------
# 解题思路

安利一下[我的博客](https://blog.csdn.net/qq_39897867/article/details/81876304)

**本题我调了很久！！！**
这道题的$unsigned\ (long\ long)$很烦，不过它们有自然溢出的功能。
**因为顺时针和逆时针都可以，所以只需将原串在前后复制两遍，然后做两遍[最小表示法](https://blog.csdn.net/qq_39897867/article/details/81783771),求出最小同构串,$hash$一下即可。**

----------
# 代码

```cpp
#include<cstdio>
#include<algorithm>
using namespace std; 
const unsigned inf=160001; 
unsigned long long h[inf];
unsigned a[21],n; 
unsigned in(){
    unsigned ans=0; char c=getchar();
    while (c<48||c>57) c=getchar();
    while (c>47&&c<58) ans=ans*10+c-48,c=getchar();
    return ans;
}
int findd(unsigned long long k)//hash哈希表
{
    unsigned g=k%inf,i=0; 
    while (i<inf&&h[(g+i)%inf]&&h[(g+i)%inf]!=k) i++; 
    return (g+i)%inf; 
}
bool hash(unsigned ans1,unsigned ans2)
{
    bool b=0; unsigned i,summ,ans=ans1; unsigned long long sum=0;  
    for (i=0;i<6&&a[ans1+i]==a[ans2-i];i++);//求最小同构串
    if (a[ans1+i]>a[ans2-i]) {ans=ans2; b=1;}
    if (b) {//累求hash值
        for (unsigned j=ans;j>ans-6;j--) 
          sum=sum*13131+a[j]; 
    } else {
        for (unsigned j=ans;j<ans+6;j++) 
          sum=sum*13131+a[j]; 
    }
    if (h[(summ=findd(sum))]==sum) return 1; 
    h[summ]=sum; return 0; 
}
int main()
{
    n=in(); 
    while (n--)
    {
        for (unsigned i=7;i<=12;i++) 
          scanf("%d",&a[i]),a[i-6]=a[i+6]=a[i]; 
        int ii=7,jj=8,kk; 
        while (ii<=12&&jj<=12)//顺时针
        {
            kk=0; while (kk<=6&&a[ii+kk]==a[jj+kk])kk++; 
            if (kk==6) break; 
            if (a[ii+kk]>a[jj+kk]) {ii=ii+kk+1; if (ii==jj) ii++;} 
            else {jj=jj+kk+1; if (ii==jj) jj++;}
        }
        unsigned ans1=min(ii,jj); ii=12,jj=11;
        while (ii>=7&&jj>=7)//逆时针
        {
            kk=0; while (kk<=6&&a[ii-kk]==a[jj-kk])kk++; 
            if (kk==6) break; 
            if (a[ii-kk]>a[jj-kk]) {ii=ii-kk-1; if (ii==jj) ii--;} 
            else {jj=jj-kk-1; if (ii==jj) jj--;}
        }
        unsigned ans2=max(ii,jj); 
        if (hash(ans1,ans2)) {
           printf("Twin snowflakes found."); return 0; 
        } 
    }
    printf("No two snowflakes are alike."); 
}
```

---

## 作者：black_trees (赞：1)

hash.

---

题目给的比较清楚了。

因为根据定义，两个相同的雪花的长度之和，长度之积是相同的。

我们定义一个 hash 函数：

$ \operatorname{hash}(a_{i,1},a_{i,2},a_{i,3},a_{i,4},a_{i,5},a_{i,6}) = \ ( \sum^{6}_{j=1} +\prod_{j=1}^{6} a_{i,j}\ ) \bmod P $

然后我们建立一个哈希表，每次插入一个新的六元组的时候，直接扫描一下表头看看有没有相同的就行了。

期望复杂度是 $\operatorname{O}(n)$ 的。


---

Code：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int si=1e5+10;
int n;
int hash_list[si][6],head[si],tail[si];
const int mod=99991;//模数P
int tot;

int hash(int *a){
    int sum=0;
    int mul=1;
    for(register int i=0;i<6;++i){
        sum=(sum+a[i])%mod;
        mul=1ll*mul*a[i]%mod;
    }
    return (sum+mul)%mod;
}//hash

bool fin(int *a,int *b){
    for(register int i=0;i<6;++i){
        for(register int j=0;j<6;++j){
            bool f=1;
            for(register int k=0;k<6;++k){
                if(a[(i+k)%6]!=b[(j+k)%6]){
                    f=0;
                }
            }
            if(f){
                return 1;
            }
            f=1;
            for(register int k=0;k<6;++k){
                if(a[(i+k)%6]!=b[(j-k+6)%6]){
                    f=0;
                }
            }
            if(f){
                return 1;
            }
        }
    }
    return 0;
}//判断两片雪花是否相同

bool insert(int *a){
    int value=hash(a);
    for(register int i=head[value];i;i=tail[i]){
        if(fin(hash_list[i],a)){
            return 1;
        }
    }
    ++tot;
    memcpy(hash_list[tot],a,6*sizeof(int));
    tail[tot]=head[value];
    head[value]=tot;
    return 0;
}

int main(){
    scanf("%d",&n);
    for(register int i=1;i<=n;++i){
        int a[10];
        for(register int j=0;j<6;++j){
            scanf("%d",&a[j]);
        }
        if(insert(a)){
            printf("Twin snowflakes found.\n");
            return 0;
        }//如果找到了就直接输出。
    }
    printf("No two snowflakes are alike.\n");//无解
    return 0;
}

```


---

P.S：POj上不可以用万能头。


借鉴了一下lyd的蓝书。


---

## 作者：luckydrawbox (赞：0)

## 分析

显然，对于两片形状相同的雪花，它们六个角的长度之和、长度之积都相等（**注意**：这并不意味着六个角的长度之和、长度之积都相等的雪花就是形状相同）。

定义 $Hash$ 函数：
$$H(a_{i,1},a_{i,2},...,a_{i,6})=(\sum_{j=1}^6a_{i,j}+\prod_{j=1}^6a_{i,j})\bmod P$$

其中 $P$ 是我们自己选取的一个较大的质数，这样，两片形状相同的雪花的 $Hash$ 函数值也相等。

建立一个 $Hash$ 表，把 $N$ 片雪花依次插入。对于每片雪花 $a_{i,1},a_{i,2},…a_{i,6}$，我们直接扫描表头 $H(a_{i,1},a_{i,2},…a_{i,6})$ 对应的链表，检查是否存在与 $a_{i,1},a_{i,2},…a_{i,6}$ 形状相同的雪花即可。对于随机数据，期望的时间复杂度为 $O(N^2/P)$；取 $P$ 为最接近 $N$ 的质数，期望时间复杂度为 $O(N)$。

## 代码

~~我相信你看完我枯燥的解释就是为了这里~~

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 100006, P = 99991;
int n, a[6], b[6];
struct S {//雪花结构体，这样方便整体赋值
	int s[6];
};
vector<S> snow[N];

int H() {//把六个角上的数转换为对应的Hash值
	int s = 0, k = 1;
	for (int i = 0; i < 6; i++) 
   {
		(s += a[i]) %= P;
		k = (ll)k * a[i] % P;
	}
	return (s + k) % P;
}

bool pd() {//判断是否相同
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 6; j++)
      {
			bool v = 1;
			for (int k = 0; k < 6; k++)
				if (a[(i+k)%6] != b[(j+k%6)]) //顺时针
           {
					v = 0;
					break;
				}
			if (v) return 1;
			v = 1;
			for (int k = 0; k < 6; k++)
				if (a[(i+k)%6] != b[(j-k+6)%6])//逆时针
           {
					v = 0;
					break;
				}
			if (v) return 1;
		}
	return 0;
}
bool insert()//插入并返回是否相同
{
	int h = H();
	for (unsigned int i = 0; i < snow[h].size(); i++) 
   {
		memcpy(b, snow[h][i].s, sizeof(b));
		if (pd()) return 1;
	}
	S s;
	memcpy(s.s, a, sizeof(s.s));
	snow[h].push_back(s);
	return 0;
}
int main() {
	cin >> n;
	for (int i = 1; i <= n; i++)
   {
		for (int j = 0; j < 6; j++) scanf("%d", &a[j]);
		if (insert()) 
      {
			cout << "Twin snowflakes found." << endl;
			return 0;
		}
	}
	cout << "No two snowflakes are alike." << endl;
	return 0;
}
```

---

## 作者：Gorenstein (赞：0)

#### 题目大意

- 给出N片六角雪花，判断是否有两篇雪花相同。
- 两篇雪花相同，当且仅当他们各自从某一角开始顺时针或逆时针记录长度，能得到相同的六元组。
- 数据范围未给出，此题解按照 $\text{long long}$ 处理。

------------


首先考虑如何判断两片雪花 $a,b$ 是否相同。

按照题意模拟即可。首先枚举第一片雪花$a$的每一角，在其中枚举第二片雪花$b$的每一角，分别判断同一方向和不同方向得到的六元组是否相等即可。

```
//判断两片雪花是否相同
for(long long i=0;i<6;i++)
	for(long long j=0;j<6;j++){
		bool trfa=true;
		for(long long k=0;k<6;k++)
			if(a[(i+k)%6]!=b[(j+k)%6])trfa=false;
		if(trfa)return true;
		trfa=true;
		for(long long k=0;k<6;k++)
			if(a[(i+k)%6]!=b[(j-k+6)%6])trfa=false;
		if(trfa)return true;
	}
return false;
```

------------


然后考虑如何寻找两片相同的雪花。

考虑到只要知道是否相同即可，因此我们可以边输入边进行判断。可以用$Hash$算法来优化。

构造一个$hash$函数

$$
Hash(a_1,a_2,...,a_6)=\sum\limits_{k=1}^6a_k\times \prod\limits_{k=1}^6a_k\mod P
$$

这个$Hash$函数可以保证拥有相同形状的雪花会有相同的$Hash$值。

```
long long sum=0,mul=1;
for(int i=0;i<6;i++)
	sum=(sum+a[i])%mod,mul=mul%mod*a[i]%mod;
return sum%mod*mul%mod;
```

对于每一个$Hash$处理后的值，使用开散列法解决冲突。数组模拟链表，建立一个邻接表来存储$Hash$后相同的元素。

这样处理之后，对于一片雪花，直接扫描对应的邻接表里的雪花即可。

```
//扫描
for(int i=head[x];i;i=next[i])
    
//插入
nxt[++cnt]=head[x],head[x]=cnt;
```

------------


#### 总结一下

- 边输入边进行判断。
- 每次遇到一片雪花，$Hash$ 后扫描相应链表，若相同则输出找到并结束；否则插入这片雪花。
- 输入结束后，若程序并未结束，即无两片雪花相同，输出没找到。

对于随机数据，期望复杂度为 $O\left(\frac{N^2}{P}\right)$。取 $P$ 为最接近 $N$ 的质数，期望复杂度 $O(N)$。

```cpp
//开散列法解决冲突，将冲突放到一个链表中
const long long SIZE=100005,mod=99991;
long long n,cnt,snow[SIZE][6],head[SIZE],nxt[SIZE];
//Hash函数
long long Hash(long long *a)
{
	long long sum=0,mul=1;
	for(int i=0;i<6;i++)
		sum=(sum+a[i])%mod,mul=mul%mod*a[i]%mod;
	return sum%mod*mul%mod;
}

//判断两片雪花是否相同
bool check(long long *a,long long *b)
{
	//枚举第一片雪花的每一角
	for(long long i=0;i<6;i++)
		//枚举第二篇雪花的每一角
		for(long long j=0;j<6;j++)
		{
			bool trfa=true;
			//顺时针对比两片雪花
			for(long long k=0;k<6;k++)
				if(a[(i+k)%6]!=b[(j+k)%6])trfa=false;
			if(trfa)return true;
			trfa=true;
			//逆时针对比两片雪花
			for(long long k=0;k<6;k++)
				if(a[(i+k)%6]!=b[(j-k+6)%6])trfa=false;
			if(trfa)return true;
		}
	return false;
}

//插入一片雪花
bool insert(long long *a)
{
	long long x=Hash(a);
	//在hash处理后对应的链表中寻找相同雪花
	for(long long i=head[x];i;i=nxt[i])
		if(check(snow[i],a))return true;
	//没寻找到，插入雪花
	++cnt;
	memcpy(snow[cnt],a,6*sizeof(long long));
	nxt[cnt]=head[x],head[x]=cnt;
	return false;
}

int main()
{
	cin>>n;
	for(long long i=1;i<=n;i++)
	{
		long long a[10];
		for(long long j=0;j<6;j++)cin>>a[j];
		if(insert(a)){cout<<"Twin snowflakes found.";return 0;}
	}
	cout<<"No two snowflakes are alike.";
	return 0;
}
```

---

## 作者：zhzzhzzzz (赞：0)

萌新刚学 $Hash$ ，如有纰漏请指正orz

题意说要判断雪花是否有相同的，自然要用 $Hash$ 做。

定义 $Hash$ 函数 $H(a_{i,1},a_{i,2},…,a_{i,6})=(\space\sum^6_{j=1}a_{i,j}+\prod^6_{j=1}a_{i,j})\space mod\space mod$，$mod$是我们选的一个质数，很明显，如果两片雪花形状相同，那么他们六个角的**长度之和，长度之积都相等**，因此，它们的 $Hash$ 值也相等。

建一个 $Hash$ 表，把 $N$ 片雪花依次插入。对于每一片雪花 $a_{i,1},a_{i,2},…,a_{i,6}$ ，我们可以直接扫描表头 $H(a_{i,1},a_{i,2},…,a_{i,6})$ 对应的链表，找一找是否有与 $a_{i,1},a_{i,2},…,a_{i,6}$ 形状相同，**即 $Hash$ 值相同**的雪花即可。

时间复杂度为 $O(N^2/mod)$ ~~别问我怎么知道的，lyd书里教的~~， $mod$ 可以取最接近 $N$ 的质数 $mod=99991$，期望的时间复杂度为 $O(N)$的。

你谷上跑了 $720ms/5.20MB$ ，讲真的很强。

在蓝书上看完这道题就写了一手代码，却打死也调不出来哪里错了，结果发现是最后输出少了个. ，大大的.

~~细节决定成败~~

AC代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch <= '9' && ch >= '0')
        x = x * 10 + ch - '0', ch = getchar();
    return x * f;
}
const int N = 100010;
int cnt;
int n, mod = 99991, snow[N][7], head[N], nxt[N];
int Hash(int *a)//Hash函数
{
    int sum = 0, mu = 1;
    for (int i = 0; i < 6; i++)
    {
        sum = (sum + a[i]) % mod;
        mu = (long long)mu * a[i] % mod;
    }
    return (sum + mu) % mod;
}
bool same(int *a, int *b)//判断是否存在相同的
{
    for (int i = 0; i < 6; i++)//循环两片雪花的每一个角
    {
        for (int j = 0; j < 6; j++)
        {
            bool sa = 1;
            for (int k = 0; k < 6; k++)
                if (a[(i + k) % 6] != b[(j + k) % 6])//正过来倒腾
                    sa = 0;
            if (sa)
                return 1;
            sa = 1;
            for (int k = 0; k < 6; k++)
                if (a[(i + k) % 6] != b[(j - k + 6) % 6])//反过来倒腾
                    sa = 0;
            if (sa)
                return 1;
        }
    }
    return 0;
}
bool inser(int *a)
{
    int x = Hash(a);//插入新雪花时，先求Hash判断是否已经存在相同的雪花
    for (int i = head[x]; i; i = nxt[i])//扫链表
        if (same(snow[i], a))
            return 1;
    cnt++;//没有发现，现在雪花总数量++
    memcpy(snow[cnt], a, 6 * sizeof(int));//从a拷贝6个int字节到第cnt个雪花上
    nxt[cnt] = head[x];//链表扩展
    head[x] = cnt;
    return 0;
}
int main()
{
    n = read();
    for (int i = 1; i <= n;i++)
    {
        int a[7];
        for (int j = 0; j < 6;j++)
            a[j] = read();
        if(inser(a))
        {
            puts("Twin snowflakes found.");
            return 0;
        }
    }
    puts("No two snowflakes are alike.");
    return 0;
}
```

OK，相当于把lyd书上的做法搬到luogu上了，~~lyd nb！~~

---

## 作者：离散小波变换° (赞：0)

## 题目大意

给出$n$个六瓣雪花的顺时针**或**逆时针的长度，询问是否存在两个相同的雪花。

## 题解

容我先吐槽一下，为什么题目连数据范围和样例都没有，以及这个时限是什么东西……

这里提供一个非常简单粗暴的方法。我们只需要用字符串哈希，分别用暴力算法算出顺时针和逆时针的连续六个雪花瓣的哈希值，然后直接插入哈希表即可。

没错，这题真的就这么简单。不过，有好多细节：

- $1.$单哈希很有可能由于数据规模巨大而被卡掉。建议用双哈希。

- $2.$断环成链处理字符串哈希值，可以有效优化时间。

- $3.$用$\rm map$大概会超时，这里可能需要手写哈希。

这里提供一个很简单的手写链表哈希方法。很显然，我们可以将哈希值模一个比较大的质数，来减少空间的使用；但是，这样会大大增加哈希碰撞的概率。因此，我们还需要存入哈希值的原始值，用来避免因为取模造成的碰撞。于是考虑邻接表：

- 我们将第$i$个表头作为取模后哈希值为$i$的值的表。

- 当插入哈希值$h$时，只需要在表$h \mod p$的后面插入$h$。

- 查询是否存在哈希值$h$时，只需要在表$h \mod p$里暴力查询即可。

由于本题空间限制挺大，所以哈希表的大小可以开的比较大。因此，暴力查询的时间复杂度期望值很小，总查询复杂度几乎达到线性。

不过由于我们需要枚举雪花的顺序，因此时间复杂度还有一个比较大的常数。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define up(l,r,i) for(int i=l;i<=r;i++)
#define dn(l,r,i) for(int i=l;i>=r;i--)
using namespace std;

typedef long long LL;
const int INF =2147483647;
int qread(){
    int w=1,c,ret;
    while((c=getchar())> '9'||c< '0')
    w=(c=='-'?-1:1); ret=c-'0';
    while((c=getchar())>='0'&&c<='9')
    ret=ret*10+c-'0';
    return ret*w;
}
const int SIZ=999997,MAXN=999997,MAXM=12+3;
typedef unsigned long long ULL;
int headA[SIZ],nxtA[MAXN],totA; ULL verA[MAXN];
ULL seedA[MAXM],seedB[MAXM],A[MAXM],P[MAXM],Q[MAXM];
void addA(int u,ULL v){
    verA[++totA]=v,nxtA[totA]=headA[u],headA[u]=totA;
}
int headB[SIZ],nxtB[MAXN],totB; ULL verB[MAXN];
void addB(int u,ULL v){
    verB[++totB]=v,nxtB[totB]=headB[u],headB[u]=totB;
}
bool fndA(ULL w){
    int p=w%SIZ; for(int i=headA[p];i;i=nxtA[i])
    if(verA[i]==w) return true; return false;
}
bool fndB(ULL w){
    int p=w%SIZ; for(int i=headB[p];i;i=nxtB[i])
    if(verB[i]==w) return true; return false;
}
ULL get(int l,int r,ULL *w,ULL *seed){
    return w[r]-w[l-1]*seed[r-l];
}
int n;
int main(){
    seedA[0]=13331,seedB[0]=19260817;
    up(1,12,i) seedA[i]=seedA[i-1]*seedA[0];
    up(1,12,i) seedB[i]=seedB[i-1]*seedB[0];
    n=qread(); up(1,n,i){
        up(1,6,j) A[j]=A[j+6]=qread();
        up(1,12,j){
            P[j]=P[j-1]*seedA[0]+A[j];
            Q[j]=Q[j-1]*seedB[0]+A[j];
        }
        up(1,6,j){
            ULL w1=get(j,j+5,P,seedA),w2=get(j,j+5,Q,seedB);
            if(fndA(w1)&&fndB(w2)) goto end;
            addA(w1%SIZ,w1),addB(w2%SIZ,w2);
        }
        reverse(A+1,A+1+12);
        up(1,12,j){
            P[j]=P[j-1]*seedA[0]+A[j];
            Q[j]=Q[j-1]*seedB[0]+A[j];
        }
        up(1,6,j){
            ULL w1=get(j,j+5,P,seedA),w2=get(j,j+5,Q,seedB);
            if(fndA(w1)&&fndB(w2)) goto end;
            addA(w1%SIZ,w1),addB(w2%SIZ,w2);
        }
    }
    puts("No two snowflakes are alike.");return 0;
    end: puts("Twin snowflakes found."); return 0;
}
/*参考样例，输出"Twin snowflakes found."。
2
1 2 3 4 5 6
4 3 2 1 6 5
*/
```

---

## 作者：misinclair (赞：0)

最小表示法

我们把一个数字串的本身和将它翻转后的字典序最小的两个数字串比较，取较小的，这样就满足了题意中 
从任何一个角开始顺时针或逆时针向后记录长度所得到的六元组都代表相同的雪花

因为相同的雪花的字典序最小的字符串肯定是相同的。

那么问题就变成了问给一堆字符串，有没有相同的。

好像怎么做都行....

单hash + 散列表 复杂度$O(\frac {N^2} {p})$ $P$ 是 hash表的大小

或者双hash比较稳套一个set 复杂度$O(nlogn)$

---

