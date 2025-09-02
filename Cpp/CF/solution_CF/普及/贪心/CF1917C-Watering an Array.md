# Watering an Array

## 题目描述

You have an array of integers $ a_1, a_2, \ldots, a_n $ of length $ n $ . On the $ i $ -th of the next $ d $ days you are going to do exactly one of the following two actions:

- Add $ 1 $ to each of the first $ b_i $ elements of the array $ a $ (i.e., set $ a_j := a_j + 1 $ for each $ 1 \le j \le b_i $ ).
- Count the elements which are equal to their position (i.e., the $ a_j = j $ ). Denote the number of such elements as $ c $ . Then, you add $ c $ to your score, and reset the entire array $ a $ to a $ 0 $ -array of length $ n $ (i.e., set $ [a_1, a_2, \ldots, a_n] := [0, 0, \ldots, 0] $ ).

Your score is equal to $ 0 $ in the beginning. Note that on each day you should perform exactly one of the actions above: you cannot skip a day or perform both actions on the same day.

What is the maximum score you can achieve at the end?

Since $ d $ can be quite large, the sequence $ b $ is given to you in the compressed format:

- You are given a sequence of integers $ v_1, v_2, \ldots, v_k $ . The sequence $ b $ is a concatenation of infinitely many copies of $ v $ : $ b = [v_1, v_2, \ldots, v_k, v_1, v_2, \ldots, v_k, \ldots] $ .

## 说明/提示

In the first test case, the sequence $ b $ is equal to $ [1, 3, 2, 3, 1, 3, 2, 3, \ldots] $ and one of the optimal solutions for this case is as follows:

- Perform the operation of the second type on the $ 1 $ -st day: your score increases by $ 3 $ and array $ a $ becomes equal to $ [0, 0, 0] $ .
- Perform the operation of the first type on the $ 2 $ -nd day: array $ a $ becomes equal to $ [1, 1, 1] $ .
- Perform the operation of the first type on the $ 3 $ -rd day: array $ a $ becomes equal to $ [2, 2, 1] $ .
- Perform the operation of the second type on the $ 4 $ -th day: your score increases by $ 1 $ and array $ a $ becomes equal to $ [0, 0, 0] $ .

It can be shown that it is impossible to score more than $ 4 $ , so the answer is $ 4 $ .

In the second test case, the sequence $ b $ is equal to $ [6, 6, 6, 6, \ldots] $ . One of the ways to score $ 3 $ is to perform operations of the first type on the $ 1 $ -st and the $ 3 $ -rd days and to perform an operation of the second type on the $ 2 $ -nd day.

## 样例 #1

### 输入

```
5
3 4 4
1 2 3
1 3 2 3
6 2 3
6 1 2 4 1 5
6 6
5 1 1
0 5 0 5 0
5
1 1 1
1
1
3 4 6
1 2 3
1 3 2 3```

### 输出

```
4
3
0
1
5```

# 题解

## 作者：Phartial (赞：13)

容易发现，如果 $a$ 全 $0$，则无论进行多少次操作一，$a$ 始终都是**单调不增**的。若有 $a_i=i$，则对所有 $j<i$，必然有 $a_j\ge a_i=i>j$；同理，对 $j>i$，必然有 $a_j\le a_i=i<j$。

由此我们可得，从全 $0$ 开始无论进行多少次操作 $1$，最多只有一个 $i$ 能满足 $a_i=i$。

而注意到从全 $0$ 开始进行一次操作 $1$ 后，必然有 $a_1=1$，由于之后不会有更多的 $i$ 满足 $a_i=i$，为了节省操作次数，我们必然会紧接着一个操作二并产生 $1$ 的贡献。

由此我们可以得到当 $a$ 全 $0$ 时的最优策略：操作一和操作二交替执行，若有 $d$ 次操作次数，答案即为 $\lfloor\dfrac{d}{2}\rfloor$。

于是唯一的变数就是 $a$ 的初始值了，进行若干次操作 $1$ 后，确实会有 $>1$ 个 $i$ 满足 $a_i=i$，但显然不会有超过 $n$ 个 $i$ 满足 $a_i=i$。

考虑在一开始就用一次操作二清空 $a$，并在之后采用最佳策略，则在第 $2n+1$ 次操作（该操作是操作二）后，我们也能产生 $n$ 的贡献。

因此，初始进行的操作 $1$ 的数量不能超过 $2n$（否则反而不如上述策略），枚举初始进行的操作 $1$ 数量即可。时间复杂度 $\mathcal{O}(n^2)$。

