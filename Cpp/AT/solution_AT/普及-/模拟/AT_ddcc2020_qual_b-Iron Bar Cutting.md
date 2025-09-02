# Iron Bar Cutting

## 题目描述

[problemUrl]: https://atcoder.jp/contests/ddcc2020-qual/tasks/ddcc2020_qual_b

DISCO 社の高橋君の前に，$ 1 $ 本の鉄の棒が置かれています．  
 この棒は，$ N-1 $ 個の切れ目によって $ N $ 個の区間に分かれています．左から $ i $ 個目の区間の長さは $ A_i $ ミリメートルです．

高橋君は，切れ目を一つ選んでそこで棒を切り，同じ長さの棒を $ 2 $ 本作ることを考えました．しかし，今の状態では，どの切れ目を選んでも $ 2 $ 本の棒を同じ長さにすることができないかもしれません．  
 そこで，彼は棒を切る**前に**，以下の操作を何回か行うことにしました．

- 棒の区間のうち $ 1 $ つを選び，膨張させ，長さを $ 1 $ ミリメートル増やす．この操作を $ 1 $ 回行うのに $ 1 $ 円かかる．
- 棒の区間のうち長さが $ 2 $ ミリメートル以上のもの $ 1 $ つを選び，収縮させ，長さを $ 1 $ ミリメートル減らす．この操作を $ 1 $ 回行うのに $ 1 $ 円かかる．

彼が棒を $ 2 $ 等分するために必要な最小の金額は何円か，求めてください．

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 200000 $
- $ 1\ \leq\ A_i\ \leq\ 2020202020 $
- $ N,\ A_i $ は整数

### Sample Explanation 1

最初，棒の各区間の長さは $ [2,\ 4,\ 3] $ (ミリメートル) です．高橋君は，以下の操作を行うことによって，$ 3 $ 円で棒を $ 2 $ 等分できます． - 左から $ 2 $ 番目の区間を収縮させる．各区間の長さは $ [2,\ 3,\ 3] $ となる． - 左から $ 1 $ 番目の区間を収縮させる．各区間の長さは $ [1,\ 3,\ 3] $ となる． - 左から $ 2 $ 番目の区間を収縮させる．各区間の長さは $ [1,\ 2,\ 3] $ となる．左から $ 2 $ 個目の切れ目で棒を切ると，長さ $ 3 $ の棒が $ 2 $ 本できる．

## 样例 #1

### 输入

```
3
2 4 3```

### 输出

```
3```

## 样例 #2

### 输入

```
12
100 104 102 105 103 103 101 105 104 102 104 101```

### 输出

```
0```

# 题解

## 作者：yydfj (赞：7)

**这是本蒟蒻第三次写的题解，如有错误点请好心指出！**

## 问题简述

__这道题我们可以换另一种思路去看待它，就容易理解了：__

将这些铁棒分成第一部分和第二部分这两部分，求出第一部分之和与第二部分之和之间最小的差。

## 解法综述

设分割的位置为 $i$，铁棒长度为 $a_i$。

就可以清楚的知道金币的花费为 $∣(a_1+a_2+a_3+...+a_i)-(a_i+a_i$ $_+$ $_1$ $+a_i$ $_+$ $_2$ $+...+a_n)∣$ ，而金币花费的数量就取决于分割的位置 $i$。

