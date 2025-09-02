# 题目信息

# Binary Median

## 题目描述

Consider all binary strings of length $ m $ ( $ 1 \le m \le       60 $ ). A binary string is a string that consists of the characters 0 and 1 only. For example, 0110 is a binary string, and 012aba is not. Obviously, there are exactly $ 2^m $ such strings in total.

The string $ s $ is lexicographically smaller than the string $ t $ (both have the same length $ m $ ) if in the first position $ i $ from the left in which they differ, we have $ s[i] < t[i] $ . This is exactly the way strings are compared in dictionaries and in most modern programming languages when comparing them in a standard way. For example, the string 01011 is lexicographically smaller than the string 01100, because the first two characters are the same, and the third character in the first string is less than that in the second.

We remove from this set $ n $ ( $ 1 \le n \le \min(2^m-1,       100) $ ) distinct binary strings $ a_1, a_2, \ldots, a_n $ , each of length $ m $ . Thus, the set will have $ k=2^m-n $ strings. Sort all strings of the resulting set in lexicographical ascending order (as in the dictionary).

We number all the strings after sorting from $ 0 $ to $ k-1 $ . Print the string whose index is $ \lfloor       \frac{k-1}{2} \rfloor $ (such an element is called median), where $ \lfloor x       \rfloor $ is the rounding of the number down to the nearest integer.

For example, if $ n=3 $ , $ m=3 $ and $ a=[ $ 010, 111, 001 $ ] $ , then after removing the strings $ a_i $ and sorting, the result will take the form: $ [ $ 000, 011, 100, 101, 110 $ ] $ . Thus, the desired median is 100.

## 说明/提示

The first test case is explained in the statement.

In the second test case, the result after removing strings and sorting is $ [ $ 001, 010, 101, 110 $ ] $ . Therefore, the desired median is 010.

## 样例 #1

### 输入

```
5
3 3
010
001
111
4 3
000
111
100
011
1 1
1
1 1
0
3 2
00
01
10```

### 输出

```
100
010
0
1
11```

# AI分析结果

### 题目内容中文重写
# 二进制中位数

## 题目描述
考虑所有长度为 $m$（$1 \le m \le 60$）的二进制字符串。二进制字符串是仅由字符 0 和 1 组成的字符串。例如，0110 是一个二进制字符串，而 012aba 不是。显然，总共有 $2^m$ 个这样的字符串。

字符串 $s$ 在字典序上小于字符串 $t$（两者长度均为 $m$），如果从左起第一个不同的位置 $i$ 处，有 $s[i] < t[i]$。这正是字典中比较字符串的方式，也是大多数现代编程语言中标准的字符串比较方式。例如，字符串 01011 在字典序上小于字符串 01100，因为前两个字符相同，而第一个字符串的第三个字符小于第二个字符串的第三个字符。

我们从这个集合中移除 $n$（$1 \le n \le \min(2^m - 1, 100)$）个不同的二进制字符串 $a_1, a_2, \ldots, a_n$，每个字符串的长度均为 $m$。这样，集合中就剩下 $k = 2^m - n$ 个字符串。将结果集合中的所有字符串按字典序升序（即字典中的顺序）排序。

我们将排序后的所有字符串从 0 到 $k - 1$ 编号。打印索引为 $\lfloor \frac{k - 1}{2} \rfloor$ 的字符串（这样的元素称为中位数），其中 $\lfloor x \rfloor$ 是将数字向下取整到最接近的整数。

例如，如果 $n = 3$，$m = 3$ 且 $a =$ [010, 111, 001]，那么移除字符串 $a_i$ 并排序后，结果将是：[000, 011, 100, 101, 110]。因此，所需的中位数是 100。

## 说明/提示
第一个测试用例在题目描述中已经解释过。

在第二个测试用例中，移除字符串并排序后的结果是 [001, 010, 101, 110]。因此，所需的中位数是 010。

## 样例 #1
### 输入
```
5
3 3
010
001
111
4 3
000
111
100
011
1 1
1
1 1
0
3 2
00
01
10
```

### 输出
```
100
010
0
1
11
```

### 算法分类
模拟

### 综合分析与结论
这些题解的核心都是围绕模拟删除二进制字符串并找出剩余字符串的中位数展开。不同题解在具体实现上有所差异，但大致思路可分为两类：一类是直接模拟删除过程，在删除过程中维护中位数；另一类是先确定最终中位数的位置，再根据删除的数与该位置的关系进行调整。

