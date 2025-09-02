# Simple Subset

## 题目描述

A tuple of positive integers $ {x_{1},x_{2},...,x_{k}} $ is called simple if for all pairs of positive integers $ (i,j) $ ( $ 1<=i&lt;j<=k $ ), $ x_{i}+x_{j} $ is a prime.

You are given an array $ a $ with $ n $ positive integers $ a_{1},a_{2},...,a_{n} $ (not necessary distinct). You want to find a simple subset of the array $ a $ with the maximum size.

A prime number (or a prime) is a natural number greater than $ 1 $ that has no positive divisors other than $ 1 $ and itself.

Let's define a subset of the array $ a $ as a tuple that can be obtained from $ a $ by removing some (possibly all) elements of it.

## 样例 #1

### 输入

```
2
2 3
```

### 输出

```
2
3 2
```

## 样例 #2

### 输入

```
2
2 2
```

### 输出

```
1
2
```

## 样例 #3

### 输入

```
3
2 1 1
```

### 输出

```
3
1 1 2
```

## 样例 #4

### 输入

```
2
83 14
```

### 输出

```
2
14 83
```

# 题解

## 作者：xunhuanyihao (赞：5)

### CF665D Simple Subset
我们发现，如果序列中出现除了 $1$ 的两个奇数或两个偶数，则他们相加会变成一个非 $2$ 的偶数，而这些偶数都为合数，所以一个序列中最多有一个 非 $1$ 奇数和一个偶数。且要求这两个数相加为质数。我们也可以只选一个任意的数，也是满足条件的（因为题目要求的是两两相加，一个数都没法两两相加）。
接下来考虑 $1$ 的情况，如果选了 $1$，就不能再选非 $1$ 奇数了，因为奇数 $+1$ 等于偶数且这个偶数不为 $2$，即必然是一个合数，那么如果选 $1$，我们只能再选一个偶数，且这个偶数 $+1$ 为质数，这种情况的答案就是 $1$ 的个数 $+1$。最后在所有情况中取最大值即可。时间复杂度 $O(n^2)$。

Code：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
typedef long long ll;
typedef pair<int, int> pii;
int n, cnt, a[N], ans, c0, c1;
pii c2;
bool chk(int x) {
    if (x < 2) return false;
    for (int i = 2; i * i <= x; i++) if (x % i == 0) return false;
    return true;
}
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        cnt += a[i] == 1;
        ans = max(ans, 1), c0 = a[i];
    }
    ans = max(ans, cnt);
    for (int i = 1; i <= n; i++) {
        if (a[i] % 2 == 0 && cnt && chk(a[i] + 1)) ans = max(ans, cnt + 1), c1 = a[i];
        for (int j = i + 1; j <= n; j++) {
            if (a[i] % 2 != a[j] % 2 && chk(a[i] + a[j])) ans = max(ans, 2), c2 = {a[i], a[j]};
        }
    }
    printf("%d\n", ans);
    if (ans == 1) printf("%d\n", c0);
    else if (ans >= 2 && c1) {
        printf("%d ", c1);
        for (int i = 1; i <= cnt; i++) printf("1 ");
        puts("");
    } else if (ans == 2 && c2.first) printf("%d %d\n", c2.first, c2.second);
    else if (ans == cnt) {
        for (int i = 1; i <= cnt; i++) printf("1 ");
        puts("");
    }
    return 0;
}
```

---

## 作者：fuxuantong123 (赞：1)

# CF665D Simple Subset 题解
## 思路
分类讨论：

1. 一个奇数和一个偶数加起来是一个质数（双奇和双偶显然不可能是质数）。
2. 一堆一和一个比质数小一的数。
3. 一个数。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[1010];
int main(){
	int n;
	scanf("%d",&n);
	int x,y;
	int f=0;
	int cnt=0;
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		if(a[i]==1){
			cnt++;
		}
	}
	for(int i=1;i<=n;i++){
		if(f){
			break;
		}
		for(int j=i+1;j<=n;j++){
			if(i!=j){
				if((a[i]+a[j])%2!=0){
					int fw=a[i]+a[j];
					int flag=1;
					for(int k=2;k*k<=fw;k++){
						if(fw%k==0){
							flag=0;
							break;
						}
					}
					if(flag){
						x=a[i];
						y=a[j];
						f=2;
						break;
					}
				}
			}
		}
	}
	int ff=0;
	if(cnt){
		for(int i=1;i<=n;i++){
			if(a[i]==1){
				continue;
			}
			int fw=a[i]+1;
			int flag=1;
			for(int j=2;j*j<=fw;j++){
				if(fw%j==0){
					flag=0;
					break;
				}
			}
			if(flag){
				ff=i;
				break;
			}
		}
	}
	if(cnt>=f && cnt){
		if(ff){
			printf("%d\n",cnt+1);
		}
		else{
			printf("%d\n",cnt);
		}
		int fw=0;
		for(int i=1;i<=cnt;i++){
			printf("1 ");
		}
		if(ff){
			printf("%d",a[ff]);
		}
	}
	else if(f){
		printf("2\n%d %d",x,y);
	}
	else{
		printf("1\n%d",a[1]);
	}
return 0;
}
```