我们先做预处理前缀和，让 $a_i+=a_i$ $_-$ $_1$，之后让 $i$ 从 $1$ 到 $n$ 遍历，求出$∣(a_i-(a_n-a_i)∣$ 的最小值。

## 代码描述
```cpp
#include<cmath>
#include<iostream>
using namespace std;
long long n,a[200010],ans=1e18;//答案初始化，越大越好 
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],a[i]+=a[i-1];//做预处理前缀和
	for(int i=1;i<=n;i++) ans=min(ans,abs(a[i]-(a[n]-a[i])));//遍历位置i，求出金币的最小值 
	cout<<ans;
	return 0;
}
```

---

## 作者：zct_sky (赞：2)

### 题意：
将铁棒分成两组，求出两组长度和之差最小是多少。
### 思路：
先求出前缀和，之后暴力枚举出分组的位置，并求出此时两组长度和之差，之后与  $ans$ 比大小，如果比 $ans$ 小就存入 $ans$ ，最后输出 $ans$ 。
### Code:
```c++
#include<bits/stdc++.h>
#define ll long long
#define un unsigned
using namespace std;   
inline int read(){//快读 
	int x=0,y=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')y=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x*y;
}      
inline void write(int x){//快输 
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10+48);
	return;
}        
ll n,a[100010];
ll ans=LLONG_MAX;
int main(){
	n=read();//输入 
	for(int i=1;i<=n;i++) a[i]=read()+a[i-1];//求前缀和 
	for(int i=1;i<=n;i++) ans=min(ans,abs(a[i]-(a[n]-a[i])));//暴力枚举，求出两组最小的长度和之差
	write(ans);//输出 
	return 0;
}

```

---

## 作者：fanersaiwenxue (赞：2)

## Describe

将 $ n $ 个铁棒分成两组 , 求第一组和第二组长度差的最小值 

## Idea

连续的铁棒分成两组 , 运用前缀和求出前 $ n $ 个的数的和 , 再从一开始枚举求出最小值即可 。

## Working

把这 $ n $ 个铁棒分成两个序列 , 使它们两个的差值最小 。

前缀和 $ + $ 枚举求最小值 ( 记得开 $ long long $ ) 。

先假设铁棒分割的位置为 $ i $ 那么花费的金币数就为 $ ( a1 + a2 + ... + ai ) - ( ai + ... + an ) $
既然这样就先用前缀和 $ a[i]+=a[i-1] $ , 再从 $ 1 $ 枚举到 $ n $ , 再记录下最小值即可 。
### 芝士点

CSDN博客自行食用 [前缀和](https://blog.csdn.net/weixin_45629285/article/details/111146240?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522163201730916780274114492%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=163201730916780274114492&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_positive~default-1-111146240.pc_search_result_control_group&utm_term=%E5%89%8D%E7%BC%80%E5%92%8C&spm=1018.2226.3001.4187)

就是假设 $ n $ 个数 , 让你求前 $ n $ 个数的和 ( 蒟蒻的个人见解如错及时指出 )

```cpp
int sum[100],a[100];
int n;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		sum[i]=sum[i-1]+a[i];
	}
}
```

大概就是这样吧（雾

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[2000005],ans=0;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];	
		a[i]=a[i-1]+a[i]; // 前缀和
	}	
	ans=a[n]; // 先去极劣值 或者赋极大值也可以 ans=0x7ffffffff
	for(int i=1;i<=n;i++)
	{
		ans=min(ans,abs(a[i]-(a[n]-a[i]))); // 差值为现差值-（总值-现差值）
	}
	cout<<ans<<endl; // 输出最小花费
	return 0;
}
```

✿✿ヽ(°▽°)ノ✿

---

## 作者：cqbztz2 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT5666)

# 前言

题意有误，这两组铁棒应该是连续的，差点让本蒟蒻做成 $ 0/1 $ 背包……

# 思路

题目可以转化为分成两组，使他们的长度之差最小。

因为铁棒必须连续的，所以第一组铁棒的开始位置必定是 1，而结尾位置并不知道，就需要进行枚举，求最小值。而要快速求前 n 个数的和，就需要用到前缀和优化。

# 代码

```cpp
  #include <bits/stdc++.h>
  using namespace std;
  long long n,a[200005],sum[200005],minn=0x3f3f3f3f3f3f;//给答案赋极大值
  int main(){
      cin>>n;
      for(int i=1;i<=n;i++){
          cin>>a[i];
          sum[i]=sum[i-1]+a[i];//前缀和
      }
      for(int i=1;i<=n;i++){
          minn=min(minn,abs(sum[i]-(sum[n]-sum[i])));//差值为当前值-（总和-当前值）
      }
      cout<<minn;//输出答案
      return 0;
  }
```


---

## 作者：hellhell (赞：0)

### 思路分析

因为要求铁棒连续，所以我们可以从 $1$ 到 $n$ 枚举每一个铁棒。令 $sum[i]$ 表示从前 $i$ 个铁棒的长度之和。

那么从第 $i$ 个铁棒断开，分成两组需要花费的金币是 $∣sum[i]-(sum[n]-sum[i])∣$。

从 $1$ 到 $n$ 枚举，记录答案即可。

初始化时，答案的最大值应该为一根铁棒的长度，即 $2020202020$。

### 代码实现

```cpp
#include<bits/stdc++.h>
#define int long long

using namespace std;

int read(){
    int f=1;
    int res=0;
    char ch=getchar();
    while(ch<'0' || ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9'){
        res=res*10+ch-'0';
        ch=getchar();
    }
    return res*f;
}

const int maxn=2e5+5;

int n;
int a[maxn],sum[maxn];
int ans=2020202020ll;

signed main(){
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		sum[i]=sum[i-1]+a[i];
	}
	for(int i=1;i<=n;i++){
		ans=min(ans,abs(sum[i]-(sum[n]-sum[i])));
	}
	printf("%lld\n",ans);
    return 0;
}
```



---

## 作者：jiang_cheng (赞：0)

## 解题思路：
相当于分割成两个非空序列，使得两个序列的差最小，而答案就是这两个序列的差。于是可以借助前缀和，从后往前枚举每两个序列的差即可。（管理员大大最帅了！！！）
## 附上代码：
```cpp
#include <cstring>
#include <iostream>

using namespace std;

const int kMaxN = 2e5 + 1;

int n;
long long a[kMaxN], ans;

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    a[i] += a[i - 1];  //预处理前缀和
  }
  ans = a[n];  //给答案附上极劣值
  for (int i = n; i >= 1; i--) {
    ans = min(ans, abs(a[n] - a[i - 1] * 2));
    //更新答案，a[n] - a[i - 1]是第二个序列的值，a[i - 1]是第一个序列的值，两个序列的差就是abs(a[n] - a[i - 1] * 2)
  }
  cout << ans;  //输出
  return 0;
}
```

---

## 作者：小小小朋友 (赞：0)

### 题意

这个题的翻译有点容易误导大家，实际上这里的铁棒分组是要连续的。

### 思路

很简单的思路~适合萌新

考虑分割的位置，假设分割的位置为$i$，铁棒长度为$a_i$

那么很显然需要$\vert (a_1+a_2...+a_i)-(a_i+a_{i+1}...+a_n) \vert$块钱

于是线性枚举分割点，计算两边差值，取最小值输出即可。

此外记得开long long

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[200005],sum=0,ans,tmp=0;
int main() {
	cin>>n; 
	for(int i=1;i<=n;i++){
		cin>>a[i];
		sum+=a[i];//sum表示所有数的总和
	}
    ans=sum;
	for(int i=1;i<=n;i++){
		tmp+=a[i];//tmp表示当前累加到的和
		ans=min(ans,abs(tmp-(sum-tmp)));
	}
	cout<<ans;
	return 0;
}
```

---

