# Sort the Array

## 题目描述

Being a programmer, you like arrays a lot. For your birthday, your friends have given you an array $ a $ consisting of $ n $ distinct integers.

Unfortunately, the size of $ a $ is too small. You want a bigger array! Your friends agree to give you a bigger array, but only if you are able to answer the following question correctly: is it possible to sort the array $ a $ (in increasing order) by reversing exactly one segment of $ a $ ? See definitions of segment and reversing in the notes.

## 说明/提示

Sample 1. You can reverse the entire array to get $ [1,2,3] $ , which is sorted.

Sample 3. No segment can be reversed such that the array will be sorted.

Definitions

A segment $ [l,r] $ of array $ a $ is the sequence $ a[l],a[l+1],...,a[r] $ .

If you have an array $ a $ of size $ n $ and you reverse its segment $ [l,r] $ , the array will become:

 $ a[1],a[2],...,a[l-2],a[l-1],a[r],a[r-1],...,a[l+1],a[l],a[r+1],a[r+2],...,a[n-1],a[n]. $

## 样例 #1

### 输入

```
3
3 2 1
```

### 输出

```
yes
1 3
```

## 样例 #2

### 输入

```
4
2 1 3 4
```

### 输出

```
yes
1 2
```

## 样例 #3

### 输入

```
4
3 1 2 4
```

### 输出

```
no
```

## 样例 #4

### 输入

```
2
1 2
```

### 输出

```
yes
1 1
```

# 题解

## 作者：William20 (赞：8)

# [CF451B ](https://www.luogu.com.cn/problem/CF451B)  
### 题目大意：
判断一个数组是否可以通过翻转这个数组中的一段，使这个数组变成一个上升数组？

------------
### 本蒟蒻的思路：  
1）将一个数组a排好序存在另一个数组b里；  
2）将a与b一位一位地比较，找到乱序的子段的两个端点l&r，并将这个子段反转；  
3）判断：如果这个反转后的数组为上升数组输出“yes”以及l&r。否则输出“no”。

------------
### AC代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, a[100010], b[100010];
int main() {
	cin >> n;//输入
	for (int i = 0; i < n; i++) {
		cin >> a[i];//输入a数组
		b[i] = a[i];//同时储存至b数组
	}
	sort(b, b + n);//将b数组排序成一个上升数组
	int l = 0, r = n - 1;
	while (a[l] == b[l] && l <= n - 1) {
		l++;//记录该非升序字段的左端点
	}
	while (a[r] == b[r] && r >= 0) {
		r--;//同理，记录右端点
	}
	if (l >= r) {
		cout << "yes\n1 1";//如果l>=r,则a数组已是上升数组，输出“yes\n1 1”即可
		return 0;
	}
	for (int i = l, j = r; i <= r; i++, j--) {
		b[i] = a[j];//将该非升序子段反转
	}
	for (int i = 0; i < n - 1; i++) {
		if (b[i] > b[i + 1]) {
			cout << "no";//判断反转后的数组是否为上升数组，非则输出“no”
			return 0;
		}
	}
	cout << "yes\n" << l + 1 << " " << r + 1;//是则输出“yes”
	return 0;//完美结束
}
```
如有不足，欢迎指出。

---

## 作者：伟大的王夫子 (赞：1)

首先，先讲一下本题基本的思路。

如果翻转的区间是  $[L, R]$，
那么这个区间中的数的值一定是单调递减，并且 $[1,L-1]$ 和 $[R+1,n]$ 区间中的数一定是单调递增。

那么思路就有了。

我们先找到最长的非严格单调递增的序列，记这个序列末尾为 $L$。

然后再从末尾开始找，满足这个序列也是非严格单调增。

记这个数组的开头下标为 $R$。

（当然，要先特判已经排好序的数组）

并且 $L, R$ 应满足 $a_L>a_{L+1}$ 和 $a_{R-1} >a_R$。

这个时候我们应该有4种选择，区间 $[L+1,R-1],[L, R],[L +1,R],[L,R-1]$ 四种选择。

我们一个个枚举，判断是否可行即可。

为了方便，我写了一个 work 函数，参数是 $l,r$，返回的是 $[l,r]$ 
下标区间中的数是否排好序。

翻转的时候，可以使用函数 reverse。



```cpp
#include <bits/stdc++.h>
using namespace std;
int n, a[100010];
bool work(int l, int r) {
	bool flag = 1;
	for (register int i = l; i <= r - 1; ++i) {
		flag &= a[i] <= a[i + 1]; 
	}
	return flag;
}
#define REV(L, R) reverse(a + L, a + R + 1)
const int dx[] = {0, 0, 1, 1}, dy[] = {0, -1, 0, -1};
int main() {
	cin >> n;
	for (register int i = 1; i <= n; ++i) scanf("%d", a + i);
	bool flag = 0;
	if (work(1, n)) {
		puts("yes\n1 1");
		return 0;
	}
	int L = 0, R = 0;
	for (register int i = 1; i <= n - 1; ++i) {
		if (a[i] > a[i + 1]) {
			L = i;
			break;
		}
	} 
	a[n + 1] = 1e9;
	for (register int i = n; i; --i) {
		if (a[i - 1] > a[i]) {
			R = i;
			break;
		}
	}
	for (register int i = 0; i < 4; ++i) {
		int x = L + dx[i], y = R + dy[i];
		REV(x, y);
		if (x <= 0 || x > n || y <= 0 || y > n) continue;
		if (work(1, n)) {
			cout << "yes\n" << x << ' ' << y;
			return 0;
		}
		REV(x, y);
	}
	puts("no");
}


