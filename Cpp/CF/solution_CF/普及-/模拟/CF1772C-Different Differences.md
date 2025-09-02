# Different Differences

## 题目描述

An array $ a $ consisting of $ k $ integers is strictly increasing if $ a_1 < a_2 < \dots < a_k $ . For example, the arrays $ [1, 3, 5] $ , $ [1, 2, 3, 4] $ , $ [3, 5, 6] $ are strictly increasing; the arrays $ [2, 2] $ , $ [3, 7, 5] $ , $ [7, 4, 3] $ , $ [1, 2, 2, 3] $ are not.

For a strictly increasing array $ a $ of $ k $ elements, let's denote the characteristic as the number of different elements in the array $ [a_2 - a_1, a_3 - a_2, \dots, a_k - a_{k-1}] $ . For example, the characteristic of the array $ [1, 3, 4, 7, 8] $ is $ 3 $ since the array $ [2, 1, 3, 1] $ contains $ 3 $ different elements: $ 2 $ , $ 1 $ and $ 3 $ .

You are given two integers $ k $ and $ n $ ( $ k \le n $ ). Construct an increasing array of $ k $ integers from $ 1 $ to $ n $ with maximum possible characteristic.

## 样例 #1

### 输入

```
7
5 9
4 12
3 3
3 4
4 4
4 6
8 11```

### 输出

```
1 3 4 7 8
2 4 7 12
1 2 3
1 3 4
1 2 3 4
2 4 5 6
1 2 3 5 6 7 8 11```

# 题解

## 作者：a2lyaXNhbWUgbWFyaXNh (赞：15)

如果没有 $n$ 的限制，我们很容易想出来，只要让差为 $[1,2,3,...]$ 这样排列下去就可以了。

但是，题目里有对大小的限制 $n$。所以对于数列的第 $i\ (i\in[1,k])$ 项，我们要其为 $\min(i\times\dfrac{1}{2}(i-1),n-k+i)$，以保证不会超出 $n$。	

```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
    int t,k,n;
	cin>>t;
	while(t--){
		cin>>k>>n;
		for(int i=1;i<=k;++i)
			cout<<min(1+i*(i-1)/2,n-k+i)<<" ";
		cout<<'\n';
	}
	return 0;
}
```

---

## 作者：CR7_houyetong (赞：11)

