# Odd sum

## 题目描述

现给予你一个长度为n,包含正整数的序列 ***a1,a2……an***，你的任务是找到一个和为奇数且值最大（在和为奇数的子序列中）的子序列。可以保证该序列中有和为奇数的子序列  
子序列是一个可以通过删除一个序列中的部分元素，但不改变其他元素的顺序后得到的新序列  
现在请你写一个程序找到上述的这样一个子序列

## 说明/提示

第一个样例中的第二个元素与第四个元素的和为3

## 样例 #1

### 输入

```
4
-2 2 -3 1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3
2 -5 -3
```

### 输出

```
-1
```

# 题解

## 作者：清清老大 (赞：2)

## 思路

首先，把所有正数相加，取得最大的和。接着，如果和为奇数，直接输出。

但是如果和不为奇数，则要通过增加或删除元素来使和为奇数，有两种方法，由于奇数 $-$ 奇数 $=$ 偶数 ， 所以可以删除最小的正奇数或者加上最大的负奇数，使得和为奇数且最大。

## 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

int main()
{
    int n,a,maxa = -10001,mina = 10001,sum = 0;
    cin >> n;
    for(int i = 0;i < n;i ++)
    {
        cin >> a;
        if(a > 0)
        {
            sum += a;
        }
        if(a < 0 && abs(a) % 2)
        {
            maxa = max(a,maxa);
        }
        if(a > 0 && a % 2)
        {
            mina = min(a,mina);
        }
    }
    if(sum % 2)
    {
        cout << sum;
    }
    else
    {
        cout << max(sum + maxa,sum - mina);
    }
}
```


---

## 作者：Fengxiang008 (赞：1)

### 解题思路：
本题是一道模拟题。（~~我最开始还以为是 dp~~）

**具体步骤：**

1. 先不考虑奇偶性，先找出序列中那些数加起来和最大。
代码实现：
```cpp
sum=max(sum,sum+a[i]);//将所有的序列中使sum大的数（即正数）
```

2. 如果最后结果是奇数，直接输出；如果最后是偶数，就减去到序列中最小的正奇数，或加上最大的负奇数，这样结果就能变为偶数。

### 代码实现：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100005],maxi=-10005,mini=10005,sum;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        sum=max(sum,sum+a[i]);//将所有的序列中使sum大的数（即正数 
        if(a[i]<0 && abs(a[i])%2)//找出最大的负奇数 
            maxi=max(a[i],maxi);
        if(a[i]>0 && a[i]%2)//找出最小的正奇数 
            mini=min(a[i],mini);
    }
    if(sum%2==0)//如果sum为偶数 
        sum=max(sum+maxi,sum-mini);//减去最小的正奇数或最大的负奇数 
    printf("%d\n",sum);//输出答案 
	return 0;
}
```


---

## 作者：伟大的王夫子 (赞：1)

