# Price Maximization

## 题目描述

A batch of $ n $ goods ( $ n $ — an even number) is brought to the store, $ i $ -th of which has weight $ a_i $ . Before selling the goods, they must be packed into packages. After packing, the following will be done:

- There will be $ \frac{n}{2} $ packages, each package contains exactly two goods;
- The weight of the package that contains goods with indices $ i $ and $ j $ ( $ 1 \le i, j \le n $ ) is $ a_i + a_j $ .

With this, the cost of a package of weight $ x $ is always $ \left \lfloor\frac{x}{k}\right\rfloor $ burles (rounded down), where $ k $ — a fixed and given value.

Pack the goods to the packages so that the revenue from their sale is maximized. In other words, make such $ \frac{n}{2} $ pairs of given goods that the sum of the values $ \left \lfloor\frac{x_i}{k} \right \rfloor $ , where $ x_i $ is the weight of the package number $ i $ ( $ 1 \le i \le \frac{n}{2} $ ), is maximal.

For example, let $ n = 6, k = 3 $ , weights of goods $ a = [3, 2, 7, 1, 4, 8] $ . Let's pack them into the following packages.

- In the first package we will put the third and sixth goods. Its weight will be $ a_3 + a_6 = 7 + 8 = 15 $ . The cost of the package will be $ \left \lfloor\frac{15}{3}\right\rfloor = 5 $ burles.
- In the second package put the first and fifth goods, the weight is $ a_1 + a_5 = 3 + 4 = 7 $ . The cost of the package is $ \left \lfloor\frac{7}{3}\right\rfloor = 2 $ burles.
- In the third package put the second and fourth goods, the weight is $ a_2 + a_4 = 2 + 1 = 3 $ . The cost of the package is $ \left \lfloor\frac{3}{3}\right\rfloor = 1 $ burle.

With this packing, the total cost of all packs would be $ 5 + 2 + 1 = 8 $ burles.

## 说明/提示

The first test case is analyzed in the statement.

In the second test case, you can get a total value equal to $ 4 $ if you put the first and second goods in the first package and the third and fourth goods in the second package.

In the third test case, the cost of each item is $ 0 $ , so the total cost will also be $ 0 $ .

## 样例 #1

### 输入

```
6
6 3
3 2 7 1 4 8
4 3
2 1 5 6
4 12
0 0 0 0
2 1
1 1
6 10
2 0 0 5 9 4
6 5
5 3 8 6 3 2```

### 输出

```
8
4
0
2
1
5```

# 题解

## 作者：strange757 (赞：12)

首先看到这道题，第一反应肯定是贪心，但是应该如何贪心呢。

有人可能一开始与我思路相同，看到 $k$  的范围只有1000， 就想到开 $ k $ 个数组，按照对 $ k $ 取余的结果存入数组中，但是这样贪心会非常复杂，代码也会非常难写。于是就需要转变一下思路，既然想到了先按照取余的结果分类，那直接将取余的结果存下来会怎么样呢。

这时候就发现其实可以将 $a$ 序列中的书除 $ k $ 的结果记录到答案中， 将对 $k$ 取模的结果存到另一个数组 $b $ 中, 这时我们只用单独考虑数组 $b$ 。 数组 $b$ 中任意两个数相加都不可能大于 $2k$   。 那么最优的方式就是让尽量多的组合相加大于等于 $k$ , 这时就可以用双指针， 先将数组 $b$ 排序， 两个指针一个从左端点开始， 另一个从右端点开始， 直到找不到为止。

总结一下步骤：

 1. 将 $a $ 数组取余
 2. 对取余后的数组排序
 3. 双指针贪心
 
 
 知道步骤之后代码就非常好写了。
 ```cpp
 #include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define int long long
using namespace std;
const int N = 2e5 + 5;
int t, n, k, a[N], ans;
int b[N];
signed main(){
	scanf("%lld", &t);
	while(t--){
		scanf("%lld%lld", &n, &k);
		ans = 0;
		for(int i = 1; i <= n; i++){
			scanf("%lld", &a[i]);
			ans += a[i]/k;
			b[i] = a[i] % k;
		}
		sort(b + 1, b + 1 + n);
		int l = 1, r = n;
		while(l < r){
			while(b[l] + b[r] < k) l++;
			if(b[l] + b[r] >= k && l < r) ans++, l++, r--;
			else break;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
 
 ```

