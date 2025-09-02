# Subsequence Hate

## 题目描述

Shubham has a binary string $ s $ . A binary string is a string containing only characters "0" and "1".

He can perform the following operation on the string any amount of times:

- Select an index of the string, and flip the character at that index. This means, if the character was "0", it becomes "1", and vice versa.

A string is called good if it does not contain "010" or "101" as a subsequence — for instance, "1001" contains "101" as a subsequence, hence it is not a good string, while "1000" doesn't contain neither "010" nor "101" as subsequences, so it is a good string.

What is the minimum number of operations he will have to perform, so that the string becomes good? It can be shown that with these operations we can make any string good.

A string $ a $ is a subsequence of a string $ b $ if $ a $ can be obtained from $ b $ by deletion of several (possibly, zero or all) characters.

## 说明/提示

In test cases $ 1 $ , $ 2 $ , $ 5 $ , $ 6 $ no operations are required since they are already good strings.

For the $ 3 $ rd test case: "001" can be achieved by flipping the first character — and is one of the possible ways to get a good string.

For the $ 4 $ th test case: "000" can be achieved by flipping the second character — and is one of the possible ways to get a good string.

For the $ 7 $ th test case: "000000" can be achieved by flipping the third and fourth characters — and is one of the possible ways to get a good string.

## 样例 #1

### 输入

```
7
001
100
101
010
0
1
001100```

### 输出

```
0
0
1
1
0
0
2```

# 题解

## 作者：fengqiao17 (赞：6)

## Solution

注意到如果字符串的所有元素全为 1 或全为 0 的话，那么该字符串必为好串。

首先维护两个变量 $cnt0$ 和 $cnt1$ 以及答案 $mini$，$cnt0$ 和 $cnt1$ 分别表示在字符串中 0 的个数和 1 的个数，$mini$ 赋极大值。遍历字符串所有元素，如果某元素为 0，则将它变为 1，然后 $cnt0$ 减少一个，$cnt1$ 增加一个，同时比较前一轮 $cnt1$ 和 $cnt0$ 的大小，取出更小的那一个，与答案 $mini$ 取较小值；反之，亦然；

## Code
```cpp
//author:fengqiao17
//转载请标明地址：https://616673.blog.luogu.org/solution-cf1363b
#include <iostream>
using namespace std;
int main() {
  int t;
  cin >> t;
  while (t--) {              //多测，用while循环
    string s;
    cin >> s;
    int cnt0 = 0, cnt1 = 0;  // cnt0、cnt1分别统计0和1的个数
    for (int i = 0; i < s.size(); i++) {
      if (s[i] == '0') {
        cnt0++;
      } else {
        cnt1++;
      }
    }
    int mini = 1e9;          //答案赋极大值
    for (int i = 0; i < s.size(); i++) {
      mini = min(mini, min(cnt0, cnt1));
      if (s[i] == '0') {     //思路中说的判断
        cnt0--, cnt1++;
      } else {
        cnt1--, cnt0++;
      }
    }
    cout << mini << '\n';
  }
  return 0;
}
```

---

## 作者：Edmundino (赞：6)

# 题意

有一个01字符串，你每次可以把某个位置的0变成1或者把1变成0，

请问你至少操作多少次之后，该字符串不包含`010`或者`101`的子序列？

例如`1001`包含`101`子序列，但`1000`不包含任何`101`或`010`子序列。

# 分析

其实就是让你把一个字符串不交错，

比如`1111`,`0000000`,`11100000`,`0011`等等

那么，我们就可以先统计，把字符串全部改成`1`和全部改成`0`的情况。

然后，从某一个下标开始划分，就是这个阶段之前是`0`,后面是`1`，或者前面是`1`,后面是`0`。

所以问题就解决了。

# 代码

**求全部改成`0`或`1`的部分**