县宣传一下[我的博客](https://www.luogu.com.cn/blog/I-AK-IOI/)

我们用这样一个策略去解题

首先，都加上正数

如果答案符合要求，那么就直接输出

否则就减去最小的奇正数，那么答案便是奇数

或者加上最大的奇负数

暴力模拟即可

注意判定没有奇负数或者奇正数的情况

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[100010], n, ans = -1e9, sum, x, y;
int main() {
	cin >> n;
	int minn = 1e9, maxn = -1e9;
	for (register int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
		if (a[i] > 0) sum += a[i];
		if (a[i] > 0 && abs(a[i]) % 2 == 1) minn = min(minn, a[i]);//最小的奇正数 
		if (a[i] < 0 && abs(a[i]) % 2 == 1) maxn = max(maxn, a[i]);//最大的奇负数 
	}
	if (sum % 2 == 1) {
		cout << sum << endl;//直接输出
		return 0;
	}
	if (minn != 1e9) ans = max(ans, sum - minn);
	if (maxn != -1e9) ans = max(ans, sum + maxn);//相互比较 
	cout << ans;
	
}
```


---

## 作者：雨伞CKY (赞：0)

# 题意简述
- 给定 $n$ 个整数 $a_{1},a_{2},\dotsc,a_{n}$。
- 你需要任取一些数，使得它的和为奇数且尽可能大。
- $1\leq n\leq 10^{5},-10^{4}\leq a_{i}\leq 10^{4}$。

# 题目分析
我们可以把数按照正负与奇偶分为正奇数、正偶数、$0$、负奇数、负偶数五类。要使和为奇数，必须要奇数个奇数和任意个偶数。

此外，$0$ 不会影响结果，不记入这些数中；负偶数不影响奇偶性，但会减小结果，不必记入结果。所以，应只记入正数和负奇数。

然而，正数会增大结果，可能会改变奇偶性；负奇数会减小结果，但可以改变奇偶性。所以，应当先计算所有正数的和 $sum$。如果 $sum$ 为奇数，直接输出 $sum$，否则 $sum$ 应加上最大负奇数或减去最小正奇数。

# 代码
```cpp
#include <algorithm>
#include <climits>
#include <cmath>
#include <iostream>
using namespace std;

int n,tmp,sum,minPosOdd = INT_MAX,maxNegOdd = INT_MIN;

int main(){
    cin >> n;
    for (int i = 1;i <= n;i++){
        cin >> tmp;
        if (tmp > 0){
            sum += tmp;
            if (tmp % 2 == 1) minPosOdd = min(minPosOdd,tmp);
        }
        else if (abs(tmp) % 2 == 1){
            maxNegOdd = max(maxNegOdd,tmp);
        }
    }
    if (sum % 2 == 1) cout << sum;
    else cout << sum + max(maxNegOdd,-minPosOdd);
}
```

---

## 作者：王熙文 (赞：0)

## 解题思路：

因为序列里的数有正有负，而题目要求和最大，所以可以先求出来所有为正数的数的和。

但是这个和可能为偶数，我们可以减去一个奇正数（已经在这个和里了，所以要减去）或者加上一个奇负数（不在这个和里）。分别求出最小的奇正数和最大的奇负数，用所有正数的总和减去最小的奇正数与最大的奇负数的相反数的最小值，就可以了。



## 参考代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxX=1e4;

int main()
{
    int n,a,sum=0,zhengji=maxX,xiaoji=-maxX;
    scanf("%d",&n);
    for(int i=1; i<=n; ++i)
    {
        scanf("%d",&a);
        if(a>0) sum+=a;
        if(a>0 && a%2) zhengji=min(zhengji,a);
        if(a<0 && a%2) xiaoji=max(xiaoji,a);
    }
    if(sum%2) printf("%d",sum);
    else printf("%d",sum-min(zhengji,-xiaoji));
    return 0;
}
```

---

## 作者：happybob (赞：0)

我用了 $\large \text{116}$ 行啊！！！

看到这个题，我首先想到的是贪心。

贪心思路：

我们先确定大于 $\text{0}$ 里面有多少个奇数。

- 如果数量是 $0$ 的话，我们需要找到一个最大的负奇数为答案，只需要一个，因为加负数相当于减去这个数的绝对值。又因为奇数加偶数等于奇数，我们再加上所有正偶数即为答案。

- 如果数量是奇数个，奇数乘奇数等于奇数，奇数加偶数也等于奇数，大于 $0$ 的都加起来就是答案。

- 如果数量是偶数个，也就是最坑人的！我们有两种情况：

1. 将所有正偶数和尽量多且是奇数个数的正奇数加起来

1. 将所有正数加起来，然后加上一个负奇数，因为偶数减奇数等于奇数。这里要注意，如果偶数里没有奇数那么这个方案无效，要特判，不然会 `WA`。

代码：

```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;

const int N = 1e5 + 5;
int a[N];
int n;

bool chk()
{
	for (int i = 1; i <= n; i++)
	{
		if (a[i] < 0 && (a[i] & 1)) return true;
	}
	return false;
}

int get()
{
	if (!chk())
	{
		return EOF;
	}
	int sum = 0;
	for (int i = 1; i <= n; i++)
	{
		if (a[i] > 0)
		{
			sum += a[i];
		}
		else
		{
			break;
		}
	}
	for (int i = 1; i <= n; i++)
	{
		if (a[i] <= 0 && (a[i] & 1))
		{
			sum += a[i];
			break;
		}
	}
	return sum;
}

int main()
{
	ios::sync_with_stdio(false);
	int ans = 0, cnt = 0;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
		cnt += (a[i] > 0 && (a[i] & 1));
	}
	sort(a + 1, a + n + 1, greater<int>());
	if (cnt == 0)
	{
		for (int i = 1; i <= n; i++)
		{
			if (a[i] & 1)
			{
				ans = a[i];
				break;
			}
		}
		for (int i = 1; i <= n; i++)
		{
			if (a[i] > 0)
			{
				ans += a[i];
			}
			else break;
		}
	}
	else if (cnt & 1)
	{
		for (int i = 1; i <= n; i++)
		{
			if (a[i] <= 0)
			{
				break;
			}
			ans += a[i];
		}
	}
	else if (!(cnt & 1))
	{
		int ans_second = get();
		int cnt_second = 0;
		for (int i = 1; i <= n; i++)
		{
			if (a[i] <= 0)
			{
				break;
			}
			cnt_second += a[i] & 1;
			if (cnt_second <= cnt - 1 && (a[i] & 1))
			{
				ans += a[i];
			}
			else if (!(a[i] & 1))
			{
				ans += a[i];
			}
		}
		if (ans_second != EOF)
		{
			ans = max(ans, ans_second);
		}
	}
	cout << ans << endl;
	return 0;
}
```
 
这个复杂度……

![https://cdn.luogu.com.cn/upload/image_hosting/palhmrua.png?x-oss-process=image/resize,m_lfit,h_170,w_225](https://cdn.luogu.com.cn/upload/image_hosting/palhmrua.png?x-oss-process=image/resize,m_lfit,h_1170,w_2225)

---

## 作者：chengni (赞：0)

根据题意很明显，我们为了这个数尽可能的大，会拿走所有正数，然后如果结果是奇数，答案就是这个数了。

如果是偶数的话，我们就需要进行抉择，扔掉一个最小的正的奇数，或者加入一个最大的负的奇数，我们需要判断这两种情况哪一个是更优的。

当然有可能会没有正奇数或者负奇数，那么只要对另一个进行操作就可以了。

ps:应该没有都不行的情况吧，那样这道题就挂了。

代码如下

```cpp
#include<bits/stdc++.h>

using namespace std;

inline int read(){
	char ch=getchar();int x=0,f=1;
	while(ch>'9' || ch<'0'){
        if(ch=='-') f=-1;
	    ch=getchar();
	}
	while(ch>='0' && ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}

int aa=0x7fffffff;//已知最小正奇数
int bb=-0x7fffffff;//已知最大负奇数

int sum;

int main(){
	int n=read();
	for(int i=1;i<=n;i++){
		int d=read();
		if(d>=0) {
		    sum+=d;//正数加上
		    if(d%2==1){
		    	aa=min(aa,d);
			}
		}
		else {
			if(abs(d)%2==1){
				bb=max(bb,d);
			}
		}
	}
	if(sum%2==1){//判断是否已经符合
		printf("%d\n",sum);
		return 0;
	}//三种情况判断
	if(aa==0x7fffffff){
		sum=sum+bb;
	}
	else if(bb==-0x7fffffff){
		sum=sum-aa;
	}
	else  {
		sum=max(sum+bb,sum-aa);
	}
	printf("%d\n",sum);
    return 0;
} 
```

---

## 作者：Indulge_myself (赞：0)

# 思路：
根据贪心思想，我们肯定首先要把所有的正数加起来，这样保证了最大。

但是这个时候有一种特殊情况：所有正数的和为偶数。这就引出了两种情况：

1. 需要减去一个最小的奇数正数

1. 需要加上一个最大的奇数负数

根据小学数学原理 1：偶数减奇数一定为奇数，可得上面的两种情况正确且最优。

如果是这样的话，我们直接贪心加暴力即可。

## Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin>>n;
    int a[n];
    for(int i=0;i<n;i++)
    cin>>a[i];
    int sum=0;
    for(int i=0;i<n;i++)
    if(a[i]>=0)sum+=a[i];//标记1
    if(sum%2==0)//标记2
    {
        int maxn=-999999;
        for(int i=0;i<n;i++)
        if(a[i]<0&&a[i]%2!=0&&maxn>a[i])maxn=a[i];
        if(maxn=-999999)
        {
            //找最小正数的代码与上面一段相似，就不贴了
        }
        cout<<sum+maxn<<endl;
        return 0;
    }
    else
    {
        cout<<sum<<endl;
        return 0;
    }
}
```

但是这一段代码有一个缺点：要是数据再大一点你不 T 掉算我输。

所以我们要考虑优化。

# 优化：
上面的算法的时间复杂度（忽略输入时间且考虑最不利情况）为 $ O(2n) $。能不能再优化？

注意看上面代码标记 1 的部分：这是在求正数的和。标记 2 则是在求最大的奇数负数。

其实我们可以把这个数组分成两段：正数段和负数段，一个快排就好啊。之后我们只要从后往前加正数，从前往后找负数就好啊。

但是这里还有一个优化：我们在从后往前加正数的时候就可以定义变量 $ xb $ 来保存正数和负数的分界点。

这样我们直接从分界点所指向的数 $ a_{xb} $ 来找就好了！

### 结语：

优化真的非常重要！为了防止有人喜欢 Ctrl+C，代码就不贴了，勤于动脑噢！

---

