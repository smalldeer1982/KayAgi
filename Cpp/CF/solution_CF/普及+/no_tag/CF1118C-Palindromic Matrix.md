# Palindromic Matrix

## 题目描述

Let's call some square matrix with integer values in its cells palindromic if it doesn't change after the order of rows is reversed and it doesn't change after the order of columns is reversed.

For example, the following matrices are palindromic:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1118C/1dd62ecf9cdea049a4333ac1caa6ce864c1d5fc5.png)The following matrices are not palindromic because they change after the order of rows is reversed:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1118C/2143b8b786a0f045139a90d99c3f905c3e226fac.png)The following matrices are not palindromic because they change after the order of columns is reversed:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1118C/fe33a9bda586416fffd510345806131041ef4caa.png)You are given $ n^2 $ integers. Put them into a matrix of $ n $ rows and $ n $ columns so that each number is used exactly once, each cell contains exactly one number and the resulting matrix is palindromic. If there are multiple answers, print any. If there is no solution, print "NO".

## 说明/提示

Note that there exist multiple answers for the first two examples.

## 样例 #1

### 输入

```
4
1 8 8 1 2 2 2 2 2 2 2 2 1 8 8 1
```

### 输出

```
YES
1 2 2 1
8 2 2 8
8 2 2 8
1 2 2 1
```

## 样例 #2

### 输入

```
3
1 1 1 1 1 3 3 3 3
```

### 输出

```
YES
1 3 1
3 1 3
1 3 1
```

## 样例 #3

### 输入

```
4
1 2 1 9 8 4 3 8 8 3 4 8 9 2 1 1
```

### 输出

```
NO
```

## 样例 #4

### 输入

```
1
10
```

### 输出

```
YES
10 
```

# 题解

## 作者：yingkeqian9217 (赞：1)

不知道为什么大家的代码都这么长，这里提供一种稍微简洁一点的做法。

首先，所谓的“回文矩阵”就是中心对称的矩阵，即 $n\times n$ 的矩阵 $a$ 满足 $\forall 1\le i,j\le n,a_{i,j}=a_{n-i+1,j}=a_{i,n-j+1}=a_{n-i+1,n-j+1}$。用人话说就是把这个矩阵横竖切成四份，都中心对称。

那么很容易得出，在任意一块中出现的数必定在另外的三块中也有出现，即在整个矩阵中出现了至少四次。考虑到 $1\le a_{i,j}\le 1000$，直接暴力开桶存即可。

那么这样就好了吗？显然没有，注意到在 $n$ 为奇数的情况时，中间的一列和中间的一行刚好在对称轴上。即对于条件 $\forall 1\le i,j\le n,a_{i,j}=a_{n-i+1,j}=a_{i,n-j+1}=a_{n-i+1,n-j+1}$，当 $i=n-i+1$ 或 $j=n-j+1$ 时，该条件退化为二元回文序列的判断。

也就是说，在奇数矩阵中，行 $i=\frac{n+1}{2}$ 与列 $j=\frac{n+1}{2}$ 只需要满足是回文串即可。我们可以像原来一样借助桶将出现两次以上的数填入。

特别的，最中心的数可以任取。

