# Equality

## 题目描述

### 题目大意：
给定一个长度为$n$的字符串和$k$，问这个字符串包含字母表前$k$个大写字母并且数量相同的子序列最长是多少

## 样例 #1

### 输入

```
9 3
ACAABCCAB
```

### 输出

```
6```

## 样例 #2

### 输入

```
9 4
ABCABCABC
```

### 输出

```
0```

# 题解

## 作者：piggymichael (赞：2)

先求各个大写字母的数量，然后再算前k个大写字母的最小值，每个大写字母都选出这个最小值的数量组成的子序列是一定存在的，就输出这个最小值乘以大写字母的个数。

上代码：
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
int n,k,a[30],minn=0x3f3f3f3f;
string s;
int main()
{
	cin>>n>>k>>s;//输入
	for(int i=0;i<s.size();++i)
		a[s[i]-'A'+1]++;//统计每个大写字母各有多少个
	for(int i=1;i<=k;++i)
		minn=min(minn,a[i]);//求最小值
	cout<<minn*k<<endl;//输出
	return 0;
}
```


---

## 作者：togeth1 (赞：0)

## [题 目 传 送 门](https://www.luogu.com.cn/problem/CF1038A)

### **[题意解析]**
让我们找包含字母表前 $k$ 个大写字母且数量相同的子序列最长是多少，而我们要注意。

+ 对于一个子序列 $\verb!ABFCD!$ 中 $\verb!ABCD!$ 也是其中一个子序列，这说明了，**子序列不一定要连续**！！！~~我这个蒟蒻在这栽了跟头。~~

### **[思路分析]**
理清了题目的思路以及知道了注意事项，那这道题就成了~~大水题~~。我们只需要统计出各个大写字母的个数，然后求出前 $k$ 个字母中的最小出现次数，再用这个值乘以 $k$ 就能求出最长子序列是多少了。

### **[贴上代码]**
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a[10010],ans=0x3f3f3f;
/*设初值*/
char s[10010];
int main()
{
    cin>>n>>k>>(s+1);
    int n=strlen(s+1);
    for(int i=1; i<=n; i++)a[s[i]-'A'+1]++;
    /*统计每个字母的出现次数*/
    for(int i=1; i<=k; i++)//前 k 个哦 
    	ans=min(ans,a[i]);
    /*算出最小次数*/ 
    cout<<ans*k;
    return 0;
}
```


---

## 作者：Sternenlicht (赞：0)

思路：桶。

用一个桶记录 $s$ 中每个字符出现的次数，在前 $k$ 个字符中寻找最少的出现次数，记为 $ans$。

因为 $ans$ 是前 $k$ 个字符中最少的出现次数，所以另外的 $k-1$ 个字符的出现次数一定 $\ge ans$，即必能构成每个字符出现次数为 $ans$ 的子序列，输出 $ans \times k$ 即可。

```cpp
#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
//快读快写模板 
namespace IO{
	#define LL long long
	inline LL read(){
		LL x=0,f=1;char c=getchar();
		for (;!isdigit(c);c=getchar())if (c=='-')f=-1;
		for (;isdigit(c);c=getchar())x=(x<<3)+(x<<1)+(c^48);
		return x*f;
	}
	inline void write(LL x,char c='\n'){
		if (x){
			if (x<0)x=-x,putchar('-');
			char a[30];short l;
			for (l=0;x;x/=10)a[l++]=x%10^48;
			for (l--;l>=0;l--)putchar(a[l]);
		}else putchar('0');putchar(c);
	}
}using namespace IO;
using namespace std;

int n,k,ans=INF,tong[30]; 
string s;
int main(){
	n=read(),k=read();cin>>s;
	for (int i=0;i<s.size();i++)
		tong[s[i]-'A'+1]++;//记录s中每个字符出现的次数 
	for (int i=1;i<=k;i++)
		ans=min(ans,tong[i]);//记录前k个字符中最少的出现次数 
	//ans是前k个字符中最少的出现次数，所以另k-1个字符出现次数一定>=ans
	//即一定可以与出现次数最少的字符构成子序列，乘k即为答案 
	write(ans*k);
	return 0;
}
```