---

## 作者：fuxuantong123 (赞：6)

# CF1690E Price Maximization 题解
## 思路
因为价值是向下取整，所以会有一部分价值取整损失了，我们要将损失降到最小。

考虑贪心，先将 $a$ 数组模 $k$，商累加，作为最小答案。余数存进 $mod$ 数组，如果 $mod_i + mod_j \geq k$，则对答案贡献 $1$。所以可以每次找到最大的 $mod_i$，去和能匹配的最小的 $mod_j$ 匹配。

先把 $mod$ 排序，保证单调性，再用双指针贪心。（双指针注意细节，记得退循环）。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[200010];
int mod[200010];
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int main(){
	int t;
	t=read();
	while(t--){
		int n,k;
		n=read();
		k=read();
		long long ans=0;
		for(int i=1;i<=n;i++){
			a[i]=read(); 	
			mod[i]=a[i]%k;
			ans+=a[i]/k;
		}
		sort(mod+1,mod+n+1);
		int l=1,r=n;
		while(l<r){
			while(mod[l]+mod[r]<k){
				l++;
			}
			if(l>=r){
				break;
			}
			if(mod[l]+mod[r]>=k){
				l++;
				r--;
				ans++;
			}
			else{
				break;
			}
		}
		printf("%lld\n",ans);	
	}
return 0;
}
```


---

## 作者：mahaoming (赞：2)

# CF1690E

### 思路

可以将 $a_i$ 除 $k$ 的结果记录到答案中，将对 $k$ 取模的结果存回数组 $a$ 中, 我们只用单独考虑数组 $a$ ，那么最优的方式就是让尽量多的组合相加大于等于 $k$ ，这时就可以用双指针，先将数组 $a$ 排序，两个指针分别从左、右端点开始，直到找不到为止。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
inline long long read(){
	long long s=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while('0'<=c&&c<='9')s=s*10+c-'0',c=getchar();
	return s;
}
long long t,n,k,s,a[200005],l,r;
int main(){
	t=read();
	while(t--){
		n=read(),k=read(),s=0,l=1,r=n;
		for(int i=1;i<=n;i++)a[i]=read(),s+=a[i]/k,a[i]=a[i]%k;
		sort(a+1,a+n+1);
		while(l<r){
			while(a[l]+a[r]<k)l++;
			if(l>=r)break;
			if(a[l]+a[r]>=k)s++,l++,r--;
			else break;
		}
		cout<<s<<endl;
	}
	return 0;
}


```


---

## 作者：include_BM (赞：1)

因为 $\left\lfloor \frac{a_i+a_j}{k}\right\rfloor=\left\lfloor\frac{a_i}{k}\right\rfloor+\left\lfloor \frac{a_j}{k}\right\rfloor+\left\lfloor \frac{a_i\bmod k+a_j\bmod k}{k}\right\rfloor$，所以 $\sum \left\lfloor\frac{a_i}{k}\right\rfloor$ 一定在答案中，故可以先算出这一部分，设 $b_i=a_i\bmod k$。

考虑 $b_i$，若 $b_i+b_j\ge k$，会给答案贡献 $1$，那么可以每次找到最大的 $b_i$，让它与能匹配的最小的 $b_j$ 匹配，若选择更大的 $b_j$ 与 $b_i$ 匹配，可能会导致 $<b_i$ 的 $b_k$ 无法匹配，故这种方案是最优的。

先将 $b_i$ 按从小到大排序，初始时 $i=n,j=1$，对于每个 $i$ 找到合适的 $j$，且每个 $j$ 只能匹配一次，当 $i$ 减小时 $j$ 会不断增大。当 $j\ge i$ 时说明不存在还能匹配的 $i,j$，退出循环。

```cpp
n=read(),k=read(),ans=0;
for(int i=1;i<=n;++i) a[i]=read(),ans+=a[i]/k,a[i]%=k;
sort(a+1,a+n+1);
for(int i=n,j=1;i>=1;--i){
    while(j<i&&a[j]+a[i]<k) ++j; if(j>=i) break; ++ans,++j;
}
printf("%lld\n",ans);
```

---

## 作者：mouseboy (赞：0)