```cpp
for(int i=1;i<lon;i++)
{
	 sw[i]=sw[i-1],sx[i]=sx[i-1];
	 if(a[i]=='0')sa++,sw[i]++;
	 else sd++,sx[i]++;
	    	
}
```
**从某一点开始划分**

```cpp
for(int i=0;i<lon;i++)
{
	s=min(sx[i]+sa-sw[i],s);//sx[i]就是这点以前为1的个数
	s=min(sw[i]+sd-sx[i],s);//sw[i]就是这点以前为0的个数
}
```



 **$AC$代码** 

```cpp
#include<iostream>
#include<algorithm>
#include<iomanip>
#include<cstring>
#include<cstdio>
#include<cmath>

using namespace std;

const int N=1050;

int t,lon,s,sa,sd,sw[N],sx[N];

string a;

int main()
{
	cin>>t;
	while(t--)
	{
		cin>>a;
		lon=a.size();
		s=sa=sd=0;
		memset(sw,0,sizeof(sw));
		memset(sx,0,sizeof(sx));
		if(a[0]=='0')sa++,sw[0]++;
		else sd++,sx[0]++;
	    for(int i=1;i<lon;i++)
	    {
	    	sw[i]=sw[i-1],sx[i]=sx[i-1];
	    	if(a[i]=='0')sa++,sw[i]++;
	    	else sd++,sx[i]++;
	    	
		}
		s=100000000;
		s=min(sa,sd);
		for(int i=0;i<lon;i++)
		{
			s=min(sx[i]+sa-sw[i],s);
			s=min(sw[i]+sd-sx[i],s);
		}
		cout<<s<<endl;
	}
	return 0;
 } 
```


---

## 作者：SpeedStar (赞：5)

### 算法分析
注意到，如果字符串的所有元素全为$0$或全为$1$的话，那么该字符串必为好串。

首先维护两个变量$c0$和$c1$，分别表示在字符串中$0$的个数和$1$的个数。然后遍历字符串所有元素，如果某元素为$0(1)$，则将它变为$1(0)$，所以$c_0(c_1)$减少一个，$c_1(c_0)$增加一个，同时比较前一轮$c0$和$c1$的大小，取出更小的那一个(如果$c_0(c_1)$更小，则把剩下的$0(1)$都变成$1(0)$)，以使得每次操作可以让该字符串变成好串的代价最小，并不断更新最小代价。


### C++代码
```cpp
#include <iostream>

#define rep(i, n) for (int i = 0; i < n; ++i)

using namespace std;

int main() {
	int t;
	cin >> t;
	
	while (t--) {
		string s;
		cin >> s;
		int n = s.size();
		int c0 = 0, c1 = 0;
		
		rep(i, n) (s[i] == '0' ? c0 : c1)++;
		
		int res = 1e9;
		rep(i, n) {
			res = min(res, min(c0, c1));
			if (s[i] == '0') --c0, ++c1;
			else --c1, ++c0;
		}
		
		cout << res << '\n';
	}
	
	return 0;
}
```


---

## 作者：liuyi0905 (赞：2)

~~话说我的方法和题解里面的巨佬不一样诶~~，但我还是勇敢得讲一讲。

### 思路：
1. 一定不会将一个位置的数翻两次。
1. 最后的结果一定会是 $0$ 一边，$1$ 一边。

然后就发现这道题是不是和 [P7404 [JOI 2021 Final] とてもたのしい家庭菜園 4](/problem/P7404) 挺像的，可以看[这篇](/blog/717971/solution-p7404)。

应为这道题有左边是 $0$ 右边是 $1$，左边是 $1$ 右边是 $0$ 两种情况，所以要多维护两个数组，最后的答案即为：$\min\limits_{1\le i\le len}\{\min(pr1_i+nx0_{i+1},pr0_i+nx1_{i+1})\}$。