对于无解的情况，只需要在填入的过程中判断即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t[3003],s[31][31];
vector<int>v;
int solve(){
	v.clear();
	for(int i=1;i<=3000;i++)
	 if(t[i]>=2)
	  v.push_back(i);
	for(int i=1;i<=n/2;i++){
		if(v.empty()) return 0;
	 	int x=v[v.size()-1];
	 	t[x]-=2;
	 	s[n/2+1][i]=s[n/2+1][n-i+1]=x;
	 	if(t[x]<2) v.pop_back();
	}
	for(int i=1;i<=n/2;i++){
		if(v.empty()) return 0;
	 	int x=v[v.size()-1];
	 	t[x]-=2;
	 	s[i][n/2+1]=s[n-i+1][n/2+1]=x;
	 	if(t[x]<2) v.pop_back();
	}
	for(int i=1;i<=3000;i++)
	 if(t[i]){
	 	s[n/2+1][n/2+1]=i;
	 	break;
	 }
	return 1;
}
signed main(){
	scanf("%d",&n);
	for(int i=1;i<=n*n;i++){
		int x;
		scanf("%d",&x);
		t[x]++;
	}
	for(int i=1;i<=3000;i++)
	 if(t[i]>=4)
	  v.push_back(i);
	for(int i=1;i<=n/2;i++)
	 for(int j=1;j<=n/2;j++){
	 	if(v.empty()) return puts("NO"),0;
	 	int x=v[v.size()-1];
	 	t[x]-=4;
	 	s[i][j]=s[i][n-j+1]=s[n-i+1][j]=s[n-i+1][n-j+1]=x;
	 	if(t[x]<4) v.pop_back();
	 }
	if(n&1&&!solve()) return puts("NO"),0;
	puts("YES");
	for(int i=1;i<=n;i++,puts(""))
	 for(int j=1;j<=n;j++)
	  printf("%d ",s[i][j]);
	return 0;
}
```

---

## 作者：jiangchen1234 (赞：1)

### Part 1 题意

请看题目翻译。

------------

### Part 2 思路

其实并不难想。

我们可以分情况来讨论。

1. 对于 $n$ 为偶数

首先，如何判断能否组成呢？

对于每一个点（假设坐标为（$cnt1,cnt2$）），我们会发现，对于这点来说，有 $4$ 个点是和它相同的，分别为 $cnt1,cnt2$ 和 $cnt1,n - cnt2 + 1$ 和 $n - cnt1 + 1,cnt2$ 和 $n - cnt1 + 1,n - cnt2 + 1$。

也就是说，对于每一个数，它出现的个数一定要是 $4$ 的倍数。否则，它不能组成矩形。

说完判断，再说构造。

首先，我们可先枚举数字 $i$，看他在序列中的出现次数。

若不为 $0$，则找一个还没没有数的位置，将其填入其中，并将其余的和该点相对应的三个点也填上（即上文说过的点）。

于是我们就完成了对这个情况的讨论。

代码如下：

```cpp