## 主要题意：
有 $n$ 个礼物，要两两合并，然后除以 $k$ 最后求和最大。

## 思路：
先加入每个数除以 $k$ 的商（单独组成 $k$ 的个数），然后全部 $ \bmod \ k$ 存入数组，排序，最后双指针一个前一个后求两个余数可以大于等于 $k$ 的两个礼物。

## 代码：
 ```cpp
 #include <bits/stdc++.h>
 using namespace std;
 
 const int Maxn = 2e5 + 5;
 int n, t, a[Maxn], k, l, r;
 long long cnt;
 
 int main()
 {
     ios::sync_with_stdio(0);//其实不用快读
     cin.tie(), cout.tie();//关同步流即可
     cin >> t;
     while (t--)
     {
         cnt = 0;
         cin >> n >> k;
         for (int i = 1; i <= n; i++)
         {
             cin >> a[i];
             cnt += a[i] / k;//求单独组成k的数
             a[i] = a[i] % k;//求余数
         }
         sort(a + 1, a + 1 + n);//排序
         l = 1;
         r = n;
         while (l < r)
         {
             while (a[l] == 0)
             {
                 l++;//0是无论如何也不能组成k的
             }
             while ((a[l] + a[r]) % k == 0 && l < r)//等于时
             {
                 cnt++;
                 l++;
                 r--;
             }
             while (a[l] + a[r] > k && l < r)//大于时（其实可以合并）
             {
                 cnt++;
                 r--;
                 l++;
             }
             while (a[l] + a[r] < k && l < r)//小于
             {
                 l++;
             }
         }
         cout << cnt << "\n";
     }
     return 0;
 }
```

---

## 作者：中缀自动机 (赞：0)

题意：将两个包裹合并，其价值为两数之和除以 $k$（向下取整），求合并所有包裹后得到的最大价值。


------------

分析：先不考虑合并，若一个数 $x$ 大于等于 $k$ ，其对最终答案的贡献至少为 $x/k$。根据这点，可以将输入的数据修改为 $x\bmod k$。因为 $k$ 小于 $1000$，所以可以用桶来储存这些数，并用贪心来合并处理。


------------
代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int sca[200010],b[2000];
int main(){
        ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t,n,k;
	cin>>t;
	while(t--){
		memset(b,0,sizeof(b));
		cin>>n>>k;
		for(int i=1;i<=n;i++) cin>>sca[i];
		long long ans=0;
		for(int i=1;i<=n;i++){
			ans+=sca[i]/k;
			b[sca[i]%k]++;
		}
		int l=1,r=k-1;
		while(l<=r){
			while(b[l]==0&&l<=r) l++;
			while(b[r]==0&&l<=r) r--;
			if(l>r) break;
			if(l+r<k){
				l++;
				continue;
			}
			if(l==r){
				ans+=b[l]/2;
				break;
			}
			int minn=min(b[l],b[r]);
			ans+=minn;
			b[l]-=minn;
			b[r]-=minn;
		}
		cout<<ans<<endl;
	}
    return 0;
}
```


---

## 作者：Xu_brezza (赞：0)

来水一发题解~

## 题意：
你有 $n$ 个数，其中 $n$ 为偶数，分成 $n\div 2$ 组数，对于每一组，它的价值是这两个数的加和除以给定常数 $k$ 并向下取整，也就是 $ \left \lfloor \frac{a[i]+a[j]}{k} \right \rfloor $，求出最大贡献和。

## 分析
这题关键在于向下取整，这会吃掉很多贡献，所以我们考虑让取整对结果的影响最小，那么余数就呼之欲出了。

首先一个小贪心，将所有数字按照升序排序，便于我们在做除法取整时尽可能得到大的贡献。

然后我们考虑按余数将这些数分类，对于每一类，我们从后面开始取，选择大的，然后根据当前这一类对应的余数假设为 $i$，那么我们最好的选择肯定是 $d=(k-i)\mod{i}$，因为这时候我们取出两个数字加和，根据余数的结合律，余数为 $0$，也就是整除，最为划算，如果 $d$ 对应的集合为空，那么继续自增寻找尽可能区别不大的余数，减少损失，直到找到非空集合，也从后面取，然后统计答案即可。

[代码在这~](https://www.luogu.com.cn/paste/iszrk6et)

---

