# Largest Beautiful Number

## 题目描述

如果一个正整数在十进制表示法下，不含前导零，有偶数个数字，并且对于它的所有数字来说，有一种排列方式使得这些数字组成一个回文数，那么这个数就是“美丽数”。例如4242是一个美丽数，因为它含有4个数字，这4个数字可以组成一个回文数2442。

给定一个正整数s，求严格小于s的最大美丽数。

## 说明/提示

t <= 10^5 
 

s的长度<= 2*10^5 

感谢@刷题永动机 提供的翻译

## 样例 #1

### 输入

```
4
89
88
1000
28923845
```

### 输出

```
88
77
99
28923839
```

# 题解

## 作者：CHK555 (赞：5)

# 解题思路
设我们得到的美丽数是 $x$

设 $x$ 与 $s$ 相同前缀的长度为 $k$

为了使我们得到的美丽数尽可能接近 $s$，我们要使得   $k$ 尽可能的大。

容易想到可以从大到小枚举 $k$，判断是否可行

我们可以从大到小枚举 $x$ 与 $s$ 第一个不同的数字的位置，同样可以达到以上的目的

我们统计前 $k+1$ 位中(算上第一个不同的数字)，出现次数为奇数的数字的个数，然后后面必须要各出现一次

设要填 $x$ 个数

若 $x>n-(i+1)+1$，则不合法，继续枚举位置

否则将这 $x$ 个数从大到小填入 $[n-x+1,n]$ 这段区间中

然后剩余的位置填9即可，容易发现剩余的位置的数量定为偶数

合法性自证不难

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 200005
int n,m,sum[N][10];
char s[N];
void solve(){
	for(int i=n;i>=1;i--){
		for(int j=s[i]-'0'-1;j>=0;j--){
			if(i==1&&j==0)continue;
			int now=0;
			for(int k=0;k<10;k++)now+=sum[i-1][k]^(j==k);
			if(now<=n-i){
				for(int k=1;k<i;k++)putchar(s[k]);
				putchar(j+'0');
				for(int k=i+1;k<=n-now;k++)putchar('9');
				for(int k=9;k>=0;k--)
					if(sum[i-1][k]^(j==k))putchar(k+'0');
				puts("");
				return;
			}
		}
	}
	for(int i=1;i<=n-2;i++)putchar('9');
	puts("");
}
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%s",s+1);n=strlen(s+1);
		for(int i=1;i<=n;i++){
			int id=s[i]-'0';
			for(int k=0;k<10;k++)
				sum[i][k]=sum[i-1][k]^(id==k);
		}
		solve();
	}
}
```

---

