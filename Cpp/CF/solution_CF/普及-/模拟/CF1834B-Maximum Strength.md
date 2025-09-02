# Maximum Strength

## 题目描述

Fedya is playing a new game called "The Legend of Link", in which one of the character's abilities is to combine two materials into one weapon. Each material has its own strength, which can be represented by a positive integer $ x $ . The strength of the resulting weapon is determined as the sum of the absolute differences of the digits in the decimal representation of the integers at each position.

Formally, let the first material have strength $ X = \overline{x_{1}x_{2} \ldots x_{n}} $ , and the second material have strength $ Y = \overline{y_{1}y_{2} \ldots y_{n}} $ . Then the strength of the weapon is calculated as $ |x_{1} - y_{1}| + |x_{2} - y_{2}| + \ldots + |x_{n} - y_{n}| $ . If the integers have different lengths, then the shorter integer is padded with leading zeros.

Fedya has an unlimited supply of materials with all possible strengths from $ L $ to $ R $ , inclusive. Help him find the maximum possible strength of the weapon he can obtain.

An integer $ C = \overline{c_{1}c_{2} \ldots c_{k}} $ is defined as an integer obtained by sequentially writing the digits $ c_1, c_2, \ldots, c_k $ from left to right, i.e. $ 10^{k-1} \cdot c_1 + 10^{k-2} \cdot c_2 + \ldots + c_k $ .

## 说明/提示

In the first test case, the weapon made from materials with strengths $ 53 $ and $ 57 $ will have the maximum possible strength: $ |5 - 5| + |3 - 7| = 4 $ .

In the second test case, the maximum strength is achieved with materials with strengths $ 190 $ and $ 209 $ : $ |1 - 2| + |9 - 0| + |0 - 9| = 19 $ .

In the fourth test case, there is only one valid strength, so the answer is $ 0 $ .

In the sixth test case, the maximum strength is achieved with materials with strengths $ 1909 $ and $ 90 $ : $ |1 - 0| + |9 - 0| + |0 - 9| + |9 - 0| = 28 $ . Note that the shorter integer was padded with leading zeros.

## 样例 #1

### 输入

```
6
53 57
179 239
13 37
132228 132228
54943329752812629795 55157581939688863366
88 1914```

### 输出

```
4
19
11
0
163
28```

# 题解

## 作者：LukeLuke (赞：6)

# CF1834B

此题可以用**贪心**做。

首先，如果 $L$ 的位数比 $R$ 少，就要在前面加上 $0$。

然后将 $L$ 和 $R$ 前面一样的部分删去，保证 $L$ 和 $R$ 的最高位的数字不一样。

假设 $L$ 和 $R$ 分别为： 

$$
L = \overline{ABC\cdots}\\
R = \overline{DEF\cdots}
$$

那么考虑构造两个数 $X$ 和 $Y$，长这样子： 

$$
X = \overline{D000\cdots}\\
Y = \overline{A999\cdots}
$$

由于 $X$ 的最高位是 $D$，而 $D > A$，所以 $X > L$。
$X$ 的除最高位外都是 $0$，所以 $X \le R$。

$Y$ 的最高位是 $A$, 而 $A  < D$， 所以 $Y < R$。
$Y$ 除最高位外都是 $9$, 所以 $Y \geq L$。

综上所述，$X$ 和 $Y$ 是合法的。

而答案就是 $D-A+(size(X) - 1) \times 9$。（加上前导 $0$ 之后，$size(X)=size(Y)$）这是最优答案。（不可能有两个一位数的差大于 $9$）所以贪心成立。

注意最后要特判一下，如果 $L=R$，就输出 $0$。

#### 代码
```c++
#include <bits/stdc++.h>
using namespace std;
 
const int N = 110;

char l[N], r[N];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
    	scanf("%s%s", l, r);
        int n = strlen(l), m = strlen(r);
        reverse(l, l + n);
        reverse(r, r + m);
        for (int i = n; i < m; i++) l[n++] = '0';
        while (n && l[n - 1] == r[m - 1]) --n, --m;
        if (!n) puts("0");
        else printf("%d\n", (n - 1) * 9 + abs(l[n - 1] - r[n - 1]));
    }
    return 0;
} 
```

