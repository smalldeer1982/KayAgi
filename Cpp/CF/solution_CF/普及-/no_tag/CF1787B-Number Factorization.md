# Number Factorization

## 题目描述

Given an integer $ n $ .

Consider all pairs of integer arrays $ a $ and $ p $ of the same length such that $ n = \prod a_i^{p_i} $ (i.e. $ a_1^{p_1}\cdot a_2^{p_2}\cdot\ldots $ ) ( $ a_i>1;p_i>0 $ ) and $ a_i $ is the product of some (possibly one) distinct prime numbers.

For example, for $ n = 28 = 2^2\cdot 7^1 = 4^1 \cdot 7^1 $ the array pair $ a = [2, 7] $ , $ p = [2, 1] $ is correct, but the pair of arrays $ a = [4, 7] $ , $ p = [1, 1] $ is not, because $ 4=2^2 $ is a product of non-distinct prime numbers.

Your task is to find the maximum value of $ \sum a_i \cdot p_i $ (i.e. $ a_1\cdot p_1 + a_2\cdot p_2 + \ldots $ ) over all possible pairs of arrays $ a $ and $ p $ . Note that you do not need to minimize or maximize the length of the arrays.

## 说明/提示

In the first test case, $ 100 = 10^2 $ so that $ a = [10] $ , $ p = [2] $ when $ \sum a_i \cdot p_i $ hits the maximum value $ 10\cdot 2 = 20 $ . Also, $ a = [100] $ , $ p = [1] $ does not work since $ 100 $ is not made of distinct prime factors.

In the second test case, we can consider $ 10 $ as $ 10^1 $ , so $ a = [10] $ , $ p = [1] $ . Notice that when $ 10 = 2^1\cdot 5^1 $ , $ \sum a_i \cdot p_i = 7 $ .

## 样例 #1

### 输入

```
7
100
10
864
130056192
1000000000
2
999999018```

### 输出

```
20
10
22
118
90
2
333333009```

# 题解

## 作者：ikunTLE (赞：12)