```


---

## 作者：Ein_Niemand (赞：1)

**题意大家应该都懂，我这里不再赘述。**

**这里向大家介绍一种非常好用的STL函数：reverse(~~STL大法好~~)**

**那么这个van意是干啥的呢？↓↓↓↓↓**

### reverse(a+l,a+r+1)就可以将a数组的第l号元素至第r号元素翻转

### 有了这个，这道题就可以进行各种♂♂操作
```
//----------------------------//
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<climits>
#include<bitset>
using namespace std;
#define R register int
#define LL long long
#define Rl register LL
#define db double
#define I inline int
#define V inline void
#define DB inline double
const int maxn=100005;
const int mod=1e8;
const db eps=1e-6;
const db pi=acos(-1.0);
const int oo=2147483647;
#define F1(i,a,b) for(R i=a;i<=b;++i)
#define F2(i,a,b) for(R i=a;i>=b;--i)
#define F3(i,a,b,c) for(R i=a;i<=b;i+=c)
#define F4(i,a,b,c) for(R i=a;i>=b;i-=c)
#define min(x,y) x<y?x:y
#define max(x,y) x>y?x:y

//------  ↑↑↑↑宏定义区↑↑↑↑  ------//

V read(R &x)
{
    R f=1;x=0;register char c=getchar();
    for(;c>'9'||c<'0';c=getchar()) if(c=='-') f=-1;
    for(;c>='0'&&c<='9';c=getchar()) x=(x<<3)+(x<<1)+(c^48);
    x*=f;
}
V print(R x)
{
    if(x<0) x=-x,putchar('-');
    if(x>9) print(x/10);
    putchar(x%10+'0');
}

//------  ↑↑↑↑快读快输函数↑↑↑↑  ------//

int n,a[maxn],tot;
//tot:记录出现了几个降序子序列
I check()
{
	F1(i,1,n)
		if(a[i]<a[i-1]) return false;
	return true;
}

//------  ↑↑↑↑check函数（判断当前数列是否严格单调递增）↑↑↑↑  ------//