il bool check2() {
	for(rg int i(1); i <= 1000; ++i) {
		if(num[i] % 4) return 1;
	}
	return 0;
}
```

```cpp
if(check2()) {
	puts("NO");
	return;
}
cout<<"YES"<<endl;
for(rg int i(1); i <= 1000; ++i) {
	while(true) {
		if(num[i] != 0) {
			if(!mp[cnt1][cnt2]) {
				mp[cnt1][cnt2] = i;
				mp[n - cnt1 + 1][n - cnt2 + 1] = i;
				mp[n - cnt1 + 1][cnt2] = i;
				mp[cnt1][n - cnt2 + 1] = i;
				++cnt2;
				if(cnt2 > n) {
					cnt2 -= n;
					++cnt1;
				}
				num[i] -= 4;
			} else {
				++cnt2;
				if(cnt2 > n) {
					cnt2 -= n;
					++cnt1;
				}
			}
		} else {
			break;
		}
	}
}
for(rg int i(1); i <= n; ++i) {
	for(rg int j(1); j <= n; ++j) {
		cout<<mp[i][j]<<" ";
	}
	cout<<endl;
}
```

2. 对于 $n$ 为奇数

这一类情况就复杂一些了。

首先，和偶数一样。我们依旧可以发现，以样例 $2$ 为例，如下图，我们可以发现，除了红色部分，其余部分均是和偶数一样 $4$ 个为一组对应的。

![](https://cdn.luogu.com.cn/upload/image_hosting/9n443rs8.png)

还是以样例 $2$ 为例，如下图，我们又可以发现，红色部分是 $2$ 个为一组，共有 $n - 1$ 组，而橙色部分只有 $1$ 个。

![](https://cdn.luogu.com.cn/upload/image_hosting/9ei92a7w.png)

那如何判断呢？

也就是说，对于每一个数，我们讨论其模 $4$ 后余数的情况，在这里设余数为 $x$。

如果 $x == 0$：没有任何事。

如果 $x == 1$：那出现 $1$ 的次数 $+ 1$。

如果 $x == 2$：那出现 $2$ 的次数 $+ 1$。

如果 $x == 3$：那出现 $2$ 和 $1$ 的次数都 $+ 1$。

我们只要判断出现 $1$ 的次数是否为 $1$，且出现 $2$ 的次数是否 $\le n - 1$，且出现 $2$ 的次数是否是 $2$ 的倍数。

若不行，它不能组成矩形。

接下来看构造：

首先，来处理 $1$ 和 $2$：

对于 $1$ 我们将他放在 $n / 2 + 1,n / 2 + 1$ 的位置上。

而对于 $2$，我们 $2$ 个一组，将他们一组放于 $n / 2 + 1$ 这一列上，上下对应。另一组则放在 $n / 2 + 1$ 这一行上，左右对应。

再看 $4$：

对于不在 $n / 2 + 1$ 行上的数或在 $n / 2 + 1$ 列上的数，用偶数的方法来做。

对于在 $n / 2 + 1$ 行上的数或在 $n / 2 + 1$ 列上的数，则用对于 $2$ 的方法来做。

代码如下：

```cpp
il bool check1() {
	for(rg int i(1); i <= 1000; ++i) {
		int x = num[i] % 4;
		if(!x) continue;
		else if(x == 1) {
			if(flag3) return 1;
			flag3 = 1;
			num3 = i;
		} else if(x == 2) {
			if(len1 > n - 1) return 1;
			++len1;
			flag1[len1] = 1;
			num1[len1] = i;
		} else {
			if(len1 > n - 1 || flag3) return 1;
			++len1;
			flag1[len1] = 1;
			num1[len1] = i;
			flag3 = 1;
			num3 = i;
		}
	}
	if(len1 & 1) return 1;
	return 0;
}
```

```cpp
if(n & 1) {
	if(check1()) {
		puts("NO");
		return;
	}
	cout<<"YES"<<endl;
	if(flag3) mp[n / 2 + 1][n / 2 + 1] = num3,--num[num3];
	int cnt3 = 1,cnt4 = 1;
	for(rg int i(1); i <= len1; ++i) {
		if(i & 1) {
			mp[cnt4][n / 2 + 1] = mp[n - cnt4 + 1][n / 2 + 1] = num1[i];
			num[num1[i]] -= 2;
			++cnt4;
		} else {
			mp[n / 2 + 1][cnt3] = mp[n / 2 + 1][n - cnt3 + 1] = num1[i];
			num[num1[i]] -= 2;
			++cnt3;
		}
	}
	for(rg int i(1); i <= 1000; ++i) {
		while(true) {
			if(num[i] != 0) {
				if(!mp[cnt1][cnt2]) {
					if(cnt1 == n / 2 + 1 || cnt2 == n / 2 + 1) {
						mp[cnt4][n / 2 + 1] = mp[n - cnt4 + 1][n / 2 + 1] = mp[n / 2 + 1][cnt3] = mp[n / 2 + 1][n - cnt3 + 1] = i;
						num[i] -= 4;
						++cnt4,++cnt3;
						continue;
					}
					mp[cnt1][cnt2] = i;
					mp[n - cnt1 + 1][n - cnt2 + 1] = i;
					mp[n - cnt1 + 1][cnt2] = i;
					mp[cnt1][n - cnt2 + 1] = i;
					++cnt2;
					if(cnt2 > n) {
						cnt2 -= n;
						++cnt1;
					}
					num[i] -= 4;
				} else {
					++cnt2;
					if(cnt2 > n) {
						cnt2 -= n;
						++cnt1;
					}
				}
			} else {
				break;
			}
		}
	}
	for(rg int i(1); i <= n; ++i) {
		for(rg int j(1); j <= n; ++j) {
			cout<<mp[i][j]<<" ";
		}
		cout<<endl;
	}
}
```

------------
### Part 3 附上完整代码

[带调试代码的代码](https://codeforces.com/problemset/submission/1118/235714050)

```cpp
#pragma comment(linker,"/stack:200000000")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#pragma GCC optimization ("unroll-loops")
#include<bits/stdc++.h>
#define int long long
#define il inline
#define rg register
#define F(i,l,r) for(int i=l,i##end=r;i<=i##end;++i)
#define G(i,l,r) for(int i=l,i##end=r;i>=i##end;--i)
#define endl '\n'
il int read() {
	int s = 0,w = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9') {
		if(ch == '-')w = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9')s = s * 10 + ch - '0',ch = getchar();
	return s * w;
}
il void write(int x) {
	if(0<=x&&x<=9) {
		putchar(x + '0');
		return ;
	}
	write(x/10);
	putchar(x%10+'0');
}
using namespace std;
int t,n,num[1005],mp[1005][1005],cnt1 = 1,cnt2 = 1;//num 表示一个数出现的次数
bool flag1[1005],flag3;//flag1 为 2 的个数
int num1[1005],num3,len1;//num1 为出现 2 的个数的数
il bool check1() {//判断 n 为奇数时能否组成矩形
	for(rg int i(1); i <= 1000; ++i) {
		int x = num[i] % 4;
		if(!x) continue;
		else if(x == 1) {
			if(flag3) return 1;
			flag3 = 1;
			num3 = i;
		} else if(x == 2) {
			if(len1 > n - 1) return 1;
			++len1;
			flag1[len1] = 1;
			num1[len1] = i;
		} else {
			if(len1 > n - 1 || flag3) return 1;
			++len1;
			flag1[len1] = 1;
			num1[len1] = i;
			flag3 = 1;
			num3 = i;
		}
	}
	if(len1 & 1) return 1;
	return 0;
}
il bool check2() {//判断 n 为偶数时能否组成矩形
	for(rg int i(1); i <= 1000; ++i) {
		if(num[i] % 4) return 1;
	}
	return 0;
}
il void solve() {
	n = read();
	for(rg int i(1); i <= n * n; ++i) {//读入
		int x = read();
		++num[x];
	}
	if(n & 1) {//奇数
		if(check1()) {//判断
			puts("NO");
			return;
		}
		cout<<"YES"<<endl;
		if(flag3) mp[n / 2 + 1][n / 2 + 1] = num3,--num[num3];//1的部分
		int cnt3 = 1,cnt4 = 1;//2的部分
		for(rg int i(1); i <= len1; ++i) {
			if(i & 1) {
				mp[cnt4][n / 2 + 1] = mp[n - cnt4 + 1][n / 2 + 1] = num1[i];
				num[num1[i]] -= 2;
				++cnt4;
			} else {
				mp[n / 2 + 1][cnt3] = mp[n / 2 + 1][n - cnt3 + 1] = num1[i];
				num[num1[i]] -= 2;
				++cnt3;
			}
		}
		for(rg int i(1); i <= 1000; ++i) {//4的部分
			while(true) {
				if(num[i] != 0) {
					if(!mp[cnt1][cnt2]) {
						if(cnt1 == n / 2 + 1 || cnt2 == n / 2 + 1) {
							mp[cnt4][n / 2 + 1] = mp[n - cnt4 + 1][n / 2 + 1] = mp[n / 2 + 1][cnt3] = mp[n / 2 + 1][n - cnt3 + 1] = i;
							num[i] -= 4;
							++cnt4,++cnt3;
							continue;
						}
						mp[cnt1][cnt2] = i;
						mp[n - cnt1 + 1][n - cnt2 + 1] = i;
						mp[n - cnt1 + 1][cnt2] = i;
						mp[cnt1][n - cnt2 + 1] = i;
						++cnt2;
						if(cnt2 > n) {
							cnt2 -= n;
							++cnt1;
						}
						num[i] -= 4;
					} else {
						++cnt2;
						if(cnt2 > n) {
							cnt2 -= n;
							++cnt1;
						}
					}
				} else {
					break;
				}
			}
		}
		for(rg int i(1); i <= n; ++i) {//输出
			for(rg int j(1); j <= n; ++j) {
				cout<<mp[i][j]<<" ";
			}
			cout<<endl;
		}
	} else {//偶数
		if(check2()) {//判断
			puts("NO");
			return;
		}
		cout<<"YES"<<endl;
		for(rg int i(1); i <= 1000; ++i) {//构造
			while(true) {
				if(num[i] != 0) {
					if(!mp[cnt1][cnt2]) {
						mp[cnt1][cnt2] = i;
						mp[n - cnt1 + 1][n - cnt2 + 1] = i;
						mp[n - cnt1 + 1][cnt2] = i;
						mp[cnt1][n - cnt2 + 1] = i;
						++cnt2;
						if(cnt2 > n) {
							cnt2 -= n;
							++cnt1;
						}
						num[i] -= 4;
					} else {
						++cnt2;
						if(cnt2 > n) {
							cnt2 -= n;
							++cnt1;
						}
					}
				} else {
					break;
				}
			}
		}
		for(rg int i(1); i <= n; ++i) {//输出
			for(rg int j(1); j <= n; ++j) {
				cout<<mp[i][j]<<" ";
			}
			cout<<endl;
		}
	}
}
signed main() {
	ios::sync_with_stdio(false);
	t = 1;
	while(t--)	solve();
	return 0;
}
```


---

## 作者：wwldx (赞：1)

思路：纯粹的模拟，细心一点就能过
讲下大概思路，首先分情况
假如n是偶数的情况，因为可以进行 **行和列的对换** ，所以每个数字都必须是**4的倍数**，这样才能保证可以随意进行行列对换，同时我们可以得出，左上角部分，也就是1/4的矩阵部分，跟右上角，左下角，右下角都是完全对称的，所以只需要填充左上角即可，其他三个角直接复制
n是奇数的情况，多了一条中心横轴和一条中心竖轴，横轴需要左右对称，竖轴需要上下对称，中心无所谓，而外部仍是上下左右对称
所以继续先填充左上角，横宽1-n/2，纵向1-n/2，每次取4个，假如相同元素不足4个，直接中断，假如左上角全部满足了，再开始铺2条中心线，每次取2个相同的元素，不够了直接中断，最后肯定是剩余最后一个元素，直接放入矩阵中心
所以我们需要大量查询元素数量，这里我使用pair数组，first存储元素大小，second存储元素数量，然后每次根据second大小使用sort，即可方便的得出按数量排序的数列，方便操作
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> P;
P a[1050];
int num[30][30];
int b;
int cmp(P a,P b)
{
	return a.second>b.second;
}
int main()
{
	int n;
	cin>>n;
	for(int i=0;i<n*n;i++)
	{
		cin>>b;
		a[b].first=b;
		a[b].second++;
	}
	int flag=1;//flag默认为1,标志为可以构成回文数组，0为不可构成
	sort(a,a+1050,cmp);//按second大小排序
	if(n%2)//n为奇数
	{
		int d=n/2;//边长 
		int l=0;//数组a的计数器
		for(int i=1;i<=d;i++)//按顺序填充左上角
		{
			for(int j=1;j<=d;j++)
			{
				while(a[l].second<4 and a[l].second!=0)
				l++;//不足四个了，l加1，直到大于等于4个，或者a[l].second==0，就代表跑到底了，因为最后的a[l]的second都是0
				if(a[l].second==0)//跑到底了，4的数量不够多
				{
					flag=0;
					break;//直接break
				}
				a[l].second-=4;
				num[i][j]=a[l].first;//填充左上角
				num[i][n-j+1]=num[i][j];//右上角复制
				num[n-i+1][j]=num[i][j];//左下角复制
				num[n-i+1][n-j+1]=num[i][j];//右下角复制
				if(a[l].second==0)
				++l;
			}
			if(!flag)//假如flag已经是0了，直接break
			break;
		}
		sort(a,a+1050,cmp);//再排序
		l=0;
		int qwe=-1;//默认是-1，假如有a[l].second%2==1,剩下的数字就应该放到中心去，因为没有可以与他对称的其他数字了
		//此时，qwe变为那个数字，假如有多个数字多余，也就是多组a[l].second%2==1，那么就可以直接break
		for(int i=1;i<=d;i++)
		{
			if(a[l].second%2==1 && qwe==-1)//qwe未更新
			{
				qwe=a[l].first;//更新qwe
				--a[l].second;
				num[d+1][d+1]=qwe;
			}
			else
			if(a[l].second%2==1 && qwe!=-1)//qwe已经更新，但是仍有多余数字
			{
				flag=0;//flag变为0，break
				break;
			}
			if(a[l].second<2)
			{
				if(a[l].second==1 && qwe==-1)
				{
					qwe=a[l].first;
					--a[l].second;
					num[d+1][d+1]=qwe;
				}
				else
				if(a[l].second==1 && qwe!=-1)
				{
					flag=0;
					break;
				}
				++l;//计数器l+1
			}
			if(a[l].second<2)//经过上述处理后，a[l].second仍小于2，就代表后续肯定没有大于等于2的了，直接break
			{
				flag=0;
				break;
			}
			a[l].second-=2;
			num[i][d+1]=a[l].first;//填充纵轴
			num[n-i+1][d+1]=num[i][d+1];
			if(a[l].second<2)//以下都为复制粘贴纵轴的操作
			{
				if(a[l].second==1 && qwe==-1)
				{
					qwe=a[l].first;
					--a[l].second;
					num[d+1][d+1]=qwe;
				}
				else
				if(a[l].second==1 && qwe!=-1)
				{
					flag=0;
					break;
				}
				++l;
			}
			if(a[l].second<2)
			{
				flag=0;
				break;
			}
			a[l].second-=2;
			num[d+1][i]=a[l].first;//填充横轴
			num[d+1][n-i+1]=num[d+1][i];
			if(!flag)
			break;
		}
		if(flag)
		{
			sort(a,a+1050,cmp);
			if(a[0].second!=0)
			num[d+1][d+1]=a[0].first;
		}
	} 
	else//n为偶数 
	{
		int d=n/2;//边长 
		int l=0;
		for(int i=1;i<=d;i++)
		{
			for(int j=1;j<=d;j++)
			{
				if(a[l].second%4!=0 or a[l].second<4)//每次找4
				{
					flag=0;
					break;
				}
				a[l].second-=4;
				num[i][j]=a[l].first;//填充左上角
				num[i][n-j+1]=num[i][j];//右上角复制
				num[n-i+1][j]=num[i][j];//左下角复制
				num[n-i+1][n-j+1]=num[i][j];//右下角复制
				if(a[l].second==0)
				++l;
			}
			if(!flag)
			break;
		}
	}
	if(flag)//判断flag
	{
		cout<<"YES\n";
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<n;j++)
			{
				cout<<num[i][j]<<" ";
			}
			cout<<num[i][n]<<"\n";
		}
	}
	else
	{
		cout<<"NO\n";
	}
	return 0;
}
```