```cpp
#include <iostream>

using namespace std;

const int kN = 2001, kK = 1e5 + 1;

int tt, n, k, d, a[kN], b[kK], ans;

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  for (cin >> tt; tt--; ) {
    cin >> n >> k >> d;
    for (int i = 1; i <= n; ++i) {
      cin >> a[i];
    }
    for (int i = 1; i <= k; ++i) {
      cin >> b[i];
    }
    ans = 0;
    for (int i = 0; i <= min(d - 1, 2 * n); ++i) {
      int c = 0;
      for (int j = 1; j <= n; ++j) {
        c += (a[j] == j);
      }
      ans = max(ans, c + (d - i - 1) / 2);
      for (int j = 1; j <= b[i % k + 1]; ++j) {
        ++a[j];
      }
    }
    cout << ans << '\n';
  }
  return 0;
}
```

---

## 作者：FiraCode (赞：2)

## 思路:
首先假如数组开始全为 $0$ 怎么做。

那么显然是每进行一次操作 $1$，就立马进行操作 $2$。因为若再进行一次，那么相等的贡献最多不变，因为是对前缀加，第一次是 $1$ 满足，而第二次只有 $2$ 满足或者没有，后面同理。

然后看不全为 $0$ 怎么做。

我们发现 $n$ 比较小，考虑暴力做 $2n$ 轮，然后对于每一轮都计算贡献。也就是对于 $i(0 \le i \le 2n)$ 来说，我们就是求做 $i$ 的贡献加上剩余轮数按照刚才的策略的贡献。

而为什么做 $2n$ 轮？是因为当执行 $2n$ 轮时，你可以直接按照上述 $2$ 轮一个贡献，就可以到 $n$ 的贡献，而若一直执行的话，最多也就所有的数字都一样，最多也就是 $n$，所以没必要在往后枚举了。

当然做的轮数还要 $<d$。

时间复杂度 $\mathcal{O(Tn^2)}$。

## Code:
```cpp
#include <bits/stdc++.h>

using namespace std;

int T;
int n, k, d;
int a[2010], v[100010];
int cnt[4010];

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d", &n, &k, &d);
		cnt[0] = 0;
		for (int i = 1; i <= n; ++i) scanf("%d", &a[i]), cnt[0] += a[i] == i;
		for (int i = 1; i <= k; ++i) scanf("%d", &v[i]);
		for (int i = 1; i <= 2 * n && i < d; ++i) {
			cnt[i] = 0;
			for (int j = 1; j <= v[(i - 1) % k + 1]; ++j) a[j]++;
			for (int j = 1; j <= n; ++j) cnt[i] += a[j] == j;
		}
		int ans = 0;
		for (int i = 0; i <= 2 * n && i < d; ++i) {
			// cout << cnt[i] << endl;
			ans = max(ans, cnt[i] + (d - i - 1) / 2);
		}
		printf("%d\n", ans);
	}
	return 0;
}
```

---

## 作者：Tang_poetry_syndrome (赞：1)

## [CF1917C] Watering an Array 
比较简单的贪心。
### 思路
首先 $a$ 序列全为 $0$。进行操作一时，因为增加区间 $[1,j]$ 可以让区间 $[1,i]$ 同时增长 $(i\le j)$，所以 $a_j\le a_i(j\ge i)$，即 $a$ 序列一定是 **单调不升的**，可以进一步推出除了在原 $a$ 序列上操作，**最多只有一个元素满足** $a_i=i$。那么在初始 $a$ 序列被结算后，得到的分数为 $\lfloor \frac{x}{2} \rfloor$，$x$ 为操作的步数（操作一、操作二交替，取 $a_1$ 得分）。  
然后考虑 $a$ 原序列，考虑暴力枚举操作一，设原序列花 $y$ 步得到 $s$ 分，最终分数为 $cnt+\lfloor \frac{d-y}{2}\rfloor$ 。  
再寻找枚举区间，因为原序列最多可得 $n$ 分，然而根据先清零，在加一+清零的策略，$2\times n+1$ 的步数可达到这样的要求，因此枚举 $[1,2n]$ 的操作数即可。  
代码就不放了。

---

## 作者：XYQ_102 (赞：0)

## 思路
如果数组 $a$ 开始全部为 $0$，那么最优策略就是操作 $1,2$ 轮流进行，可以获得 $\lfloor\frac{d}{2}\rfloor$ 点得分（注意：开始时若 $a_1 \ge 1$，则需要使用一次操作 $2$ 将 $a_1$ 修改为 $0$，此时得分为 $\lfloor\frac{d - 1}{2}\rfloor +$ 开始时数组元素可以产生的得分。