int main()
{
//	freopen("number.in","r",stdin);
//	freopen("number.out","w",stdout);
	read(n);a[n+1]=oo,a[0]=-1;
//      将0号元素置为最小值，n+1号元素置为最大值
    
	F1(i,1,n) read(a[i]);
	if(check()) {printf("yes\n1 1");return 0;}
//	如果当前数列已经单调递增，就直接输出
	F1(i,1,n)
	{
		R pos=i,flag;
		while(a[pos+1]>a[pos]) ++pos;
//		因为我们要找第一个降序列，所以要将这之前的升序列一键排除（作者是蒟蒻，这里居然WA了几次）
		i=pos;
		while(a[pos+1]<a[pos]&&pos<=n) ++pos,flag=1;
//		搜出第一个降序列，并用flag标记
		reverse(a+i,a+pos+1);
//		翻转搜到的第一个降序列
		if(flag) ++tot;
//		降序列数++
		if(tot>1) {puts("no");return 0;}
//		如果有超过1个的降序列，就直接输出no
		if(check()) {puts("yes"),print(i),putchar(' '),print(pos);return 0;}
//		满足条件就输出左右端点
		else {puts("no");return 0;}
//		否则，翻转后也不满足条件，就输出no
		if(flag) i=pos;
//		如果有降序列，就将下一次循环起点置为pos
	}
	return 0;
/*
6
1 2 4 3 5 6
*/
}
```
# 希望管理员大大给过qwq

---

## 作者：SimonSu (赞：1)

一遍线型跑过

遇到下降就判断 如果可以调换就加计数器 最后看计数器的数量

#### 注意！！
要注意重复的数据 所以加上等号 

注意开始l r 赋初值均为1

也就没有什么其他的需要注意了

普通的线型模拟 注意细节别写的脑袋昏

```
#include<bits/stdc++.h>
#define debug cout<<bug<<endl
using namespace std;
const int inf=0x7f7f7f7f;
inline void read(int &x){
	x=0;int f=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
	x*=f;
}
int n,x,y,l=1,r=1,f;
int a[100100];
int main()
{
	
	read(n);
	for(int i=1;i<=n;i++) read(a[i]);
	a[n+1]=inf;
	for(int i=1;i<=n;i++)
	{
		if(a[i]<a[i-1])
		{
			f++;
			l=i-1;
			x=a[i-2];
			for(;i<=n;i++)
			{
				if(a[i]<=a[i+1])
				{
					if(x>=a[i]) f=inf;
					if(a[l]>=a[i+1]) f=inf;
					r=i;
					break;
				}
			}
		}
	}
	if(f>1) printf("no\n");
	else printf("yes\n%d %d\n",l,r);
	return 0;
}
```


---

## 作者：InfSauf (赞：0)

根据题意，输入一个数 $n$，接着输入 $n$ 个数，翻转**一次**该数组的其中一段 $[l,r]$，使该数组为上升数组。

我们可以先找到下降数组的左右端点，然后翻转这一段，判断翻转后的数组是否是上升数组，如果不是就输出 no。

思路大概就是这样，我们可以用一个函数来翻转数组的某一段：
```cpp
reverse(a+l, a+r+1);
```
注：如果输入的数组原本就是上升数组，则输出的左右端点都为 $1$。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5 + 10;
int n, l = 0, r = 0;
int a[N], b[N];
bool ok;
signed main(){
	cin >> n;
	for(int i = 1; i <= n; i++){
		cin >> a[i];
		b[i] = a[i];
	}
	a[n + 1] = 2e9;
	for(int i = 2; i <= n + 1; i++){
		if(!l && a[i] < a[i - 1])l = i - 1;
		if(l){
			if(a[i] > a[i - 1]){
				r = i - 1;
				break;
			}
		}
	}
	reverse(a + l, a + r + 1);
	sort(b + 1, b + n + 1);
	for(int i = 1; i <= n; i++){
		if(a[i] != b[i]){
			cout << "no";
			return 0;
		}
	}
	if(!l && !r){
		l++, r++;
	}
	cout << "yes" << endl << l << " " << r;
}
```


---

## 作者：__Octhyccc__ (赞：0)

题意：给一个有 $n$ 个数的序列 $a$，请问能否翻转这个序列中的一个连续部分，使序列 $a$ 变成上升的有序序列。

对于已经有序的序列，直接输出 `yes`，并且换行输出 `1 1` 就可以了，因为翻转的地址一样，不会对序列本身造成影响。