---

## 作者：XL4453 (赞：1)

### $\text{Difficulty : 1800}$

---
### 解题思路：

考虑分情况讨论，分别统计：
1. 比某个质数小一的数和若干个一。
2. 一个奇数和一个偶数。
4. 单独一个数。

这三种情况，取最大值即可。

---
考虑推导过程。任何一个质数只可能是由一个奇数和一个偶数或者两个 $1$ 构造而成，所以如果没有 $1$ 的协助，最多只能有两个数被选中，否则就是若干个 $1$ 和一个能和 $1$ 构成质数的数。


---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,num[1005],ans,c[3000005],pri[3000005],tot,cnt,flag1,flag2,flag3;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&num[i]);
	sort(num+1,num+n+1);
	for(int i=1;i<=n;i++)if(num[i]==1)cnt++;
	for(int i=2;i<=2000000;i++){
		if(c[i]==0)pri[++tot]=i;
		for(int j=1;j<=tot;j++){
			if((long long)i*(long long)pri[j]>2000000)break;
			c[i*pri[j]]=1;
			if(i%pri[j]==0)break;
		}
	}
	ans=cnt;flag1=-1;
	for(int i=cnt+1;i<=n;i++){
		if(c[num[i]+1]==0){
			if(ans>=cnt+1)continue;
			ans=cnt+1;
			flag1=1;flag2=i;
		}
		for(int j=cnt+1;j<=n;j++){
			if(c[num[i]+num[j]]==0){
				if(ans>=2)continue;
				ans=2;
				flag1=2;flag2=i;flag3=j;
			}
		}
	}
	if(ans==0){
		printf("%d\n%d\n",1,num[1]);
		return 0;
	}
	printf("%d\n",ans);
	if(flag1==-1){
		for(int i=1;i<=ans;i++)printf("%d ",1);
		printf("\n");
		return 0;
	}
	if(flag1==1){
		for(int i=1;i<=ans-1;i++)printf("%d ",1);
		printf("%d\n",num[flag2]);
		return 0;
	}
	printf("%d %d\n",num[flag2],num[flag3]);
	return 0;
}
```


---

## 作者：世末OIer (赞：1)

显而易见，有4种情况：

1.无限个1，一个偶数且这个偶数+1是质数

2.所有都是1

3.1奇1偶

4.任意一个数

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1001],cnt[1000001],n;
int nisp[2000001];
int main(){
	int i,j;
	cin>>n;
	nisp[0]=nisp[1]=1;
	for(i=2;i<=2000000;++i)
		if(!nisp[i])
			for(j=i+i;j<=2000000;j+=i) nisp[j]=1;
	for(i=0;i<n;++i) cin>>a[i],++cnt[a[i]];
	if(cnt[1]){//case 1
		for(i=2;i<=1000000;i+=2) if(cnt[i] and !nisp[i+1]){
			cout<<cnt[1]+1<<endl;
			for(j=0;j<cnt[1];++j) cout<<1<<' ';
			cout<<i<<endl;
			return 0;
		}		
	}
	if(cnt[1]>=2){//case 2
		cout<<cnt[1]<<endl;
		for(i=0;i<cnt[1];++i) cout<<1<<' ';
		cout<<endl;
		return 0;
	}
	for(i=0;i<n;++i) if(a[i]&1) for(j=0;j<n;++j) if(!(a[j]&1)) if(!nisp[a[i]+a[j]]){  //case 3
		cout<<2<<endl;
		cout<<a[i]<<' '<<a[j]<<endl;
		return 0;
	}
	cout<<1<<endl<<a[0]<<endl;  //case 4
	return 0;
}
```

---

## 作者：yangxikun (赞：0)

### 题目传送门