---

## 作者：WuMin4 (赞：0)

## 思路

因为回文矩阵左右翻转和上下翻转都不变，所以可以知道回文矩阵一定满足 $a_{i,j}=a_{n-i+1,j}=a_{i,n-j+1}=a_{n-i+1,n-j+1}$。

由于当 $n$ 为奇数，$x=\frac{n+1}{2}$ 时，$x=n-x+1$，所以需要根据 $n$ 的奇偶性分类讨论。

- 当 $n$ 为偶数时

此时不存在 $x$ 满足 $x=n-x+1$，所以所有数字的个数一定为 $4$ 的倍数，直接枚举位置填充即可。

- 当 $n$ 为奇数时

当 $i=\frac{n+1}{2}$ 时 $i=n-i+1$，则只需满足 $a_{i,j}=a_{i,n-j+1}$，此时该数字只要满足为 $2$ 的倍数即可填充，$j$ 同理。

特别的，当 $i=\frac{n+1}{2}$ 且 $j=\frac{n+1}{2}$ 时，该数字无需满足任何条件即可填充。

对于无解的情况，只需在填入时判断即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
int n,a[405],b[25][25];
vector<int> num;
unordered_map<int,int> cnt;
void nxt(int &nx,int &ny){
	if(nx==n/2)
		nx=1,ny++;
	else
		nx++;
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	cin>>n;
	for(int i=1;i<=n*n;i++){
		cin>>a[i];
		if(!cnt[a[i]])
			num.push_back(a[i]);
		cnt[a[i]]++;
	}
	int nx=1,ny=1,zx=1,zy=1;
	bool odd=1;
	for(int v:num){
		if(cnt[v]%4!=0&&n%2==0){
			cout<<"NO";
			return 0;
		}
		if(n%2==1){
			if(cnt[v]%2==1){
				if(odd)
					odd=0,b[n/2+1][n/2+1]=v,cnt[v]--;
				else{
					cout<<"NO";
					return 0;
				}
			}
			if(cnt[v]%4==2){
				if(zx<=n/2)
					b[zx][n/2+1]=v,b[n-zx+1][n/2+1]=v,zx++,cnt[v]-=2;
				else if(zy<=n/2)
					b[n/2+1][zy]=v,b[n/2+1][n-zy+1]=v,zy++,cnt[v]-=2;
				else{
					cout<<"NO";
					return 0;
				}
			}
		}
		while(cnt[v]&&ny<=n/2){
			b[nx][ny]=v;
			b[nx][n-ny+1]=v;
			b[n-nx+1][ny]=v;
			b[n-nx+1][n-ny+1]=v;
			nxt(nx,ny);
			cnt[v]-=4;
		}
	}
	for(int v:num){
		while(cnt[v]){
			if(zx<=n/2)
				b[zx][n/2+1]=v,b[n-zx+1][n/2+1]=v,zx++,cnt[v]-=2;
			else if(zy<=n/2)
				b[n/2+1][zy]=v,b[n/2+1][n-zy+1]=v,zy++,cnt[v]-=2;
			else{
				cout<<"NO";
				return 0;
			}
		}
	}
	cout<<"YES"<<endl;
	for(int i=1;i<=n;i++,cout<<endl)
		for(int j=1;j<=n;j++)
			cout<<b[i][j]<<" ";
	return 0; 
}
```

---

## 作者：LZYAC (赞：0)

# 思路
模拟。

通过样例发现分两种情况。

- $N$ 为偶数

把矩形分成四个部分，像这样：![](https://cdn.luogu.com.cn/upload/image_hosting/c51xsk0d.png)
那么可以发现，每个部分填的数肯定一样。于是就可以开始填了。当某个元素个数不是四的倍数时无解。

也就是说，我们只要枚举左上部分的元素，利用刚才的性质：

$a_{i,j}=a_{n-i+1,j}=a_{i,n-j+1}=a_{n-i+1,n-j+1}$

（左上，右上，左下，右下）
进行填充即可。
- $N$ 为奇数

同偶数，但是中间的一行一列会被空出来，于是再两个两个填即可，中间的一个最后填上。填完后有没填到的就是无解。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int mp[1010],a[510][510],n,x,flag;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n*n;i++){
		scanf("%d",&x);
		mp[x]++;
	}
	for(int i=1;i<=1000;i++){
		if(mp[i]%2==1){
			flag=i;
			break;
		}
	}
	mp[flag]--;
	if(n%2==0){
		for(int i=1;i<=n/2;i++){
			for(int j=1;j<=n/2;j++){
				for(int k=1;k<=1000;k++){
					if(a[i][j]==0&&mp[k]>=1&&mp[k]%4==0){
						a[i][j]=k;
						a[n-i+1][j]=k;
						a[i][n-j+1]=k;
						a[n-i+1][n-j+1]=k;
						mp[k]-=4;
						break;
					}
				}
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(a[i][j]==0){
					printf("NO\n");
					return 0;
				}
			}
		}
		printf("YES\n");
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				printf("%d ",a[i][j]);
			}
			printf("\n");
		}
	}
	else{
		a[n/2+1][n/2+1]=flag;
		for(int i=1;i<=n/2;i++){
			for(int j=1;j<=n/2;j++){
				for(int k=1;k<=1000;k++){
					if(mp[k]>=4&&a[i][j]==0){
						a[i][j]=k;
						a[n-i+1][j]=k;
						a[i][n-j+1]=k;
						a[n-i+1][n-j+1]=k;
						mp[k]-=4;
						break;
					}
				}
			}
		}
		for(int i=1;i<=n/2;i++){
			for(int k=1;k<=1000;k++){
				if(a[n/2+1][i]==0&&mp[k]>=2){
					a[n/2+1][i]=k;
					a[n/2+1][n-i+1]=k;
					mp[k]-=2;
				}
			}
		}
		for(int i=1;i<=n/2;i++){
			for(int k=1;k<=1000;k++){
				if(a[i][n/2+1]==0&&mp[k]>=2){
					a[i][n/2+1]=k;
					a[n-i+1][n/2+1]=k;
					mp[k]-=2;
				}
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(a[i][j]==0){
					printf("NO\n");
					return 0;
				}
			}
		}
		printf("YES\n");
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				printf("%d ",a[i][j]);
			}
			printf("\n");
		}
	}
	return 0;
}
```