然后剩下的只有 $2$ 种情况：

- 降序序列。
- 无序序列。

对于这道题来说，可以输出 `yes` 的序列只有下图 $3$ 种：![](https://cdn.luogu.com.cn/upload/image_hosting/1hjfqnhq.png)

然后把 $l,r$ 内的元素翻转，`reverse` 是反转初始地址和结束地址 $-1$ 范围内的数。翻转后检查一下是否是升序就可以了，程序如下：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,l,r;
int a[100000];
bool work(){//检查是否有序。
	for(int i=0;i<n-1;i++){
		if(a[i]>a[i+1])return 0;
	}
	return 1;
}
int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%d",&a[i]);
	}
	if(work()){
		printf("yes\n1 1");
		return 0;
	}
	for(int i=1;i<n;i++){
		if(a[i]<a[i-1]){
			l=i;break;
		}
	}
	for(int i=n-1;i>=0;i--){
		if(a[i-1]>a[i]){
			r=i+1;break;
		}
	}
	reverse(a+l-1,a+r);
   //因为 l 赋值时 i 从 1 开始，多了 1，要减去 1，r 本身多 1 可以不减。
	work()?printf("yes\n%d %d",l,r):printf("no");
	return 0;
}
```

---

## 作者：_Revenge_ (赞：0)

### 题目简化和分析：  

这题就是判断将一段翻转后是否能变为升序的数组。   

我的方法是保存原数组每一个数出现的位置（相同任意一个），让后另外用一个数组存储排好序后的原数组，逐一进行比较。

- 若同，则跳到下一个元素比较继续。
- 若不同，枚举当前位置到排序数组当前元素在原数组中的位置，时候一直为降序。  
- 若多次出现不同，则跳出循环，立即输出。  
- 特别的，若一直相同任意输出相同的左端点和右端点，但保证是合法范围内的。   

### Solution:
```cpp
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef double db;

const int N=1e5+50;
const int M=1e5+50;
const int Mod=1e9+7;

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}

int n;
int a[N],b[N];

map<int,int>pos;

int main()
{
	n=read();
	for(int i=1;i<=n;++i) a[i]=read(),b[i]=a[i],pos[a[i]]=i;
	sort(b+1,b+n+1);
	int l=0,r=0;
	bool flag=1;
	for(int i=1;i<=n;){
		if(a[i]==b[i]){
			i++;
			continue;
		}
		if(l!=0){
			flag=0;
			break;
		}else{
			l=i,r=pos[b[i]];
			i=pos[b[i]]+1;
			for(int j=l;j<r;++j){
				if(a[j]<a[j+1]){
					flag=0;
					break;
				}
			}
			if(!flag) break;
		}
	}
	if(flag){
		printf("yes\n");
		if(l==0) l=r=1;
		printf("%d %d\n",l,r);
	}else{
		printf("no\n");
	}
	return 0;
}