[题目传送门](https://www.luogu.com.cn/problem/CF1787B)

### 题目大意

给出一个正整数 $n$，将 $n$ 分解成其质因数不能重复的因数的幂的乘积，使因数与它们的幂指数的乘积之和最大。

### 思路

将 $n$ 分解质因数，存储在序列 $A$，每一次从剩下的质因子里各取一个数相乘得到新的数，并将其加和。

举例说明：$864=2^5\times3^3$，那么 $A=\{2,2,2,2,2,3,3,3\}$。前三次需将所有的质因子全部相乘，即各取一个 $2$ 和一个 $3$，第四次取两个 $2$，最终答案为 $6\times3+2\times2=22$。同理，$130056192=2^{15}\times3^4\times7^2=42^2\times6^2\times2^{11}$，答案为 $42\times2+6\times2+2\times11=118$。

---

## 作者：D23lhc (赞：8)

## 题目大意:
给出一整数 $n$，将这个数分解成因数的幂的乘积，且这些因数的质因数不能重复，求最大的这些因数与他们的幂指数的乘积之和最大是多少。$2\le n\le 10^9$。

## 思路： 
因为这些因数的质因数不能重复，所以要想最大，只能将不同的因数乘在一起变成更大的因数例如 $864= 2^5\times 3^3 = 6^3\times 2^2$，因为两个数相乘肯定比相加大，$2+3 < 2\times 3$，加上幂指数大小关系不变。

## 代码：
```
#include<bits/stdc++.h>
using namespace std;
pair<int, int>a[100000];
int tot = 0;
int x = 1;
void cal(int n)//分解质因数        
{
	for (i = 2; i*i <= n; i++)
	{//只需遍历到sqrt(n)
		bool flag = 0;//当前数字是否是质因数
		int cnt = 0;//记录指数
		while (n % i == 0)
		{//n除尽这个因数
			cnt++;
			n /= i;
			flag = 1;
		}
		if (flag)
		{
			x *= i;//记录所有不同的质因数的乘积
			a[++tot] = make_pair(cnt, i);//记录底数和指数
		}
		if (n == 1)
			return;
	}
	if (n > 1)
	{//还有大于sqrt(n)的因数
		a[++tot] = make_pair(1, n);
		x *= n;
	}
}
int main()
{
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);
	int t;
	cin >> t;
	while (t--)
	{
		x = 1;
		int n;
		cin >> n;
		tot = 0;
		cal(n);
		sort(a + 1, a + 1 + tot);//按指数从小到大排序
		int ans = 0;//记录答案
		int mi = 0;//记录当前已选择的指数
		for (int i = 1; i <= tot; i++)
		{
			ans += x * (a[i].first - mi);
			mi = a[i].first;//更新选择的指数
			x /= a[i].second;//所有数的乘积减小
			if (x == 1)
				break;
		}
		cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：__bjxx0201__ (赞：2)

## 题目大意

给定一个 $n$，将 $n$ 分解成**不同的**质因数的幂的乘积。如 $36=2^2\times 3^2$ 就是一个模拟操作。

求出最大的因数和数的乘积之和最大是多少。

## 思路

[题目传送门](https://www.luogu.com.cn/problem/CF1787B)

首先暴力找出所有不大于 $n$ 的为 $n$ 的质因数，表示成为指数的方式，先将 $n$ 分解成为两个差最小的数字相成的形式，然后再将这两个数字分解成为质数的指数，这样简单点。如 $42=6\times 7=3^2\times 7^1$。

之后我们按照题意操作，要求出最大的乘积之和，可以对这堆质因数分成若干组，然后每一组找出因数和指数之积，选取最大值即可。

最后注意一下：$2\le n\le 10^9$。

---

## 作者：gaohaoyuan (赞：2)

## 题意概括
给出一个数 $n$（$n$ 是正整数），将 $n$ 分解成因数的幂的乘积（因数的质因数不能重复）求因数与它们的幂指数的乘积之和的最大值。
## 解题步骤
### 1.质因数分解
将 $n$ 分解为所有质因数的乘积。
### 2.组合优化
尝试不同的组合，将质因数分组，并计算每组中因数与幂指数的乘积之和，从中找到一种分组方式，使得这个总和最大化。
### 3.敲代码
使用编程来实现上述步骤。
## 关键代码

```cpp
//对于每一组数据
scanf("%d",&n);
fj(n);//分解质因数
sort(a + 1, a + 1 + tot);//按指数从小到大排序
num = 0;
//num用来记录当前已选择的指数
for (int i = 1; i <= tot; i++) {
	ans += x * (a[i].zhishu - num);
	num = a[i].zhishu;//更新指数
	x /= a[i].chengji;//减小所有数的乘积
	if (x == 1) break;
}
printf("%d\n",ans);
```

---

## 作者：Charles_with_wkc (赞：1)

# 题目翻译：
给出一整数 $n$，将这个数分解成因数的幂的乘积，且这些因数的质因数不能重复，求最大的这些因数与他们的幂指数的乘积之和最大是多少。
# 思路：
我这里用 $864$ 举例，$864 = 2^5 \times 3^3 = 2^2 \times 6^3$，这里我们要运用一个性质**两个不同的数相乘一定比相加大**，比如 $2 \times 3 > 2 + 3$，因此**加上幂指数大小关系不变**。这个过程实际上就是在分解质因数。
# 核心代码：
```cpp
cin>>n;
fjzys(n);//分解质因数
sort(a+1,a+1+tot);//按指数排序
for(int i=1;i<=n;i++){
    ans+=x*(a[i].zhishu-mi);
    mi=a[i].zhishu;
    x/=a[i].chengji;
}
```
这里提供一下分解质因数怎么分解放置有同学不会，如下。
```cpp
for(int i=2;i<=x;i++){//枚举质数（这里不用质数筛的原因是如果是4会在2的时候被筛掉了） 
	cnt=0;
	while(x%i==0){
		cnt++;
		x/=i;
	}//不停去除就像4会被除成1 
	if(cnt!=0){
		cout<<"整数x中含有质因数"<<i<<","<<cnt<<"个\n";
	}//保证一定是cnt中有数字才记录 
}
```
至于怎么存储还需要同学们自己想一想。

---

## 作者：QingDeng_Star (赞：0)

## 题目大意
给出一个数 $n$，将 $n$ 分解成因数的幂的乘积，要求这些指数与底数的乘积之和的最大值是多少。
## 思路
先把 $n$ 分解质因数。两个大于 $1$ 的数之积一定是大于等于这两个数的和。 因为质因数是不能重复的，要求最大值，就得把不同的质因数乘在一起使一个因数变得更大。
## 核心代码

```cpp
int n;
cin>>n;
fj(n);//分解质因数
sort(a+1,a+zs+1);//排序
for(int i=1;i<=n;i++)
{
    ans+=x*(a[i].zhishu-tmp);
    tmp=a[i].zhishu;
    x/=a[i].chengji;
}
```

---

## 作者：a_girl (赞：0)

## 题意
把一个整数 $n$ 分解成因数的幂的积，并且这些因数的质因数无重复，求这些指数与底数的乘积之和的最大值是多少。

## 思路
我们首先把 $n$ 分解质因数，两个大于 $1$ 的数之积一定不小于他们的和，比如说 $2\times 2=2+2$，因为质因数不能重复，所以要求最大值，我们就可以将不同的质因数乘在一起使得每一个因数变得更大。

## 部分代码

```cpp
cin>>n;
init(n);//分解质因数
sort(a+1,a+id+1);//按指数数量排序
for(int i=1;i<=n;i++){
    ans+=x*(a[i].zhishu-tmp);
    tmp=a[i].zhishu;
    x/=a[i].chengji;
}
```

---

## 作者：Eterna (赞：0)

###  大意

将一整数 $n$ 分解成因数的幂的积，并且这些因数的质因数不重复，求这些底数与指数的乘积之和最大是多少。

### 思路

类似贪心。

先将 $n$ 分解质因数。

可以证明，两个大于 $1$ 的数之积一定不小于他们的和。  
因为质因数不能重复，所以想要最大，就可以将不同的质因数乘在一起使单个因数更大。

最劣时间复杂度：$O(\displaystyle\sum\sqrt n)$。

可以通过，瓶颈主要在分解质因数，其实可以再优化，但是没必要。

---

## 作者：我梦见一片焦土 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF1787B)

---

# 思路：
可以将 $n$ 分解成质因数，要求是加和尽可能大，那么可以让所有的指数都是 $1$，$(a \times b) \gt (a+b)$ 一定成立，所以要尽可能地将质因数乘在一起组成更大的数，加在一起得到最后的解。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10;
const int INF=0x3f3f3f3f;
vector<pair<int,int> >get(int n){
	vector<pair<int,int> >res;
	for(int i=2;i<=n/i;i++){
		if(n%i==0){
			int s=0;
			while(n%i==0){
				n/=i;
				s++;
			}
			res.push_back({s,i});
		}
	}
	if(n>1){
        res.push_back({1,n});
    }
	return res;
}
int t,n;
signed main(){
	cin>>t;
	while(t--){
		cin>>n;
		vector<pair<int,int> > res=get(n);
		sort(res.begin(),res.end());
		int sum=1,last=0,ans=0;
		for(int i=0;i<res.size();i++){
            sum*=res[i].second;
        }
		for(int i=0;i<res.size();i++){
			ans+=sum*(res[i].first-last);
			sum/=res[i].second;
			last=res[i].first;
		}
		cout<<ans<<endl;
	}
	return 0;
}
```
完结撒花~

---

## 作者：loser_seele (赞：0)

结论：一种最优方案可以如下构造：从目前剩下的所有质因子里各取一个凑成新的数。

证明也很显然，我们只考虑指数为 $ 1 $ 的情况，否则不满足题意。因为对于两个质数 $ p,q \geq 2 $，将题目中给定的式子 $ \sum a_i \times p_i $ 代入计算，则显然有 $ p+q+2 \leq pq+1 $，那么合并两个数总是更优，再考虑第三个数，这时候有 $ pq+1+k+1 \leq pqk+1 $，以此类推。因此这么做答案一定不会更劣。

注意到 $ n \leq 10^9 $，于是我们用 Pollard-rho 分解质因子，时间复杂度 $ \mathcal{O}(Tn^\frac{1}{4}) $，可以通过。

代码：（已经省略过长的模板部分）

```cpp
int main() 
{
    uint64_t T;
    cin>>T;
    while(T--)
    {
        uint64_t n;
        cin>>n;
        uint64_t ans=0;
        auto map = OY::Pollard_Rho::decomposite(n);
        while(map.size())
        {
        uint64_t mul=1;
        for(int i=0;i<map.size();i++)
       mul*=map[i].prime,map[i].count--;
        auto tmp=map;
		tmp.resize(0);
        for(auto now:map)
        if(now.count)
        tmp.push_back(now);
        map=tmp;
        ans+=mul;
        }
        cout<<ans<<'\n';
    }
}
```

---

