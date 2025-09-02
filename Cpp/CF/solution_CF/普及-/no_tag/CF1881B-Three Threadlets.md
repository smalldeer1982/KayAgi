# Three Threadlets

## 题目描述

Once upon a time, bartender Decim found three threadlets and a pair of scissors.

In one operation, Decim chooses any threadlet and cuts it into two threadlets, whose lengths are positive integers and their sum is equal to the length of the threadlet being cut.

For example, he can cut a threadlet of length $ 5 $ into threadlets of lengths $ 2 $ and $ 3 $ , but he cannot cut it into threadlets of lengths $ 2.5 $ and $ 2.5 $ , or lengths $ 0 $ and $ 5 $ , or lengths $ 3 $ and $ 4 $ .

Decim can perform at most three operations. He is allowed to cut the threadlets obtained from previous cuts. Will he be able to make all the threadlets of equal length?

## 说明/提示

Let's consider some testcases of the first test.

In the first testcase, you can apply following operations:

 $ 1, 3, 2 \to 1, 2, 1, 2 \to 1, 1, 1, 1, 2 \to 1, 1, 1, 1, 1, 1 $ .

In the second testcase, you can do nothing, the threadlets are already of equal length.

In the third testcase, it isn't possible to make threadlets of equal length.

## 样例 #1

### 输入

```
15
1 3 2
5 5 5
6 36 12
7 8 7
6 3 3
4 4 12
12 6 8
1000000000 1000000000 1000000000
3 7 1
9 9 1
9 3 6
2 8 2
5 3 10
8 4 8
2 8 4```

### 输出

```
YES
YES
NO
NO
YES
YES
NO
YES
NO
NO
YES
YES
NO
YES
NO```

# 题解

## 作者：wanghaoran00 (赞：4)

### 思路
设最小数为 $a$，在三个数都相等时显然成立，除此之外，$2a=a+a,3a=a+2a=a+a+a,4a=2a+2a=a+a+a+a$ 分别需要操作 $1,2,3$ 次，因此符合条件的三个数需满足 $(a,a,a),(a,a,2a),(a,a,3a),(a,a,4a),(a,2a,2a),(a,2a,3a)$ 中任意一组即可。

ACcode
```
#include <bits/stdc++.h>
using namespace std;
long long T,a[10];
int main(){
    scanf("%lld",&T);
    while(T--){
        scanf("%lld%lld%lld",&a[1],&a[2],&a[3]);
        sort(a+1,a+4);
        if((a[1]==a[2]&&a[2]==a[3])||(a[2]==a[3]&&a[2]==a[1]*2)||(a[1]==a[2]&&a[3]==a[1]*2)||(a[1]==a[2]&&a[3]==a[1]*3)||(a[1]==a[2]&&a[3]==a[1]*4)||(a[2]==a[1]*2&&a[3]==a[1]*3)){
            printf("YES\n");
        }
        else{
            printf("NO\n");
        }
    }
    return 0;
}

```

---

## 作者：include13_fAKe (赞：3)

## 前言
谨以此篇题解纪念我 CF 绿名。
## 题意
题意十分简单，~~就不写了吧~~。

$T$ 组数据。

每组数据给定三个数 $a,b,c$，每一次可以把其中一个数拆成两个数，满足这两个数都是**正整数**。如 $5$ 可以拆成 $1,4$ 或 $2,3$。

询问可不可能在**三次**操作内让所有数**大小相同**。
## 思路
以下设 $a\le b\le c$。（其实简简单单排下序就搞定了）

讨论 $a,b,c$ 之间的大小关系，即可得到答案。

首先，在 $a=b=c$ 时，不需要任何操作就可以使得所有数相等。（~~这还用得着说吗？~~）

其次，在 $a=b$ 且 $c=2a$ 或 $3a$ 或 $4a$ 时，可以通过缩小 $c$ 使得所有数相等，且操作次数在**三次以内**。

再次，在 $a:b:c=1:2:2$ 或 $a:b:c=1:2:3$ 时，可以通过缩小 $b$ 和 $c$ 使得所有数相等，且操作次数在**三次以内**。

可以证明，在其他情况下，不可能在**三次**操作内让所有数**大小相同**。
## 赛时代码
```cpp
#include<bits/stdc++.h>
using namespace std;

void solve(){
	int a,b,c;
	cin>>a>>b>>c;
	if(a>b)	swap(a,b);
	if(b>c)	swap(b,c);
	if(a>b)	swap(a,b);
	if(a==b&&b==c){
		puts("YES");
		return;
	}
	if(a==b&&(a*2==c||a*3==c||a*4==c)){
		puts("YES");
		return;
	}
	if(b==c&&a*2==b){
		puts("YES");
		return;
	}
	if(a*2==b&&a*3==c){
		puts("YES");
		return;
	}
	puts("NO");
	return;
}
int main(){
	int t;
	cin>>t;
	while(t--)	solve();
	return 0;
}
```