---

## 作者：Merge_all (赞：0)

### 思路
 - **模拟**

### 过程：
1. 先记录每个数出现的个数，如果有奇数个，就用一个变量存着，率先考虑它。
2. 判断 $n$ 的**奇偶性**。然后暴力枚举每个位置，并枚举每个数是否能放在这里（**条件：是 4 的倍数且不为 0 **，**奇数**的话还有判断是否是 2 的倍数，因为 $n$ 为奇数**每行每列中间**还可以放数），在根据对称将数放入其中。
3. 代码上的细节很多，仔细调代码。

### 代码：
```c
#include <bits/stdc++.h>
using namespace std;

const int N = 600;

int n;
int ans[N][N], root, Max;
map<int, int> mp;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for (int i = 1, x; i <= n * n; i++) {
		cin >> x;
		mp[x]++;
		Max = max(Max, x);//最大的一个数
	}
	for (int i = 1; i <= Max; i++) {
		if (mp[i] & 1) {
			root = i;//找到出现次数为奇数的数
			break;
		}
	}
	mp[root]--;//先处理
	if (n & 1 == 0) {//判断奇偶性，分别讨论
		//三重循环暴力枚举
		for (int i = 1; i <= n / 2; i++) {
			for (int j = 1; j <= n / 2; j++) {
				for (int k = 1; k <= Max; k++) {
					if (!ans[i][j] && mp[k] && mp[k] % 4 == 0) {
						ans[i][j] = k;
						ans[n - i + 1][j] = k;
						ans[i][n - j + 1] = k;
						ans[n - i + 1][n - j + 1] = k;
						mp[k] -= 4;
						break;
					}
				}
			}
		}
		//如果有空没有填，说明不行
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (!ans[i][j]) {
					cout << "NO\n";
					return 0;
				}
			}
		}
		//否则说明可以，输出答案
		cout << "YES\n";
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				cout << ans[i][j] << " ";
			}
			cout << "\n";
		}
	} else {
		ans[n / 2 + 1][n / 2 + 1] = root;//先将正中心的位置填好
		//同偶数的方式处理
		for (int i = 1; i <= n / 2; i++) {
			for (int j = 1; j <= n / 2; j++) {
				for (int k = 1; k <= Max; k++) {
					if (mp[k] >= 4 && !ans[i][j]) {
						ans[i][j] = k;
						ans[n - i + 1][j] = k;
						ans[i][n - j + 1] = k;
						ans[n - i + 1][n - j + 1] = k;
						mp[k] -= 4;
						break;
					}
				}
			}
		}
		//奇数每行每列的中心也可以填数字，所以还要处理
		for (int i = 1; i <= n / 2; i++) {
			for (int j = 1; j <= Max; j++) {
				if (!ans[n / 2 + 1][i] && mp[j] >= 2) {
					ans[n / 2 + 1][i] = j;
					ans[n / 2 + 1][n - i + 1] = j;
					mp[j] -= 2;
				}
			}
		}
		for (int i = 1; i <= n / 2; i++) {
			for (int j = 1; j <= Max; j++) {
				if (!ans[i][n / 2 + 1] && mp[j] >= 2) {
					ans[i][n / 2 + 1] = j;
					ans[n - i + 1][n / 2 + 1] = j;
					mp[j] -= 2;
				}
			}
		}
		//判断是否还有空位
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (!ans[i][j]) {
					cout << "NO\n";
					return 0;
				}
			}
		}
		cout << "YES\n";
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				cout << ans[i][j] << " ";
			}
			cout << "\n";
		}
	}
	return 0;
}
```