有了答案，就可以直接写代码了（无注释）：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1005;
string s;
int t;
int good(string s){
	int len=s.size(),mini=1e18;
	int pr0[N]={0},pr1[N]={0},nx0[N]={0},nx1[N]={0};
	s=" "+s;
	for(int i=1;i<=len;i++)
		if(s[i]=='1')pr1[i]=pr1[i-1]+1,pr0[i]=pr0[i-1];
		else pr1[i]=pr1[i-1],pr0[i]=pr0[i-1]+1;
	for(int i=len;i>=1;i--)
		if(s[i]=='1')nx1[i]=nx1[i+1]+1,nx0[i]=nx0[i+1];
		else nx1[i]=nx1[i+1],nx0[i]=nx0[i+1]+1;
	for(int i=1;i<=len;i++)mini=min(mini,min(pr1[i]+nx0[i+1],pr0[i]+nx1[i+1]));
	return mini;
}
signed main(){
	cin>>t;
	while(t--)cin>>s,cout<<good(s)<<"\n";
	return 0;
}
```

---

## 作者：刘健铭 (赞：2)

# Subsequence Hate

思路：三种情况：要么全是一，要么全是零，或者一边是一，一边是零，一边是零，一边是一，前两种直接统计零，一个数取最小，第三，四种情况因为我们不知道从以哪个地方为分界线，所以直接暴力遍历一遍，枚举所有情况。（注意这题，最优情况可能是改几个零然后再改几个一，所以不能直接全部改零或全部改一）

$0000000000000.......11111111111111$

$0000000000000.......11111111111111$

$1111111111111111111111111111111$

$0000000000000000000000000000000$

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		char s[1005];
		int cnt1=0,cnt2=0;
		scanf("%s",s);
		for(int i=0;i<strlen(s);i++)
		{
			if(s[i]=='0')
			cnt1++;
			else
			cnt2++;
		}
		int ans=1000000;
		for(int i=0;i<strlen(s);i++)
		{
			ans=min(ans,min(cnt1,cnt2));
			if(s[i]=='0')
			{
				cnt1--;
				cnt2++;
			}
			else
			{
				cnt1++;
				cnt2--;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：wz20201136 (赞：2)

# 题目大意
有题目可得，要将字符串变成没有 $101$ 或 $010$ 的字符串，等价于在所有字符 $1$ 中没有穿插字符 $0$ ，同时所有字符 $0$ 中没有穿插字符 $1$。

也就是新字符串的 $0$ 全部位于左部或全部位于右部，同理可得所有 $1$ 也全部位于左部或全部位于右部。
# 思路
分别统计字符 $0$ 和 $1$ 的前后缀和，枚举字符 $1$ 与 $0$ 的分割点，之后选最小值。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,s1[1111],s2[1111],S1[1111],S2[1111];
//分别统计0，1的前后缀和
string str;
int main()
{
	cin>>t;
	while(getchar()!='\n');
	while(t--)
	{
		getline(cin,str);
		int n=str.size();
		memset(s1,0,sizeof(s1));
		memset(s2,0,sizeof(s2));
		memset(S1,0,sizeof(S1));
		memset(S2,0,sizeof(S2));//初始化
		for(int i=1;i<=n;i++)//前缀和
		{
			s1[i]=s1[i-1]+(str[i-1]=='1');
			s2[i]=s2[i-1]+(str[i-1]=='0');
		}
		for(int i=n;i>=1;i--)//后缀和
		{
			S1[i]=S1[i+1]+(str[i-1]=='0');
			S2[i]=S2[i+1]+(str[i-1]=='1');
		}
		int ans=INT_MAX;
		for(int i=0;i<=n;i++) ans=min(ans,min(s1[i]+S1[i+1]/*前部为0，后部为1的情况*/,s2[i]+S2[i+1]));//前部为1，后部为0的情况
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：liwenxi114514 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1363B)。

其实这题很简单，既然不能出现 $010$ 或 $101$ 的情况，那就让字符串变成**一边全是 $1$，一边全是 $0$ 的情况**，再把所有情况枚举出来，求出需要改变次数的最小值。

考虑使用前缀和，用前缀和记录从 $1$ 到 $i$ 的 $0$ 和 $1$ 的数量。具体见注释。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,sum1[1005],sum0[1005],minn=INT_MAX;//sum1记录1的前缀和数组，sum0记录0的前缀和数组。
string s;
int main(){
	cin>>n;
	while(n--){
		minn=INT_MAX;//记得初始化！！！
		memset(sum0,0,sizeof(sum0));//记得初始化！！！
		memset(sum1,0,sizeof(sum1));//记得初始化！！！
		cin>>s;
		int len=s.size();
		for(int i=1;i<=len;i++){//从1开始枚举是为了方便前缀和数组
			if(s[i-1]=='0'){//由于我们是从1开始的，所以对于字符串来说，下标就是i-1
				sum0[i]=sum0[i-1]+1;//如果这一位是0，sum0数组+1，sum1数组不变
				sum1[i]=sum1[i-1];
			}else{
				sum1[i]=sum1[i-1]+1;//如果是1则相反
				sum0[i]=sum0[i-1];
			}
		}
		for(int i=1;i<=len;i++){//枚举分界点
			minn=min(minn,min(sum1[i]+sum0[len]-sum0[i],sum0[i]+sum1[len]-sum1[i]));//min的前项是求左边全是0（要把1变成0，求左边1的数量），右边全是1（要把0变成1，求右边0的数量），后项是求左边全是1（要把0变成1，求左边0的数量），右边全是0（要把1变成0，求右边1的数量）
		}
		cout<<minn<<"\n";//输出加换行
	}
	return 0;//完结撒花！！！
}
```