---

## 作者：Annihilation_y (赞：2)

# [CF1881B] Three Threadlets 题解

## 题目大意
- $ t $ 组数据，每组数据给三个数 $ a $，$ b $，$ c $。
- 每一次操作，可以将任意一个数拆分成两个**正整数**。
- 询问，可不可以通过**三次以内**的操作，让所有数字大小相同。

## 思路
首先，因为题目中要求让所有数字大小相同，所以可以将 $ a $，$ b $，$ c $ 排序后再来处理。

这里，我们就令 $ a \geq b \geq c $。

然后，再分情况讨论：

1. 如果 $ a = b = c $ ，那么绝对能满足要求。
2. 如果 $ b = c $ 且 $ a = 2b $ 或 $ 3b $ 或 $ 4b $，那么绝对能满足要求。
3. 如果 $ a = b $ 且 $ a = 2c $ 或 $ a=2c $ 且 $ b=3c $，那么也能满足要求。

像这样讨论即可~~水掉此题~~。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int a,b,c,t;
void cl(){
	if(a<b) swap(a,b);
	if(b<c) swap(b,c);
	if(a<b) swap(a,b);
}
bool pd(){
	if(a==b&&a==c)
		return 1;
	if((b==c&&a==b*2)||(b==c&&a==b*3)||(b==c&&a==b*4))
		return 1;
	if((a==c*2&&b==c*2)||(a==c*3&&b==c*2))
		return 1;
	return 0;
}
int main(){
//	freopen("Three Threadlets.in","r",stdin);
//	freopen("Three Threadlets.out","w",stdout);
	scanf("%d",&t);
	while(t--){
		scanf("%d%d%d",&a,&b,&c);cl();
		if(pd()) printf("YES\n");
		else printf("NO\n");
	}
}
```

---

## 作者：gtafics (赞：1)

[洛谷题目链接](https://www.luogu.com.cn/problem/CF1881B) / [CF 题目链接](https://codeforces.com/contest/1881/problem/B)。

## 题目大意

输入三个正整数 $a,b,c$。你可以进行 $3$ 次操作，每次操作可以将任意一个数（在原序列中）分成两部分，要求这两部分之和等于原数。问你是否能在 $3$ 次操作内使得该序列均各个数相等，可行输出 `YES`，否则输出 `NO`。（大小写不区分）

共有 $t$ 组测试数据。

## 解题思路

考虑数 $x$，使它分为由多个数，要求这些数之和 $=x$，且每个数均相等。容易发现这些数是 $x$ 的因数。

因此，为了使 $3$ 个数 $x,y,z$ 构成的序列通过 $0$ 次或多次操作后相等，我们可以将其分为 $(x+y+z) \div \gcd (x,y,z)$ 个 $\gcd (x,y,z)$。

又因为每次操作会使序列长度增加 $1$，所以可直接判断 $(x+y+z) \div \gcd (x,y,z)$ 是否大于 $3+3$（原来已有 $3$ 个数）。 

## 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
long long gcd(long long x,long long y)
{
	long long mod_=x%y;
	while(mod_)
	{
		x=y,y=mod_,mod_=x%y;
	}
	return y;
}
int main()
{
	long long n;
	scanf("%lld",&n);
	for(;n;n-=1)
	{
		long long a,b,c;
		scanf("%lld%lld%lld",&a,&b,&c);
		long long gcd_=gcd(a,gcd(b,c));
		printf(a/gcd_+b/gcd_+c/gcd_<=6?"yes\n":"no\n");
	}
	return 0;
}
```

---

## 作者：kkk_dex (赞：1)

# 题意：
有 $3$ 个数字，每次操作可以任选一个数字将它分为两个**正整数**，且两个正整数之和等于被分的数字。

你**最多**只能进行 $3$ 次操作，最终询问所有数是否相同，是输出 `YES`，否输出 `NO`。


# 思路：
将输入的数进行排序，每次将最大的数分为最小的数和最大的数与最小的数之差，再次将数列排序，进行三次这样的循环，最后判断第一个数是否和最后一个数相同。