# 鸣谢
- 感谢管理员 @[Maxmilite](https://www.luogu.com.cn/user/274993)，多次指出本题解的不妥当之处。
- 感谢 @[tangrunxi](https://www.luogu.com.cn/user/231147)，本题解参考了一下他的代码并做出了细小改动。

# 题意
- 给定一个数组，把这个数组相邻两个数的差列出来，汇聚成另一个数组，这个数组有 $n$ 个不同的值，就代表这个数组的特征数。
- 现在给定 $n$ 和 $k$，让你构造出一个长度为 $k$ 且数组中每个数都不超过 $n$ 的一个**严格递增数组**，使这个数组的特征数尽量大，并输出这个数组。
- 共有 $t$ 组独立的询问，$1\le t\le 819$ 且 $1\le k\le n\le 40$。

# 分析
显然这题的算法是贪心。让特征数尽量大，那我们就可以让每两数之差都变得不一样，设定为 $ [1, 2, 3, 4, 5\cdots ] $。

------------
$\texttt{Q:}$  什么要设定为 $ [1, 2, 3, 4, 5\cdots] $ 而非 $ [1, 3, 5, 7, 9\cdots] $、$ [1, 100, 1000, 10000, 100000\cdots] $ 等其他数组呢？

$\texttt{A:}$ 因为题目中明确表明构造的数组有一个上限 $n$，数组中的每个数都不能超过 $n$，假如不把两数之差设置为 $ [1, 2, 3, 4, 5\cdots] $ 的话，那肯定就不是最优解，到后面可能会超过 $n$。

------------
既然我们把每两数之差给定下来了，那么就这样结束了吗？并没有，因为加到后面可能会超出上限 $n$。例如样例中的 $k=5$ 且 $n=9$ 的情况下，第一个数是 $1$，第二个数是 $1+1=2$，第三个数是 $2+2=4$，第四个数是 $4+3=7$，都很正常。

那么第五个数呢？$7+4=11$，超过了上限 $n=9$，怎么办呢？我们只能再次利用贪心，既然离最优解有差距，那么就让这个差距变小些，我们需要让后面的数足够凑出数组的长度。

我们找到满足条件的最后一个数，之后不满足条件的数就以它为基准，依次递增 $1$，这样的话，只和前面的 $1$ 重复，把损失降到了最小，且不会超过上限 $n$。那么，代码就有了。

# 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int t,n,i,j,k,cnt1,cnt2,a[10010];
signed main(){
	cin>>t;
	while (t--){
		cin>>k>>n;
		memset(a,0,sizeof(a));
		a[1]=1;
		cnt1=2;
		for (i=0;i<k;i++){
			if (n-a[cnt1-1]>k-2){
				a[cnt1]=a[cnt1-1]+cnt1-1;
				cnt1++;
			} 
			else{
				cnt2=a[cnt1-1]+1;
				for (j=cnt1;j<=k;j++){
					a[j]=cnt2;
					cnt2++;
				}
			}
		}
		for (i=1;i<=k;i++)
		  cout<<a[i]<<" ";
		cout<<endl;
	}
	return 0;
}
```
代码参考了 @[tangrunxi](https://www.luogu.com.cn/user/231147) 的并做出了一些修改，因为我的思路和他的很像，侵删。

---

## 作者：ImNot6Dora (赞：5)

本题显然是一道贪心题，差值序列为 $[1,2,3,4,5,...]$。

但是由于 $n$ 的限制，我们必须在输出之前提前预判，为了损失最小，但继续累加的条件不成立且 $i<k$ 时，我们后面每次只能加 $1$。

用 $ans$ 和 $cnt$ 分别表示前一个数字和差值，显然 $ans+cnt$ 表示新的值，而 $n-ans-cnt$ 则表示剩下最多的能增加的次数，只要这个次数大于等于 $k-i$ 也就是剩下的元素个数，就可以继续累加，否则就将元素 $+1$。

具体分析见代码注释。

# C++ CODE:
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		int k,n;
		int ans=1;//前一个数字，第一次由于前面没有数字，所以代表第一个数字 
		int cnt=0;//差值，由于第一次ans代表第一个数字，所以为零 
		cin>>k>>n;
		for(int i=1;i<=k;i++){
			if(n-ans-cnt>=k-i)ans+=cnt++;//如果剩下输出个数够用就继续累加 
			else ans++;//否则就用最节省的方式+1 
			cout<<ans<<' ';
		}
		cout<<endl;
	}
	return 0;
}
```
By ImNot6Dora

---

## 作者：tangrunxi (赞：3)

首先构造的策略很显然，肯定是想让相邻数差依次为 $[1,2,3,4,...]$，原数组从 $1$ 开始，即为 $[1,2,4,7,11,...]$。要注意的是不能这样一直操作。需要有足够的数能使数组恰好为 $n$ 个。例如样例 $k=5,n=9$，如果我们构造 $[1,2,4,7,11]$ 会出现爆掉的情况。再例如 $k=8,n=11$，我们如果构造出 $[1,2,4,7,11]$，之后就没有足够的数凑出 $8$ 个数了。因此我们在操作的时候，需要让后面的数足够凑出数组长度。

假设当前位置是 ```i```，后面的数就有 ```k-i``` 个，如果 $n-a_{i+1}>k-i$，就可以进行一次操作。若不满足，则不能进行操作，数组当前位置 $a_i$，后面的数只能是 $[a_i+1,a_i+2,...,a_i+k-i]$。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t,n,k,a[100001];
	cin>>t;
	for(int i=0;i<t;++i){
		cin>>k>>n;
		memset(a,0,sizeof(a));
		int cnt=2;
		for(int j=0;j<k;++j){
			a[1]=1;
			if(n-a[cnt-1]>k-2){
				a[cnt]=a[cnt-1]+cnt-1;
				++cnt;
			} 
			else{
				int s=a[cnt-1]+1;
				for(int x=cnt;x<=k;++x){
					a[x]=s;
					s++;
				} 
			}
		}
		for(int y=1;y<=k;++y) cout<<a[y]<<" ";
		cout<<endl;
	}
	return 0;
}
```


---

## 作者：Lovely_Elaina (赞：2)

看完题目，我们可以发现两个要点：

1. 特征数为相邻两数差的不同值的个数。
2. 特征数尽可能大。
3. 输出的是严格递增数列。

提示：此题输出不唯一，样例只需理解，程序输出不应该全等于样例。

---

我们以样例第一组输入数据为例讲解。

```
5 9
```

首先我们容易想到造一个差为 $[1,2,3,4\ldots]$ 的数列，我们定义为数列 $A$，我们直接输出看看。

```cpp
for(int i = 1; i <= k; i++)
    cout << 1 + i * (i - 1) / 2 << " ";
```

```
1 2 4 7 11
```

但是题目要求每个数都不超过 $n$，也就是说，到这个数列中的其中一个数时，我们已经使特征数尽可能大了，后面的差为多少都无所谓了，只要数值不超过 $n$。

所以我们应该构建另一个长度为 $k$ 数列 $B$，存的是 $[n-k+1,n]$。

```cpp
for(int i = 1; i <= k; i++)
    cout << n - k + i << " ";
```

```
5 6 7 8 9
```

我们可以发现，当 $B_i$ 刚刚好大于 $A_i$ 时，我们已经尽可能让特征数大了，所以说，第 $i$ 个数为 $\min(a_i,b_i)$。

---

代码：

```cpp
#include <iostream>
#define min(a,b) (a<b?a:b)
using namespace std;

int t,k,n;

//处理 handle
inline void handle(){
    for(int i = 1; i <= k; i++){
        int ha = 1+i*(i-1)/2;//A_i
        int hb = n-k+i;//B_i
        int mi = min(ha,hb);
        printf("%d ",mi);
    }
}

int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d %d",&k,&n);
		handle();
		printf("\n");
	}
	return 0;
}
```

---

## 作者：zajasi (赞：2)

## 题意
给你一个个数 $k$ 和最大数范围 $n$。请构造 $k$ 个数，使这个序列单调递增且每个数之间的差为不同数的个数尽可能多。
## 解题思路
这道题很明显是一个贪心的思路。首先，我们可以将不同数的个数最大化，然后再慢慢缩小。

不同数的个数最大化是什么意思？就是刚开始构造的差是 $1\ 2\ 3\cdots$ 这样，第一个数是 $1$，然后累加差值。

慢慢缩小是什么意思？就是我们当发现最后可以用来加的位置全部累加 $1$ 还达不到 $k$ 个数，我们就要拿前面贪心的一部分数来换取个数的要求。

于是就有了以下的代码。
## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t;
int n,k;
main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--){
		cin>>k>>n;
		int z=0;
		int c=1;
		int s=1;
		while(s+(k-z-1)<=n&&k>=z+1){
			cout<<s<<" ";
			s+=c++;
			z++;
		}
		c--;
		s-=c;
		for(int i=1;i<=k-z;i++)cout<<++s<<" ";cout<<"\n";
	}
	return 0;
}

```