---

## 作者：btng_smith666 (赞：1)

被同学骗来做这道题，顺便水一发题解（

说在前面，这题其实就是要把所有的字符都变成 $0$ 或 $1$ 。

这题主要思路是分别取出`01`串中`1`和`0`的个数，然后循环每次更新最小值，顺便将该位置翻转（只在计数器中翻），这样就能取出最小的操作次数。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,x,y,ans;
string str;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		cin>>str;
		x=y=0;//x是0的数量，y是1的数量 
		for(int i=0;i<str.size();i++)
			if(str[i]=='0')//计数 
				x++;
			else
				y++;
		ans=INT_MAX;//最大值 
		for(int i=0;i<str.size();i++)
		{
			int minn=min(x,y);//取出最小值 
			if(minn<ans)//比较 
				ans=minn;//将此次答案赋值为最小值 
			if(str[i]=='0')//如果是0就将x减回去，y加1，完成将1转成0的过程 
				x--,y++;
			else//否则将y减回去，x加1，完成将0转成1的过程 
				x++,y--;
		}
		printf("%d\n",ans);//输出答案 
	}
	return 0;
}
```


---

## 作者：Neilchenyinuo (赞：0)

## Solution
1. 维护 $sum0_{i}$ 和 $sum1_{i}$ 表示前 $i$ 个数 $0$ 和 $1$ 的数量。

2. 维护 $post0_{i}$ 和 $post1_{i}$ 表示后 $i$ 个数 $0$ 和 $1$ 的数量。

3. 枚举 $0$ 和 $1$ 的分界线 $i$。

4. 当 $a_{1}$ 到 $a_{i}$ 全为 $0$ 时，则 $i$ 左侧修改 $sum1_{i}$ 次，右侧修改 $post0_{i+1}$ 次。

5. 当 $a_{1}$ 到 $a_{i}$ 全为 $1$ 时，则 $i$ 左侧修改 $sum0_{i}$ 次，右侧修改 $post1_{i+1}$ 次。

6. 定义 $mini$ 存储最小修改次数，最后输出。

### 注意：
1. 多组数据记得清空。

## Code

```cpp
#include<bits/stdc++.h> 
using namespace std;
const int N=1e3+5;
int t,sum1[N],sum0[N],post1[N],post0[N];
int work()
{
	string s;
	cin>>s;
	for(int i=0;i<s.size();i++)
	{
		if(s[i]=='1')
		{
			sum1[i]=sum1[i-1]+1;
			sum0[i]=sum0[i-1];
		}
		else
		{
			sum1[i]=sum1[i-1];
			sum0[i]=sum0[i-1]+1;
		}
	}
	memset(post1, 0, sizeof(post1));
	memset(post0, 0, sizeof(post0));
	for(int i=s.size()-1;i>=0;i--)
	{
		if(s[i]=='1')
		{
			post1[i]=post1[i+1]+1;
			post0[i]=post0[i+1];
		}
		else
		{
			post1[i]=post1[i+1];
			post0[i]=post0[i+1]+1;
		}
	}
	int mini=1e9;
	for(int i=0;i<s.size();i++)
	{
		int tmp=min(sum1[i]+post0[i+1],sum0[i]+post1[i+1]);
		mini=min(mini,tmp);
	}
	return mini;
} 
int main()
{
	cin>>t;
	while(t--)
	{
		cout<<work()<<endl;
	}
	return 0;
}
```
#### 莫抄袭，没了AC记录，空悲切。

---

## 作者：Yizhixiaoyun (赞：0)

[本套题所有题解](https://www.luogu.com.cn/blog/yizhixiaoyun/cf1363-ti-xie)

由于笔者水平较弱，所以可能只能一路做到自己做不了的题，不保证能全部写完。

------------
洗了个澡想出的题...

首先是一个显而易见的性质：**全部为 $1$ 或 $0$ 的字符串必定是好串**。

唯一需要判断的就是只有一个字符不同且在两端的情况。

考虑记录 $1$ 与 $0$ 在字符串中的个数，随后遍历字符串不断更新最小价值。遍历过程中，对于特殊情况，找一下两个数字个数的最小值就可以了。

```cpp
#include<bits/stdc++.h>
#define betterIO ios::sync_with_stdio(false);cin.tie(0)
using namespace std;
const int inf=1e9;
int T;
int n;
int cnt0,cnt1,ans;
string s;
inline void init(){
	cin>>s;n=s.size();s=" "+s;
	cnt0=0;cnt1=0;ans=inf;
	for(register int i=1;i<=n;++i){
		if(s[i]=='0') cnt0++;
		else cnt1++;
	}
}
int main(){
	betterIO;
	cin>>T;
	while(T--){
		init();
		for(register int i=1;i<=n;++i){
			ans=min({ans,cnt0,cnt1});
			if(s[i]=='0'){
				cnt0--;cnt1++;
			}
			else{
				cnt0++;cnt1--;
			}
		}
		cout<<ans<<endl;
	}
} 
```

---

## 作者：ShineEternal (赞：0)

[更佳的阅读效果](https://vipblog.github.io/pRCDOERxL/)

## description：
将一个 `01` 串变为不含 `010` 和 `101` 子串的字符串。

## solution：
仔细分析一下性质就可以发现，我们大部分情况下需要将整个字符串都变成 `0` 或 `1`。

但是如果整个字符串中只有一个 `0/1`  在字符串的两端，那么情况也是合法的。

所以我们只需要在变字符串的时候每次都更新一下两种数字的最小值就行了。

其最小值就意为最小可以获取的步数。


## code：
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		char s[1005];
		int cnt1=0,cnt2=0;
		scanf("%s",s);
		for(int i=0;i<strlen(s);i++)
		{
			if(s[i]=='0')
			cnt1++;
			else
			cnt2++;
		}
		int ans=1000000;
		for(int i=0;i<strlen(s);i++)
		{
			ans=min(ans,min(cnt1,cnt2));
			if(s[i]=='0')
			{
				cnt1--;
				cnt2++;
			}
			else
			{
				cnt1++;
				cnt2--;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
} 
```

---