### code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,a,b,c,n;
int q[50];
bool q1;
int num,s;
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>a>>b>>c;
		n=3;
		q[1]=a,q[2]=b,q[3]=c;
		sort(q+1,q+1+3);
		q1=0,num=0;
		while(num<3)
		{
			if(q[1]==q[n])
			{
				q1=1;
				break;
			}
			num++;//记录操作次数
			s=q[n];
			q[n]=q[1];
			q[n+1]=s-q[1];//将最大数分裂
			n++;//记录数组共有多少数字
			sort(q+1,q+1+n);//数组更新进行排序
		}
		sort(q+1,q+1+n);
		if(q1==1||q[1]==q[n])
		{
			cout<<"YES\n";
		}
		else
		cout<<"NO\n";
	}
}
```


---

## 作者：lrx___ (赞：1)

**题意简述**

有 $3$ 条绳子，每切分一次可以将一条绳子切成两条绳子，这两条绳子长度之和要等于原来的绳子，且这两条绳子的长度都要是正整数。最多进行 $3$ 次切分，询问是否能切分这 $3$ 条绳子，使得切分后所有绳子的长度都相等。

**思路**

因为最多进行 $3$ 次，所以我们可以从 $0$ 到 $3$ 次依次判断一遍。每切分一次绳子的数量就会加一，于是我们可以求出平均数，再判断是不是每条绳子都是这个平均数的倍数即可。

**代码**

```cpp
#include<cstdio>

using ll=long long;

int main(){
	int T;
	ll a,b,c,s,d1,d2,d3;
	scanf("%d",&T);
	while(T--){
		scanf("%lld%lld%lld",&a,&b,&c);
		s=a+b+c;d1=s/4;d2=s/5;d3=s/6;
//		s为和，di为切分i次时每份应有的长度 
		if(a==b&&b==c){
//			切分0次 
			puts("YES");
		}else if(s%4==0&&a%d1==0&&b%d1==0&&c%d1==0){
//			切分1次 
			puts("YES");
		}else if(s%5==0&&a%d2==0&&b%d2==0&&c%d2==0){
//			切分2次 
			puts("YES");
		}else if(s%6==0&&a%d3==0&&b%d3==0&&c%d3==0){
//			切分3次 
			puts("YES");
		}else{
//			无解 
			puts("NO");
		}
	}
	return 0;
}
```

---

## 作者：1234567890sjx (赞：0)

那肯定是分情况讨论。

令 $a\le b\le c$。如果不满足就交换一下。

如果 $a=b=c$ 那么已经分配完了。

如果 $a=b=2c$ 那么把 $c$ 平均分即可。

如果 $a=2b=2c$ 那么同理，平均分 $b$，然后平均分 $c$。

如果 $a=2b=3c$ 那么把 $b$ 平均分两段，$c$ 平均分三段。只使用了 $3$ 次操作。

如果 $a=b=4c$ 那么 $c$ 平均分成四段，共计使用 $3$ 次操作。

易得其他的情况均无法在 $3$ 次操作内完成。

时间复杂度 $O(1)$。

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

bool check(int *a) {
	if (a[0] == a[1] && a[1] == a[2]) return true;
	if (a[0] == a[1] && a[1] * 2 == a[2]) return true;
	if (a[0] == a[1] && a[1] * 3 == a[2]) return true;
	if (a[0] == a[1] && a[1] * 4 == a[2]) return true;
	if (a[0] * 2 == a[1] && a[0] * 2 == a[2]) return true;
	if (a[0] * 2 == a[1] && a[0] * 3 == a[2]) return true;
	return false;
}

void slv(int tc = 0) {
	if (tc) {
		cerr << "Test Case " << tc << '\n';
	}
	int a[3];
	cin >> a[0] >> a[1] >> a[2];
	sort(a, a + 3);
	cout << (check(a) ? "Yes" : "No") << '\n';
}

signed main() {
	int T;
	cin >> T;
	for (int i = 0; i < T; i++) {
		slv(i + 1);
	}
	return 0;
}
```


---

## 作者：yangmingshuo114514 (赞：0)

## 思路

$3$ 个数，最多 $3$ 次操作，最终可以分为 $3,4,5,6$ 个数。定义 $s=a+b+c$，如果 $s\bmod i\ne0$，那么这 $3$ 个数一定不能被分成 $i$ 个数。否则，设 $x=s\div i$，对于 $a,b,c$ 每一个数，如果有一个数模 $x$ 不为 $0$，那么分成若干个 $x$ 时必然留下无法再分的剩余部分。于是，我们将这 $3$ 个数最终分为 $3,4,5,6$ 个数的方案全讨论一遍，看看有没有一个满足就可以了。

## 代码

```cpp
#include<cstdio>
long long a,b,c,s,x;
bool f;
int t;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%lld%lld%lld",&a,&b,&c);
		s=a+b+c;
		f=0;
		for(int i=3;i<=6;i++)
			if(s%i==0){
				x=s/i;
				if(a%x==0&&b%x==0&&c%x==0) f=1;
			}
		if(f) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}

---