```

---

## 作者：断清秋 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF451B)

首先将原数组排序，然后从前向后找到第一个需要翻转的位置记为 $l$，从后向前找到最后一个需要翻转的位置记为 $r$。将原数组的 $l$ 至 $r$ 位置进行翻转，然后比较这样反转后得到的新数组是否与直接排序后的结果相同即可。

时间复杂度 $O(nlogn)$。

代码：
```cpp
#include<bits/stdc++.h>
#include<iostream>
#define ll long long
#define back return
#define ri register int 
using namespace std;
int read()
{
	int x=0,f=1;
    char ch=getchar();
	while(!isdigit(ch))
    {
        if (ch=='-') 
            f=-1;
        ch=getchar();
    }
	while(isdigit(ch))
    {
        x=x*10+ch-48;
        ch=getchar();
    }
	back x*f;
}
bool flag;
ll a[100005],b[100005],c[100005];
ll t,n,m,k;
int l=1,r=1;
int main()
{	
	cin>>n;
	for(ri i=1;i<=n;i++)
	{
		a[i]=read();
		b[i]=a[i];
		c[i]=a[i];
	}
	sort(b+1,b+n+1);
	for(ri i=1;i<=n;i++)
		if(a[i]!=b[i])
		{
			l=i;
			break;
		}				
	for(ri i=n;i>=1;i--)
		if(a[i]!=b[i])
		{
			r=i;
			break;
		}
	for(ri i=l;i<=r;i++)
		a[i]=c[r-i+l];
	for(ri i=1;i<=n;i++)
		if(a[i]!=b[i])
		{
			cout<<"no"<<endl;
			back 0;
		}
	cout<<"yes"<<endl;
	cout<<l<<" "<<r<<endl;
    back 0;
}
```

---

## 作者：sinsop90 (赞：0)

我们选择一个区间 $[l, r]$ 进行翻转,为什么我们一定要选择这个 $[l,r]$ 呢?

肯定是因为在这个区间里每一个 $i$ $(l + 1 \le i \le r - 1)$ 都满足 $a_{i+1} < a_i < a_{i-1}$ 。

如果我们翻转这个序列之后整个 $a$ 序列满足要求,肯定是因为 :

翻转后对于每一个 $i$ $(2 \le i \le n - 1)$, 都满足 $a_{i-1} < a_i < a_{i+1}$。

于是我们开始研究如何确定翻转后序列是一个上升序列。

肯定是因为除了我们选择翻转的区间 $[l,r]$ 里的元素,其他元素在最原始的时候就已经是满足要求了。

这时候我们翻转这个区间, 若翻转完后, $a_r > a_{l-1}, a_l < a_{r+1}$ 我们才能保证翻转完后满足要求。

那么如何选出翻转的区间呢?

我们知道,翻转完后这个区间必须要成上升的,所以我们找到一个下降的区间即可。

显然,输出 $
\text{no}$ 的情况就是这个序列 $A$ 里存在不止一个下降的区间。

所以我们得到如下代码:

```
#include <bits/stdc++.h>
using namespace std;
int n, mps[100005], ansx, ansy, op = 0, p;
inline int read() {
    int w = 1, q = 0;
    char ch = ' ';
    while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
    if (ch == '-') w = -1, ch = getchar();
    while (ch >= '0' && ch <= '9') q = q * 10 + ch - '0', ch = getchar();
    return w * q;
}
inline void write(int x) {
    if (x < 0) {
        x = ~(x - 1);
        putchar('-');
    }
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
int main() {
	mps[0] = -2147483648;
	bool flag = false;
	n = read();
	mps[n + 1] = 2147483647;
	for(int i(1);i <= n;++i) mps[i] = read();
	for(int i(1);i <= n;++i) {
		if(mps[i] > mps[i + 1]) {
			if(op == 1) {//如果下降区间不止一个,就是不行啦
				printf("no\n");
				return 0;
			}
			if(!flag) {
				p = i;
				flag = true;//flag用来判断循环i的时候在不在下降区间中
				continue;
			}
		}
		if(mps[i] < mps[i + 1]) {
			if(flag) {
				if(mps[p] < mps[i + 1] && mps[i] > mps[p - 1]) {
					ansx = p, ansy = i;//记录答案
					op = 1;//记录已经找到一个下降区间了
					flag = false;
				}
				else {
					printf("no\n");
					return 0;
				}
			}
		}
	}
	if(ansx != 0) {
		printf("yes\n");
		write(ansx);
		putchar(' ');
		write(ansy);
		puts("");
 	}
 	else {
 		printf("yes\n");
 		printf("1 1\n");
 	}
}
```


---

## 作者：TLMPEX (赞：0)

```
这是一道模拟题。

如果输入的序列就是升序的话，哪么输出“yes\n1 1”了。

否则找到乱序的第一个位置和最后一个位置，把这两个位置之间的所有数（包括这两个数）全部翻转，如果可以，就输出“yes\n”和乱序的第一个位置和最后一个位置。否则输出“no”啦！
```
代码：
```c
#include<bits/stdc++.h>
using namespace std;
int a[100001],b[100001];
int main(){
	int n,i,j,l,r,f=1;
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>a[i];
		b[i]=a[i];
	}
	sort(b+1,b+n+1);
	for(i=1;i<=n;i++)
		if(a[i]!=b[i]){
			f=0;
			break;
		}
	if(f){
		cout<<"yes\n1 1";
		return 0;
	}
	for(i=1;i<=n;i++)
		if(a[i]!=b[i]){
			l=i;
			break;
		}
	for(i=n;i>=1;i--)
		if(a[i]!=b[i]){
			r=i;
			break;
		}
	for(i=l,j=r;i<=r,j>=l;i++,j--)
		if(i<=j)swap(a[i],a[j]);
	for(i=1;i<=n;i++)
		if(a[i]!=b[i]){
			cout<<"no";
			return 0;
		}
	cout<<"yes\n"<<l<<" "<<r;
}
```


---

## 作者：小豆子范德萨 (赞：0)

- 首先定义一个int数组v1存储原始输入，另一个v2暂存用
- 对v2 sort搞一下，从v1,v2前端开始找第一个不相同的元素，假设下标为pos1（蕴含着pos1前面的元素位置一定都是上升的），再从v1,v2后端找第一个不相同的元素(蕴含着pos2后面的元素位置都是上升的)。
- 那么我们要执行一次操作，一定是在pos1和pos2之间逆置。逆置完毕后再让其与v2的元素比较，若不同则直接输出no。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	cin>>n;
	vector<int>v1(n),v2(n);
	for(int i=0; i<n; ++i) {
		cin>>v1[i];
		v2[i]=v1[i];
	}

	sort(v2.begin(),v2.end());
	int pos1=0,pos2=0 ;
	for(int i=0; i<n; ++i) {
		if(v2[i]!=v1[i]) {
			pos1=i;
			break;
		}
	}
	for(int i=n-1; i>=0; --i) {
		if(v2[i]!=v1[i]) {
			pos2=i;
			break;
		}
	}
	int l=pos1,r=pos2;
	while(l<r) {
		swap(v1[l],v1[r]);
		++l;
		--r;
	}
	for(int i=0; i<n; ++i) {
		if(v1[i]!=v2[i]) {
			cout<<"no";
			return 0;
		}
	}
	cout<<"yes\n";
	cout<<pos1+1<<" "<<pos2+1;
	return 0;
}
```