### 所选题解
- 作者：暗ざ之殇 (赞：10)，4星
  - 关键亮点：思路清晰，通过确定最终中位数的位置，避免了在删除过程中复杂的中位数维护。利用规律判断删除的数对中位数位置的影响，简化了计算过程。
  - 个人心得：特别鸣谢 [一扶苏一](https://www.luogu.com.cn/user/65363) 帮我 $debug$。
- 作者：蒟酱 (赞：2)，4星
  - 关键亮点：代码简洁，使用 `bitset` 处理二进制输入，提高了代码的可读性。通过枚举元素并结合排序，巧妙地计算出中位数。
- 作者：Dovе (赞：1)，4星
  - 关键亮点：思路明确，先计算出删除后中位数的位置，再根据删除的数与中位数的大小关系进行调整，最后将结果转换为二进制输出。

### 重点代码
#### 暗ざ之殇的代码
```cpp
#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int T,n,m,cnt;
long long len,mid;
long long delet[1500];
bool read()              //读入单个数字 
{
	char ch=getchar();
	while(ch!='0'&&ch!='1') ch=getchar();
	return ch^48;
}
int check(long long x)   //查找x是否在delet数组里 
{
	return delet[lower_bound(delet+1,delet+1+cnt,x)-delet]==x;  //lower_bound偷懒qwq 
}
void work()
{
	for(long long i=mid+1;i<=len;i++)
	{
		if(!check(i))    //判断i是否被删除 
		{
			mid=i;       //没有被删除就来当mid 
			return ;
		}
	}
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d %d",&n,&m);
		len=1ll<<m;                  //len是初始数的个数 
		mid=(len-n+1)/2-1;           //删除一些数之后的中位数的位置上的数现在是几 
		memset(delet,0,sizeof(delet));
		cnt=0;                       //记录删除的数中有多少个数比mid大 
		for(int i=1;i<=n;i++)        
		{
			long long a=len/2;   
			long long num=0;         //num是转化为十进制之后的数 
			for(int j=1;j<=m;j++)    //二进制转化为十进制 
			{
				int x=read();
				if(x) num+=a;
				a/=2;
			}
			if(num>mid) delet[++cnt]=num;   //只需记录所有比mid大的数 
		}
		sort(delet+1,delet+1+cnt);   //从小到大排序,便于二分查找 
		for(int i=1;i<=n-cnt;i++)    //总共有n-cnt个数小于等于mid,就要右移n-cnt次 
		    work();
		len/=2;    
		while(len)                   //十进制转化为二进制 
		{
			if(mid>=len) 
			{
				printf("1");
				mid-=len;
			}
			else printf("0");
			len/=2;
		}
		printf("\n");
	}
	return 0;
}
```
核心实现思想：先计算出初始数的个数和删除后中位数的位置，然后将删除的数中比中位数大的数记录下来并排序。对于比中位数小的数，通过右移操作更新中位数的位置，最后将中位数转换为二进制输出。

#### 蒟酱的代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<bitset>
using std::cin;using std::cout;
using lolu=unsigned long long;
constexpr int N=101;
int n,m;
lolu a[N];
std::bitset<64>num;
signed main(){
	std::ios::sync_with_stdio(false);cin.tie(nullptr);
	int T;cin>>T;while(T--){
		cin>>n>>m;
		lolu mid=((1ull<<m)-n-1)/2;
		for(int i=1;i<=n;i++)cin>>num,a[i]=num.to_ullong();
		std::sort(a+1,a+n+1);
		for(int i=1;i<=n;i++)if(a[i]>mid)break;else mid++;
		num=mid;
		for(int i=m-1;~i;i--)cout<<num[i];
		cout<<'\n';
	}
	return 0;
}
```
核心实现思想：使用 `bitset` 读取二进制输入并转换为十进制，计算出初始中位数的位置。对删除的数进行排序，枚举删除的数，若小于等于中位数则将中位数加 1，最后将中位数转换为二进制输出。

#### Dovе的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=60+50;
int n,m;
int a[maxn];
signed main()
{
	int T;
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld%lld",&n,&m);
		int mid=((1ll<<m)-n-1)/2;
		for(register int i=1;i<=n;++i)
		{
			string s; cin>>s;
			int Ans_=0;
			for(register int j=0;j<s.length();++j)
			  if(s[j]=='1') Ans_+=1ll<<m-j-1;
			a[i]=Ans_; // 将删除的数转成十进制
		}
		sort(a+1,a+n+1);
		
		for(register int i=1;i<=n;++i)
		  if(a[i]>mid) break;
		  else mid++; // 处理 mid
		 
		vector<int> res;
		
		while(mid)
		{
			res.push_back(mid%2);
			mid/=2;
		} 
		reverse(res.begin(),res.end()); // 将 mid 转为 二进制
        
		for(register int i=1;i<=m-res.size();++i) printf("0");
		for(register int i=0;i<res.size();++i) printf("%d",res[i]);
		printf("\n"); // 输出答案
	}
	return 0;
 } 
```
核心实现思想：计算出删除后中位数的位置，将删除的数转换为十进制并排序。遍历删除的数，若小于等于中位数则将中位数加 1，最后将中位数转换为二进制并补齐前导 0 输出。

### 最优关键思路或技巧
- **确定最终中位数位置**：避免在删除过程中复杂的中位数维护，直接根据删除的数与最终中位数位置的关系进行调整。
- **使用 `bitset`**：方便处理二进制输入，提高代码的可读性。
- **排序与二分查找**：对删除的数进行排序，利用二分查找判断某个数是否已被删除，提高查找效率。

### 拓展思路
同类型题可能会改变数据范围或增加其他条件，例如：
- 增加删除操作的次数，需要考虑更高效的算法。
- 改变中位数的定义，如求第 $k$ 小的数。
- 增加字符串的长度，需要处理大整数问题。

### 推荐洛谷题目
- P1059 [NOIP2006 普及组] 明明的随机数
- P1177 [模板] 快速排序
- P1271 [深基9.例1] 选举学生会

---
处理用时：78.62秒