---

## 作者：Mr_Biantainne (赞：4)

## 题外话
第一次打 div2，写篇题解。

~~竟然敢随便提到王国之泪！~~
## 题意简述
在 $l$ 和 $r$ 之间选两个整数，使得它们每一位之差的和最大，求最大值。
## 解法介绍
### 前置知识：贪心。
因为要和最大，所以大部分位要差最大。怎么样做呢？必然一个位取 9，另一个对应的位取 0。

先把两个数补充到同样的长度再继续操作。**这里有一个要点：如果两个数的最前面几个高位是一样的，那就可以忽略不计了，去掉不看。下一位还不能随便取，要计算好上下限（即两位的差的绝对值）。后面就可以随便取 9 和 0 了。**
## 代码
```cpp
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
ll t;
string a, b;
int main()
{
    cin >> t;
    while (t--)
    {
        cin >> a >> b;
        reverse(a.begin(), a.end()), reverse(b.begin(), b.end()); //反转，方便添加0
        while (a.size() < b.size()) a.push_back('0'); //如果第一个数字位数少就加0
        while (a.size() > b.size()) b.push_back('0'); //如果第二个数字位数少就加0
        ll p = a.size() - 1;
        while (p >= 0 && a[p] == b[p]) p--; //去掉相同的高位
        if (p == -1) cout << 0 << endl; //什么都没有，两个数字完全一样，答案只能为0
        else cout << abs(a[p] - b[p]) + p * 9 << endl; //下一位计算上下限，然后后面随便取
    }
}
```
~~点个赞再走吧~~

---

## 作者：fantastic_dream (赞：2)

## 思路
首先我们知道 $\overline{abc00} \leq \overline{abcde} \leq \overline{abc99}$，并且如果范围允许，要使得 $\left\vert x_i-y_i\right\vert$ 最大，第 $i$ 位上的减法应该是 $\left\vert 0-9\right\vert=9$。如果两个数上的同一位数字不同，那么下一位一定能凑出 $0$ 和 $9$，这一位上差的最大值显然是这一位上数字的差，因为前面都是相等的。

那么我们的贪心就呼之欲出了：从最高位向后遍历当有一位上的数字不同，答案便是该位数字的差与后面位数乘上 $9$。

## 注意：
- 位数不相等时，把前面空缺的位想象成 $0$ 去算，但是不同的那一位要算作较大数字最高位的前一位，可以分类讨论。
- 由于数据范围，应用字符串存储数据。
- （~~我这个蒟蒻犯的错误~~）在交换两个数时，记得交换两数的长度。（大部分人代码中没有这个部分）。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n;
string a,b;
int main(){
	ios::sync_with_stdio(0);
	cin>>T;
	while(T--){
		cin>>a>>b;
		int len1=a.size(),len2=b.size(),ans=0,cnt;
		if(len1!=len2){
			if(len1>len2)	swap(a,b),swap(len1,len2);//别忘了交换 len1,len2! 
			for(int i=0;i<len2-1;i++){
				ans+=9;
			}
			ans+=b[0]-'0';
			cout<<ans<<'\n';
			continue;
		}
		cnt=len1;
		for(int i=0;i<len1;i++){
			if(a[i]!=b[i]){
				ans+=abs(b[i]-a[i]);
				cnt=i+1;
				break;
			}	
		}
		ans+=9*(len1-cnt);
		cout<<ans<<'\n';
	}
	return 0;
}