---

## 作者：Erina (赞：0)

仔细思考一下，**是不是只有一个从大到小排列的区间才可能通过反转来排序？**

所以说要先找到目标降序区间，然后检查降序区间的个数

如果区间个数小于大于1，那么不能达成

否则，就可以达成吗？

答案是不一定，因为观察

> 4

> 3 1 2 4

可以发现，只有3 1这个降序序列，但是"排好"后 我们看到的是：

> 1 3 2 4

所以要排好之后再次进行判断，才能确认结果。

代码如下：(记住，不要抄代码，不然有可能变成![cheater](https://cdn.luogu.com.cn/upload/pic/18888.png)!)

```cpp
#include<iostream>
using namespace std;
int bigger[100000];
int n;
int num[100000];
int tail;
int main(){
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>num[i];
    }
    for(int i=1;i<n;i++){
        if(num[i]<num[i-1]){
            bigger[tail++]=i;
        }
    }
    for(int i=1;i<tail;i++){
        if(bigger[i]!=bigger[i-1]+1){
            cout<<"no";//超过一个区间
            return 0;
        }
    }
    if(tail==0){
        cout<<"yes\n1 1";//已经排好序的直接输出 1 1
        return 0;
    }
    int a=bigger[0]-1;
    int b=bigger[tail-1];
    for(int i=a;i<=(a+b)/2;i++){//交换区间顺序，这里容易写错(我调了三天)，多加注意
        swap(num[i],num[a+b-i]);
    }
    for(int i=1;i<n;i++){
        if(num[i]<num[i-1]){//判断反转后可不可以形成序列
            cout<<"no";
            return 0;
        }
    }
    cout<<"yes"<<endl;//输出结果，注意编号顺序，答案从1开始！！！
    cout<<bigger[0]<<' '<<bigger[tail-1]+1;
}
```

---