---

## 作者：copper_ingot (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1118C)

个人评价：思路黄，代码绿。细节很多。

在一个回文矩阵 $a$ 中，对于任意 $1 \le i,j \le n$，都有 $a_{i,j} = a_{i,n-j+1} = a_{n-i+1,j} = a_{n-i+1,n-j+1}$。

所以，当 $i \ne n - i + 1$ 且 $j \ne n - j + 1$ 时，在 $a_{i,j}$ 上的数会出现 $4$ 的倍数次；当 $i = n - i + 1$ 且 $j = n - j + 1$ 时，在 $a_{i,j}$ 上的数会出现奇数次；否则 $a_{i,j}$ 上的数的出现次数模 $4$ 余 $2$。

当 $n$ 为偶数时，只会出现上面的第一种情况。所以，每个数字的出现次数必须都是 $4$ 的倍数，否则会无解。对于如何构造，我们只要枚举左上角 $\frac{n}{2} \times \frac{n}{2}$ 的矩阵，再根据对称性填补剩余的空缺。

当 $n$ 为奇数时，有以下步骤：

![](https://cdn.luogu.com.cn/upload/image_hosting/q45s8ppw.png?x-oss-process=image/resize,m_lfit,h_340,w_450)

1. 用 $n$ 为偶数时的方法先填好涂红色的部分。

2. 找到剩余次数是偶数的数字。如果剩余次数是奇数，将其用另一个变量 $t$ 记录。

3. 再次利用对称性（上下对称或左右对称）填好黄色的部分。

4. 把最后的 $t$ 填进中心的白色部分。

具体实现比较复杂，大家看代码注释就好

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, a[1001], cnt[1001], ans[100][100], b[1001];//n、原序列、桶、生成的矩阵、预备序列 
int main(){
	scanf("%d", &n);
	for (int i = 1; i <= n * n; i++){scanf("%d", &a[i]); cnt[a[i]]++;}//用桶计数 
	int c = 0;//一个计数器 
	for (int i = 1; i <= 1000; i++){
		for (int j = 1; j <= cnt[i] / 4; j++){b[++c] = i;}
		cnt[i] %= 4;
	}//把能放进预备序列里的数都放进去 
	if (c < (n / 2) * (n / 2)){puts("NO"); return 0;}//如果预备序列里数不够就退出 
	for (int i = 1; i <= n / 2; i++)
		for (int j = 1; j <= n / 2; j++){
			int k = b[c]; c--;//从后往前填，这样比较方便 
			ans[i][j] = k, ans[n - i + 1][j] = k;
			ans[i][n - j + 1] = k, ans[n - i + 1][n - j + 1] = k;
		}//填偶数（奇数的红色部分） 
	if (n % 2 == 1){//以下是奇数黄白色部分 
		int t = 0;
		for (int i = 1; i <= c; i++) b[i + c] = b[i];
		c *= 2;//因为原预备序列里一个数代表填4个而现在只代表填2个，所以要复制一遍 
		for (int i = 1; i <= 1000; i++){
			for (int j = 1; j <= cnt[i] / 2; j++) b[++c] = i;
			if (cnt[i] % 2) t = i;//记录t 
		}//再次把能放进预备序列里的数都放进去
		if (c < n / 2 * 2){puts("NO"); return 0;}//数不够就退出 
		for (int i = 1; i <= n / 2; i++){
			int k = b[c]; c--;
			ans[i][n / 2 + 1] = k, ans[n - i + 1][n / 2 + 1] = k;//横向 
		}
		for (int i = 1; i <= n / 2; i++){
			int k = b[c]; c--;
			ans[n / 2 + 1][i] = k, ans[n / 2 + 1][n - i + 1] = k;//竖向 
		}
		if (!t){puts("NO"); return 0;}
		ans[n / 2 + 1][n / 2 + 1] = t;//填中心 
	}
	puts("YES");
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++) printf("%d ", ans[i][j]);//输出答案 
		puts("");
	}
	return 0;
}
```

---