[洛谷](https://www.luogu.com.cn/problem/CF665D) [CF](https://codeforces.com/problemset/problem/665/D)

### 题目大意

给定一个数组，请从中挑出一些数（可以是 $1$ 个），使得其中任意两个数之和都为质数。

你希望挑出尽量多的数，请给出方案，挑出的数不一定要按顺序输出。

### 解法

既然这题涉及到质数，那我们先用埃氏筛（$ip$ 数组）。

这题可以分情况讨论。通常，我们可以选所有的 $1$，如果可以再选一个偶数；保底选项是随便两个凑一个质数；超级保底选项是随便选一个数。

详情见代码。

### 代码

[CF 提交记录](https://codeforces.com/problemset/submission/665/295485939)

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
int a[1005];
bool ip[2000005];//质数表
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	for(int i=2;i<=2000005;i++){
		if(ip[i]==0){
			for(int j=i+i;j<=2000005;j+=i)ip[j]=1;
		}
	}
	int n,cnt1=0,add1=0,u=0,v=0;//分别为1的个数，最后一个加1是质数的数，两个加起来是质数的数
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>a[i];
		if(a[i]==1)cnt1++;
		else if(!ip[a[i]+1])add1=a[i];
		for(int j=0;j<i;j++)if(!ip[a[i]+a[j]])u=a[i],v=a[j];
	}
	if(cnt1+(add1!=0)>2){
		cout<<cnt1+(add1!=0)<<endl;
		for(int i=0;i<cnt1;i++)cout<<1<<" ";
		if(add1)cout<<add1;
	}
	else if(u)cout<<2<<endl<<u<<" "<<v;
	else cout<<1<<endl<<a[0];
	return 0;
}
```

---

## 作者：huangzhixia (赞：0)

【**前言**】

板刷教育性 CF 的时候刷到了这题，感觉挺有意思就来写题解了。

-------------
【**解法**】

一步步进行考虑。

首先是偶数加偶数，一定等于偶数，也就是说这个数一定存在 $2$ 这个因数，那么加上 $1$ 和这个数本身，所以这个数不可能是质数。拓展开来，任意个数个偶数相加不可能为质数。

奇数加奇数等于偶数，同上，此时不可能是质数。也可以进行扩展：偶数个奇数相加，最后得出来的是偶数，也就不可能是质数。

以上是不可能是质数的情况。

还有一个奇数加偶数为质数的情况，因为得数是奇数，有可能为质数。

很多 $1$ 和一个比质数少 $1$ 的数。那么我们次数需要有偶数个 $1$ 才有肯能为质数，因为其中一个 $1$ 给了比质数少 $1$ 的数，那个数就成了质数，所以剩下的就是一个奇数，这样相加才有可能为质数。

还有一种最简单的情况，一个质数。

根据以上进行分类讨论，进行枚举即可通过本题。

---------------

【**代码**】

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, a[1001], tot;

inline bool solve(int x) {
	for (int mod = 2; mod <= x / mod; mod++)
		if (!(x % mod)) 
			return 0; //return false;
	return 1; //return true;
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) 
		scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++)
		if (a[i] == 1)
			tot += 1;
	if (tot <= 1) {
		for (int i = 1; i <= n; i++) 
			for (int j = i + 1; j <= n; j++) 
				if ((a[i] & 1) != (a[j] & 1) && solve(a[i] + a[j])) {
					puts("2");
					printf("%d %d\n", a[i], a[j]);
					return 0;
				}
		printf("1\n%d\n", a[1]);
	} else {
		int sum = 0;
		for (int i = 1; i <= n; i++) {
			if (solve(a[i] + 1) && a[i] != 1) {
				sum = a[i];
				break;
			}
		}
		printf("%d\n", tot + (sum != 0));
		for (int i = 1; i <= tot; i++) 
			printf("1 ");
		if (sum)
			printf("%d\n", sum);
	}
}

```

---

## 作者：QWQ_123 (赞：0)

显然的，偶数加偶数为偶数不是素数（其中这两个作为加数的偶数都 $\ge2$）。

然后奇数加奇数为偶数，除了这两个奇数都为 $1$ 以外都不是素数。

那么考虑先计算出这个序列中 $1$ 的个数。

若 $1$ 的个数 $\ge2$，那么一定全选 $1$，因为若不选一，那么最多只能选 $2$ 个数，又全选 $1$ 一定合法，所以 $1$ 全选，然后再判断有没有一个数 $+1$ 是质数。

否则就暴力枚举两个数，然后判断和是不是质数。

```cpp
#include <bits/stdc++.h>

using namespace std;

int n;
int a[1010];
int cnt1 = 0;

bool prime(int a) {
	for (int i = 2; i <= a / i; ++i)
		if (a % i == 0) return false;
	return true;
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]), cnt1 += (a[i] == 1);

	if (cnt1 <= 1) {
		for (int i = 1; i <= n; ++i) {
			for (int j = i + 1; j <= n; ++j) {
				if ((a[i] & 1) != (a[j] & 1) && prime(a[i] + a[j])) {
					printf("%d\n", 2);
					printf("%d %d\n", a[i], a[j]);
					return 0;
				}
			}
		}

		printf("1\n%d\n", a[1]);
	} else {
		int s = 0;
		for (int i = 1; i <= n; ++i) {
			if (prime(a[i] + 1) && a[i] != 1) {
				s = a[i];
				break;
			}
		}

		printf("%d\n", cnt1 + (s != 0));
		for (int i = 1; i <= cnt1; ++i) printf("%d ", 1);
		if (s != 0)
			printf("%d\n", s);
	}

	return 0;
}
```

---