---

## 作者：abensyl (赞：0)

原题：[原题传送门](https://www.luogu.com.cn/problem/CF1038A)

## 思路

~~我sort一下就飞了！~~

- 由题意得，我们选择的字符不一定是从字符串头或从字符串最后的，所以我们可以断章取义。

- 所以我们的做法是：

- 1. 读入字符串。

- 2. 统计每个字母出现的次数。

- 3. 将字母表前 $k$ 个字母出现的次数排序（sort）。

- 4. 输出出现次数最少的字母乘以 $k$。

- 5. 输出答案

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 3;
string s;
int cnt[26];  //定义

void solve() {
  memset(cnt, 0, sizeof cnt);
  int n, k;
  cin >> n >> k;
  cin >> s;  //读入
  for (unsigned long long i = 0; i < s.size(); ++i) {  //计数
    char c = s[i];
    if (isupper(c)) {
      int ch = c - 'A';
      cnt[ch]++;
    }
  }
  sort(cnt, cnt + k);  //排序
  cout << cnt[0] * k;  //计算+输出
}

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  std::cout.tie(0);
  solve();
  return 0;  //完美结束
}
```


我的AC记录：[AC记录](https://www.luogu.com.cn/record/82657959)

---

## 作者：CH30S (赞：0)

思路：

先用数组存储各个大写字母的数量，再计算前 k 个字母的最小值。(如题) 
由于每个大写字母都选出此最小值的数量后组成的子序列一定存在(显然)
所以我们最后输出这个最小值乘以大写字母数量就是长度了。


------------


细节发在代码里了。

```c

#include<bits/stdc++.h>
using namespace std;
int ans,n,k,x=1e8,a[30];//数组开大一点 
string s;

int mn(int x,int y){
	if(x>y)x=y;
	else x=x;
} 

//手写求最小值的函数
//优点更快 

int main(){
	cin>>n>>k>>s;//输入 
	for(int i=0;i<n;i++){
		a[s[i]-'A']++;//记录各个大写字母的个数 
	}
	for(int i=0;i<k;i++){
		x=mn(x,a[i]);//前k个字母的最小值
	}
	ans=x*k;//小值乘上大写字母数量即为答案
	cout<<ans<<endl;//输出
    return 0;//done
}
```


---

## 作者：ckk11288 (赞：0)

题目不是很难，我们只需要理清思路就可以了：先用数组存储各个大写字母的数量，再计算前 k 个字母的最小值。

因为每个大写字母都选出此最小值的数量后组成的子序列一定存在，所以我们最后输出这个最小值乘以大写字母数量就行了。

**Code:**
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,x=1e9,b[28];
char s[100001];
int main()
{
	scanf("%d%d",&n,&k);
	cin>>s;
	for(int i=0;i<n;i++)
	{
		b[s[i]-'A']++;//用数组存储各个大写字母的个数
	}
	for(int i=0;i<k;i++)
	{
		x=min(x,b[i]);//求前k个字母的最小值
	}
	printf("%d",x*k);//输出最小值乘上大写字母数量（k）
        return 0;//收工
}
```

---

## 作者：flora715 (赞：0)

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#include<deque>
#include<cmath>
using namespace std;
typedef unsigned long long ll;

/*【A.Equality】
给你一个含有n个字符的字符串，该字符串由字母表的前k个字母随意组合而成。
求这个字符串中从A到A+K-1个字符中最少的那个字母的数量乘以k。*/

int a[27],n,k,ans=1e8;

int main(){
    string s; cin>>n>>k>>s;
    for(int i=0;i<n;i++) a[s[i]-'A']++;
    for(int i=0;i<k;i++) ans=min(ans,a[i]);
    cout<<ans*k<<endl; return 0;
}
```

---