而由于初始的数组是包含初始数字的，且长度为 $n$ 的数组最多可以产生 $n$ 点得分，因此，只需要在 $2 \times n - 1$ 的操作次数内均有可能超过循环操作获取的 $n$ 点固定得分。

枚举第一次进行操作 $2$ 前会进行多少次操作 $1$，每次遍历数组统计得分，剩余的操作次数使用最优策略进行。记录过程中最大的得分即可。

### 坑点
既然获取的长度为 $n$ 的数字最高可以产生 $n$ 点得分，那么只枚举 $n$ 次操作是否就够了？

#### 反例

原数组为 $2,1,2,\cdots,n-1$，给出的b数组为 $1, 1,\cdots,1,n$，其中  $b_i = n$ 前有 $(2 \times n)-4$ 个 $1$，此时 $d = 2 \times n$。

可以发现，枚举 $0 \sim n$ 次操作 $1$，均无法产生额外得分，此时获得的最高总分为 $\lfloor \frac{d - 1}{2} \rfloor = n - 1$，而依次使用 $(2 \times n) - 3$ 次操作 $1$，再进行操作 $2$，可以获得 $n - 1$ 点得分，此时还剩下两次操作，还可以继续一次最优策略，最后得分为 $n$。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[300500],b[300500];
int main() 
{
    int T;
    cin>>T;
    while(T--)
    {
    	long long n,k,d;
	    cin>>n>>k>>d;
	    long long ans=0;
	    for(int i=1;i<=n;i++) 
			cin>>a[i];
	    for(int i=0;i<k;i++) 
			cin>>b[i];
	    for(int i=0;i<=2*n && i<d;i++) 
		{
	        long long cnt=0;
	        for(int j=1;j<=n;j++) 
				if(a[j]==j) 
					cnt++;
	        ans=max(ans,cnt+(d -i-1)/2);
	        for(int j=1;j<=b[i % k];j++) 
			{
	            if(a[j]==j) 
					cnt--;
	            a[j]++;
	            if(a[j]==j) 
					cnt++;
	        }
	    }
	    cout<<ans<<"\n";
	}
    return 0;
}
```

---

## 作者：UncleSam_Died (赞：0)

### 解题思路
观察可以发现，我们在清零后进行第一种操作，得到的序列是单调不下降的，也就是说，在清零后，我们每两次操作最多可以获得 $1$ 分，设在 $q$ 次操作后清零，那么我们后面的操作最多可以得 $\displaystyle \frac{d-q}{2}$ 分。考虑清零前如何得分最大，观察数据范围可以发现，暴力枚举即可通过，我们考虑枚举清零的日期，每次更新 $a$ 中的元素大小，设此时有 $cnt$ 个 $a_i$ 满足 $a_i=i$，那么当前可得的分即为 $\displaystyle cnt+\frac{d-q}{2}$，和答案 $ans$ 取最大值即可。
### 注意事项
可能出现将 $v$ 遍历一次无法得到最优解的情况，因此，我们在枚举的时候应将循环条件设置为 $i\le \min(\max(10^5,\mid v \mid),d-1)$，且在进行操作前应计算原本数组的得分。

### AC 代码
```cpp
#include<iostream>
#include<math.h>
#include<time.h>
#include<stdio.h>
#include<algorithm>
#define ll long long
#define int ll
#define N 2005
#define M 100005
int n,k,d,a[N],v[M];
inline void work(){
    scanf("%lld%lld%lld",&n,&k,&d);
    for(register int i=1;i<=n;++i)
        scanf("%lld",&a[i]);
    for(register int i=1;i<=k;++i)
        scanf("%lld",&v[i]);
    int ans,cnt=0;
    for(register int i=1;i<=n;++i)
        if(a[i]==i) ++cnt;
    ans=cnt+((d-1)>>1);
    for(register int i=1;i<=std::min(std::max(k,100000ll),d-1ll);++i){
        for(register int j=1;j<=v[i%k==0?k:(i%k)];++j)
            ++a[j];cnt=0;
        for(register int j=1;j<=n;++j){
            if(a[j]==j) ++cnt;
        }
        int now=cnt+((d-i-1)>>1);
        ans=std::max(ans,now);
    }printf("%lld\n",ans);
}signed main(){
    int T;scanf("%lld",&T);
    while(T--) work();
}
```

---

## 作者：technopolis_2085 (赞：0)

分析：

首先证明每次进行操作二 时，$c$ 最大为 $1$。

证：$a$ 数组为一个单调不增的序列。所以 $a_{i-1}≥a_i≥a_{i+1}$。

假设此时 $a_i=i$。那么 $a_{i-1}≥i>i-1$，$a_{i+1}≤i<i+1$。故 $a_{i-1}$ 和 $a_{i+1}$ 都不满足条件。 

所以 $c$ 最大为 $1$。

首先考虑如果数组全为 $0$ 时怎么做。

那么最优的做法为：使用一次操作一，然后使用一次操作二。

这样，当使用操作一后，数组会变成 $[1,1,1,...,1,0,0...0]$。此时，我们发现 $a_1=1$。

有根据前面证的结论，发现这是最优情况。所以进行操作二。答案加 $1$，数组清零。

所以问题变成了如何处理初始值。

我们发现，后面每操作两次就给答案贡献了 $1$。假设初始值中有很长一段连续的数，使得做完若干次操作一后的 $c$ 很大。那么，此时 $c$ 最大为 $n$。那么对应着，我们最多操作 $2n$ 次，就能得到最长连续的数。

所以，我们只需要在刚开始时暴力操作 $2n$ 次，后面就先操作一后操作二。

时间复杂度 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long

const int maxn=2010,maxk=1e5+10;
int a[maxn],b[maxk];
int n,k,d;

int Get(){
	int ans=0;
	for (int i=1;i<=n;i++){
		if (a[i]==i) ans++;
	}
	return ans;
}

signed main(){
	int T;
	scanf("%lld",&T);
	
	while (T--){
		scanf("%lld%lld%lld",&n,&k,&d);
		
		for (int i=1;i<=n;i++) scanf("%lld",&a[i]);
		for (int i=1;i<=k;i++) scanf("%lld",&b[i]);
		
		int ans=0;
		int flag=0;
		for (int i=1;i<=n;i++){
			if (a[i]){
				flag=1; break;
			} 
		}
		
		if (flag==0) ans=max(ans,d/2);
		ans=max(ans,Get()+(d-1)/2);
		int remain=d;
		for (int step=1;step<=min(d-1,4*n);step++){
			int pos=step%k;
			if (pos==0) pos=k;
			remain--;
			for (int j=1;j<=b[pos];j++) a[j]++;
		//	printf("remain=%lld, %lld\n",remain,Get());
			
			ans=max(ans,Get()+(remain-1)/2); 
		}
		
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：1025xp (赞：0)

这题主要是两个点：

- 多少次操作使得数组提供的权值最大?

- 操作完数组后每**两**次操作提供 $1$ 权值。

而数组最多提供的权值是 $n$，超过 $2 \times n$ 次操作之后直接不考虑利用数组提供权值了。


直接两重 for 循环枚举，时间复杂度为 $O(n^2)$。

第一重 for 循环枚举到 $\min(d,2\times n)$。

第二重进行判断和操作，注意：得先判断再操作。

最后记得用 $idx$ 维护一下 $k$ 数组。


主要代码：
```cpp
void solve()
{
    cin>>n>>k>>d;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=0;i<k;i++) cin>>b[i];
    
    int ans=0,idx=0;
    for(int i=1;i<=min(d,2*n);i++){
    	int t=(d-i)/2,sum=0;
    	for(int j=1;j<=n;j++) if(a[j]==j) sum++;
    	ans=max(ans,sum+t);
    	for(int j=1;j<=b[idx];j++) a[j]++;
    	idx=(idx+1)%k;
    }
    cout<<ans<<'\n';
}
```

---

## 作者：翼德天尊 (赞：0)

考虑如果初始序列全 $0$，由于每次都是前缀加，我们一定可以通过 $1,2$ 操作交替进行来达到最优解。

那么对于初始序列不为 $0$ 的情况，显然我们最多在第一次 $2$ 操作之前使用 $2n$ 次 $1$ 操作。于是我们可以枚举初始序列使用了几次 $1$ 操作，贪心取最大即可。时间复杂度 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e5+5;
int n,k,d,a[N],v[N];
ll read(){
	ll w=0,f=1;
	char c=getchar();
	while (c>'9'||c<'0'){
		if (c=='-') f=-1;
		c=getchar();
	}
	while (c>='0'&&c<='9'){
		w=(w<<3)+(w<<1)+(c^48);
		c=getchar();
	}
	return w*f;
} 
int main(){
	// freopen("in.in","r",stdin);
	int t=read();
	while (t--){
		n=read(),k=read(),d=read();
		for (int i=1;i<=n;i++) a[i]=read();
		for (int i=1;i<=k;i++) v[i]=read();
		int ans=0;
		for (int i=1;i<=min(2*n+1,d);i++){
			int num=0;
			for (int j=1;j<=n;j++) num+=(a[j]==j);
			ans=max(ans,num+(d-i)/2);
			for (int j=1;j<=v[(i-1)%k+1];j++) a[j]++;
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