---

## 作者：ShanCreeperPro (赞：1)

##  CF1772C Different Differences 題解

### 题面

构造一个严格递增的序列使得相邻数之间的集合长度最长。

### 解析

贪心，找规律。

要让不同的值更多并使最大数不超过限制且序列严格递增，理应采用间隔为 $[1,2,3 \cdots ]$ 这样的序列。

但考虑到一个问题，如果按照此规律，可能会在某一个数字即以后超过了题目要求的最大值 $n$，为了不破坏前面不同的间隔，只需要将后面的间隔全部修改为 $1$ 即可。


### 代码

依照贪心模拟即可。


---

## 作者：Patients (赞：1)

### [Different Differences](https://www.luogu.com.cn/problem/CF1772C)

------------

考虑贪心。

由题可知：

![](https://cdn.luogu.com.cn/upload/image_hosting/ircti2e6.png)

这两个式子是相同的。

可以发现：

![](https://cdn.luogu.com.cn/upload/image_hosting/1i9iutef.png)

这明显是最优方案。

问题就在于边界。

假设当前加到了 $ sum $。

那么边界是 $ sum \le n $ 吗？

感觉后面不好处理有没有。

$\because $ 还需要 $ k-cnt $ 个点。

所以要将边界改为 $ sum + k - cnt \le n $。

Q：后面会不会有更优？

A：不会，因为后面加的数一定比 $ 1 $ 大，当前点不行后面就一定不行。

完了。

### Code：

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int T;
int k,n;
void Solve()
{
    cin>>k>>n;
    int sum=1,id=0,cnt=1;
    for(int i=1;;i++)
    {
        sum+=i;
        cnt++;
        if(sum+(k-cnt)>n) {id=i-1;break;}
    }
    sum=1;
    int tmp=0;
    for(int i=1;i<=id;i++)
    {
        cout<<sum<<' ';
        tmp++;
        if(tmp==k) break ;
        sum+=i;
    }
    while(tmp<k)
    {
        cout<<sum<<' ';
        sum++;
        tmp++;
    }
    cout<<'\n';
}
signed main()
{
#ifdef LOCAL
    freopen("1.in","r",stdin);
    freopen("1.out","w",stdout);
#endif
    cin>>T;
    while(T--) Solve();
    return 0;
}
```


---

## 作者：FiraCode (赞：1)

## 思路
可以想到，用贪心的方法，每次相隔 $1,2,3...$。

那么当当前这个数增加了间隔的数之后，剩余的数字加上以前的数字不足 $k$ 的话，就只能把剩下的间隔都变成 $1$。

例如 $n=4,k=3$

1. 第一个数是 `1`。
2. 第二个数，与前一个间隔 $1$,是 `2`。
3. 第三个数，因为 `2+2=4`，所以这个数间隔完之后，就没有数字了（因为要 $\le n$，且要严格递增），所以就变成间隔一个，是 `3`。

## CODE:
```cpp
#include <bits/stdc++.h>
using namespace std;
int T;
int k, n;
int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &k, &n);
		printf("%d ", 1);
		bool flag = false;
		int tempk = k;
		--k;
		int id = 1, last = 1, t = 0;
		for (int i = 1; i < tempk; ++i) {
			int temp = last + id;
			if (flag) {//间隔都是1
				printf("%d ", ++t);
				continue;
			}
			if (temp > n) {//超过了值域
				flag = true;
				t = last + 1;
				printf("%d ", t);
				continue;
			}
			if (n - temp + 1 < k) {//即使其他的间隔只有一也不足k个数，即剩下的所有的都是前一个+1，都还是会在第k个数时超过值域，那么从这个开始，以后就是间隔是1
				flag = true;
				t = last + 1;
				printf("%d ", t);
				continue;
			}
			printf("%d ", temp);//否则输出这个数
			--k;//剩余的数字个数减一
			last = temp;
			id++;//间隔加一
		}
		puts("");
	}
	return 0;
}
```

---

## 作者：loser_seele (赞：1)

首先考虑最优的方案是怎么样的：差分数组一定满足对于一个限定值 $ x $，满足取值一定取满 $ [1,x] $ 中的所有值，其他位置全部填满 $ 1 $ 即可，这样显然是最优的。

于是枚举合法的最大值 $ x $，构造出的数列最大值可以用一个公式计算出来，具体见代码。确定最大值在合法范围内后对于前 $ x $ 个数填入 $ a_{i-1}+i $，否则填入 $ a_{i-1}+1 $ 即可，也就是上述的构造过程。

时间复杂度 $ \mathcal{O}(T \times n^2) $，可以通过。

代码：

```cpp
#import <bits/stdc++.h>
using namespace std;
void solve() 
{
	int k, n;
	cin >> k >> n;
	for (int x = k - 1; x >= 0; x--) 
    {
		int e = (x * (x + 1) / 2);
		if (e + k - x <= n) 
        {
			cout << "1 ";
			int a = 1, b = 1;
			for (int i = 1; i <= x; i++) 
			    cout << a + b << " ", a += b, b++;
			for (int i = x + 2; i <= k; i++) 
			    cout << a + 1 << " ", a++;
			cout << "\n";
			return;
		}
	}
}
int main() 
{
	int T;
	cin >> T;
	while (T--) 
	solve();
}
```


---

## 作者：luqyou (赞：0)

考虑贪心。

想要让差值不同，显然差值序列为 $[1,2,3,\dots]$。

每次取差值时判断一下如果加上下一个差值会不会超过 $n$。

如果会，用差值为 $1$ 的序列填充，直到序列中数的个数为 $k$。

如果不会，加上当前差值再输出即可。

---

## 作者：Wind_Smiled (赞：0)

## 题意

给定 $t$ 组数据，对于每次询问，给出一个严格递增的数字序列长度 $k$ 和一个最大数字 $n$，使相邻两数之差尽可能不相同，输出这个序列。

### 分析

显然的，对于题中要求的“相邻两数之差尽可能不相同”，则需要构造一个“差之差”为 $1$ 的数组。形如：
```
1   2   4   7   11   16
 (1) (2) (3) (4)  (5)
   (1) (1) (1) (1)