```

---

## 作者：Auto_Accepted (赞：2)

## 题意

给定一个区间 $[l,r]$，现在取两个数，使得他们的每一位的差之和最大，输出这些差之和。多组数据测试。

## 题解

观察到数据范围为 $ 1 \le L \le R < 10^{100} $，超过 ```unsigned long long``` 范围，应使用字符串。

下文内 $a_i$ 默认为字符串 $a$ 的前 $i$ 位。

不难发现，当 $l_i \ne r_i$ 时，后面可以取成全 $9$ 和全 $0$，这样差才会最大。

而当 $l_i=r_i$ 时，差显然为 $0$。

最后的答案为 $9\ \times\ (size\ -\ i)\ +\ r_i\ -\ l_i\ \ (l_i \ne r_i$ 且 $i$ 最小$)$，输出这个答案即可。

## 代码

```
#include <bits/stdc++.h>
using namespace std;
#define int long long
int work(string a , string b){
	int ans = 0;
	if(a.size() < b.size()) a.insert(0 , b.size() - a.size() , '0');
//	cout << a << ' ' << b << endl;
	int tmp = a.size() - 1;
	int i;
	for(i = 0;i <= tmp;i++){
		if(a[i] != b[i]){
			ans += b[i] - a[i];
			break;
		}
	}
	ans += 9 * (max(tmp - i , 0ll));
	return ans;
}
signed main(){
	int t;
	string a , b;
	cin >> t;
	while(t--){
		cin >> a >> b;
		cout << work(a , b) << endl;
	}
	return 0;
}
```


---

## 作者：无钩七不改名 (赞：1)

### 题意：

求两个数每一位之差的绝对值之和。

### 思路：

从 $L$ 和 $R$ 的最高位开始对比，设当前位数为 $i$。

如果 $L_i$ 和 $R_i$ 相等，则绝对值最大肯定为 $0$。

否则绝对值最大为 $\operatorname{abs}(L_i-R_i)$，后面每一位的绝对值最大都为 $9$，也就不用再搜下去了。

理由：因为此时小数该位取 $L_i$，大数该位取 $R_i$，小数后面每一位都取 $9$，大数后面每一位都取 $0$，都不会超出范围，且此时绝对值之差最大。

### 代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;

int t;
int a[105],b[105],cnt1,cnt2;
int ans;

int main(){
	scanf("%d",&t);
	while(t--){
		//cout<<"***"<<t<<endl;
		ans=0;cnt1=0;cnt2=0;
		char c;c=getchar();
		while(c<'0'||c>'9')c=getchar();
		while(c>='0'&&c<='9'){
			a[++cnt1]=c-'0';
			c=getchar();
		}
		while(c<'0'||c>'9')c=getchar();
		while(c>='0'&&c<='9'){
			b[++cnt2]=c-'0';
			c=getchar();
		}
		if(cnt1>cnt2){
			for(int j(cnt1);j>cnt1-cnt2;j--)
				b[j]=b[j-(cnt1-cnt2)];
			for(int j(cnt1-cnt2);j;j--)
				b[j]=0;
			cnt2=cnt1;
		}
		else if(cnt1<cnt2){
			for(int j(cnt2);j>cnt2-cnt1;j--)
				a[j]=a[j-(cnt2-cnt1)];
			for(int j(cnt2-cnt1);j;j--)
				a[j]=0;
			cnt1=cnt2;
		}
		bool bo=0;
		for(int j(1);j<=cnt1;j++){
			if(bo)ans+=9;
			else ans+=abs(a[j]-b[j]);
			if(a[j]!=b[j])bo=1;
		}
		printf("%d\n",ans);
	}
	return 0;
} 
```

---

## 作者：huangrenheluogu (赞：0)

## Preface

感觉比 C 难。

## Solution

先补 $0$。

然后一位一位判断。如果一样，那显然两个数这一位都是这样的，如果不一样，我们下面讨论。

如果两个数字为 $\overline{a_1a_2...a_n},\overline{b_1b_2...b_n}$，如果在第 $i$ 为发现不一样，我给出的是 `ans = 9 * (len - i) + abs(a[i] - b[i]);`。

下面我将对其证明。

- 可行性

我们把前面的位数都去掉，有两个数 $\overline{a_ia_2...a_n},\overline{b_ib_2...b_n}$，满足 $a_i \ne b_i$。不妨 $a_i< b_i$。

我们发现，可以取到 $\overline{a_i99...9}$ 和 $\overline{b_i00...0}$。他们算出来就是 $9\times(len-i)+b_i-a_i$。

- 最值性

由于前面都是一样的，所以这一位的值 $x_i\in[a_i,b_i]$，而后面的 $x_{i+1},x_{i+2},...,x_n\in[0,9]$，所以，最大差值就是 $b_i-a_i+9\times(n-i)$。

证毕。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 105;
int T, lena, lenb, a[N], b[N], len, ans, suma[N], sumb[N];
string s1, s2;
inline void read(int &res){
	char ch=getchar();int f=1;res=0;
	while('0'>ch||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while('0'<=ch&&ch<='9'){
		res=(res<<1)+(res<<3)+(ch^48);
		ch=getchar();
	}
	res*=f;
}
signed main(){
	read(T);
	while(T--){
		cin >> s1 >> s2;
		memset(a, 0, sizeof(a));
		memset(b, 0, sizeof(b));
		lena = s1.size(), lenb = s2.size();
		if(s1 == s2){
			printf("0\n");
			continue;
		}
		len = max(lena, lenb);
		for(int i = len - lena + 1; i <= len; i++) a[i] = s1[i - (len - lena + 1)] - '0';
		for(int i = len - lenb + 1; i <= len; i++) b[i] = s2[i - (len - lenb + 1)] - '0';
		for(int i = len; i; i--) suma[i] = suma[i + 1] + a[i];
		for(int i = len; i; i--) sumb[i] = sumb[i + 1] + b[i]; 
		for(int i = 1; i <= len; i++){
			if(a[i] == b[i]) continue ;
			ans = 9 * (len - i) + abs(a[i] - b[i]);
			break;
		}
		printf("%d\n", ans);
	}
	return 0;
}

```

---

## 作者：skyskyCCC (赞：0)

## 前言。
稍加分析就可以做出来的题。
## 分析。
其实这个题目看起来很难理解，但其实就是求两个数每一位之差的绝对值之和。

如果数据范围偏小，我们可以用常规的方法定义，但考虑到数据范围，我们要用字符串进行读入，所以这个题要通过字符串与数字的转化来完成。

因为存在可以补齐的情况，所以我们需要分情况讨论。

- 当两个字符串长度相等时。

这个情况比较好分析。考虑到数据的区间范围，对于前面的相同的数据，差的绝对值是 $0$ 所以不需要考虑。但对于同位置但不同数据的地方，我们可以尽可能用差值较大的两个数，所以不难想到，较小的那个数后边尽可能选择 $0$ 而较大数后面尽可能选择 $9$ 可以使结果最优。

- 当两个字符串长度不同时。

当我们把位数补齐后，我们可以同样用上述思路分析。考虑到区间范围，我们可以让较小数在和较大数的共有位上尽可能取 $9$ 而较大数取 $0$ 使结果最优。对于我们补齐的位数，因为较大数的对应位置上有数，所以保留即可。

代码如下，仅供参考：
```
#include<iostream>
#include<cstring>
using namespace std;
int t,n,ans;
string l,r;
int main(){
	cin>>t;
	while(t--){
		ans=0;
		cin>>l>>r;
		int len=l.size();
		int len2=r.size();
		if(len==len2){//情况1。
			if(l==r){
				cout<<"0\n";
				continue;
			}
			int sum=0;
			for (int i=0;i<=len;i++){
				if(l[sum]==r[sum]){
					sum++;
				}
			}
			cout<<(len-sum-1)*9+(int)(r[sum]-l[sum])<<"\n";
		}
		else{//情况2。
			for (int i=0;i<len2-1;i++){
				ans+=9;//相当于补齐。
			}
			ans+=r[0]-'0';
			cout<<ans<<"\n";
		}
	}
	return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：封禁用户 (赞：0)

# 题目描述

[Maximum Strength](https://www.luogu.com.cn/problem/CF1834B)

## 题意

给你一个区间 $[l,r]$，现在在这个区间内取两个数，使得这两个数每一位的差之和最大，输出这个最大值。

# 算法思路

看到范围 $1 \le L \le R < 10^{100}$，就立马可以得出：不能用枚举，而且只能用字符串。

那我们如何求出最大值呢？贪心。可以想到当 $l_i \ne r_i$ 时，后面的数可以全部取成 $9$ 和 $0$，这样子差就会最大。

最后的答案为 $9\times(size-i)+r_i-l_i$。

### 时间复杂度：$O(t \times n)$。

## 代码
```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;//日常开long long 
ll t,ans,tmp,i;
string a,b;
ll take(string a,string b)
{
	if(a.size()<b.size())//如果位数不同 
	{
		a.insert(0,b.size()-a.size(),'0');//0补齐 
	}
	ans=0;
	tmp=a.size()-1;
	for(i=0;i<=tmp;i++)
	{
		if(a[i]!=b[i])//如果a[i]不等于b[i]
		{
			ans+=b[i]-a[i];//答案加上b[i]-a[i]
			break;
		}
	}
	ans+=9*(max(tmp-i,0ll)); 
	return ans;//返回ans 
} 
int main()//简洁明了的主程序 
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);//输入输出优化(关同步) 
	cin>>t;//t组数据 
	while(t--)
	{
		cin>>a>>b;//输入 
		cout<<take(a,b)<<"\n";//输出 
	}
	return 0;
}
```

---

## 作者：_sunkuangzheng_ (赞：0)

**【题目分析】**

我们分情况讨论。设数 $a$ 长度为 $l_1$，$b$ 长度为 $l_2$。

- $l_1 \ne l_2$

我们用一个例子来分析：

$$0088$$

$$1914$$

我们发现在后面的共有位上，$a$ 一定可以全部取 $9$，$b$ 一定可以全部取 $0$，使得差值最大。而前面的由于是 $-0$，所以保留原位最优。

- $l_1 = l_2$

依旧用例子分析：

$$12105$$

$$12488$$

我们发现相同位上没有发挥余地，贡献是 $0$。而对于非相同位上的最高位，一定差值最大最优。后面的位数都可以取全 $0$ 和全 $9$。

**【代码】**

```cpp
#include <bits/stdc++.h>
using namespace std;
int t,n;
string a,b;
int main(){
	cin >> t;
	while(t --){
		cin >> a >> b;
		int l1 = a.size(),l2 = b.size(),ans = 0;
		if(l1 == l2){
			if(a == b) {cout << 0 << endl;continue;}
			int s = 0;
			while(a[s] == b[s]) s ++;
			cout << (l1 - s - 1) * 9 + (int)(b[s] - a[s]) << endl;
		}
		else{
			for(int i = 0;i < l2-1;i ++) ans += 9;
			ans += b[0] - '0';
			cout << ans << endl;
		}
	}
	return 0;
}
```



---

## 作者：little_kongbai (赞：0)

先看数据范围，$10^{100}$ 的数据范围应用字符串处理。

首先对于 $L$ 和 $R$ 位数不同的情况下补齐 $0$，随后发现了一个不错的性质，我们需要找到第一位 $i$ 使得 $L_i \ne R_i$，对于所有 $j > i$，令 $L_j \gets 9,R_j \gets 0$，容易发现这样可以让答案最大。

Code:

```cpp


    	#include<bits/stdc++.h>
    	using namespace std;
    	int t;char a[105],b[105];
    	int main(){
    		scanf("%d",&t);
    		while(t--){
    			scanf("%s%s",a+1,b+1);
    			int cz=strlen(b+1)-strlen(a+1),ls=strlen(a+1);
    			a[ls+cz+1]='\0';
    			int ans=0;
    			if(cz)for(int i=strlen(a+1);i;i--){
    				a[i+cz]=a[i];
    				a[i]='0';
    			}
    			int len=ls+cz;bool f=0;
    			for(int i=1;i<=len;i++){
    				if(f||a[i-1]<b[i-1]){
    					ans+=9;f=1;
    				}else ans+=b[i]-a[i];
    			}
    			printf("%d\n",ans);
    		}
    		return 0;
    	}
```


---