```
但是，当我们生成的数组最大值会大于给定的限定值，所以在按位输出数组的时候加一个判断即可，其条件为：当最大值减下一位大于等于剩余个数时，可以继续按照分析输出，否则每次的输出仅增加 $1$。

### 解释

若最大值超出，则后面的两数之差一定等于前面的某一位的差值，所以为了节省数值的占用，每次增加 $1$ 即可满足题中的递增条件。从而压缩后面的数值，使前面的数字可以尽可能大。使得两数之差不同的可能性增大。

### 提示

多测要清空。


------------

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int k,n,a,b;
int main(){
	scanf("%d",&t);
	while(t--){
		a=1;//基础的数字
		b=0;//额外增加的数字
		scanf("%d%d",&k,&n);
		for(int i=1;i<=k;i++){
			if(n-a-b>=k-i){//满足可以继续
				a+=b;//加上差
				b++;//差加一
			}
			else{//否则就只能增加一位
				a++;
			}
			printf("%d ",a);//输出，加空格
		}
		putchar('\n');//下一组数据换行
	}
	return 0;
}
```

---

## 作者：wdgm4 (赞：0)

我又来出~~水~~题解了。

------------

这是一道十分简单的大贪心。我们可以让数组中第一个数为 $1$，第二个数为 $2$，第三个数为 $4$，第四个数为 $7$，每相邻两个数的差都是递增的。但是，我们还需要考虑这么干可能会超出 $m$ 的范围。所以我用一个叫做 `wz` 的变量，来表示前 `wz` 个数按照上面的规律来，剩下的每相邻两个数的差都是 $1$。然后输出即可。

解释如何贪心的说明都在代码的注释里，不懂怎么实现代码的可以去看注释。

## code
```cpp
#include<bits/stdc++.h>
#define XD 114514

using namespace std;
int t,n,m;
int main(){
	cin>>t;
	while(t--){
		scanf("%d%d",&n,&m);
		n--;
		cout<<"1 ";//第一个数直接输出
		int sum=1,num=0,wz=n;
		for(int i=1;i<=n;i++){
			num++;
			sum+=num;
			if(sum>m or n-i+sum>m){//判断如果前i个数都按第一个规律来，剩下的按第二个规律来是否能不超范围
				wz=i-1;//说明前i-1个数用规律一
				break;
			}
		}
		sum=1,num=0;
		for(int i=1;i<=wz;i++){//规律一
			num++;
			sum+=num;
			printf("%d ",sum);
		}
		if(wz!=n){//规律二,wz=n时说明前n个数都用规律一，不用规律二
			for(int i=wz;i<n;i++){
				sum++;
				printf("%d ",sum);
			}
		}
		printf("\n");//最后记得换行
	}
	return 0;
}
```


---

