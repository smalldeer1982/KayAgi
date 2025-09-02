# Bits Are Dangerous

## 题目描述

[problemUrl]: https://atcoder.jp/contests/jag2015summer-day3/tasks/icpc2015summer_day3_b



# 题解

## 作者：xQWQx (赞：6)

### 前置

[题目链接](https://www.luogu.com.cn/problem/AT_icpc2015summer_day3_b)

[AC 记录](https://www.luogu.com.cn/record/170824603)

### 思路

因为每一次异或 $1$ 只能改变最后一位，所以我们可以直接循环枚举，同时枚举循环左移和循环右移，最后输出最小值。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int cnt=0,sum=10000005;
int n;
int main(){
    string s;
    cin>>s;//输入
    n=s.size();
    for(int i=0;i<s.size();i++){
        if(s[i]=='1') cnt++;//看一看一共有多少个1
    }
    int i=1,j=n;
    string g=s+s;
    //为了方便枚举，可以将序列复制一次，这样就做到了"循环"
    for(int t=0;t<=cnt;t++){
        //因为最大的左移或右移次数取决于两个1之间的最大长度所以枚举cnt次
        while(g[i]=='0') i++;//左移
        while(t!=0&&g[j]=='0') j++;//右移
        int a=max(0,n-i);//保存
        int b=j-n;
        sum=min(sum,min(a,b)+a+b);//取最小
        i++,j++;
    }
    cout<<cnt*4+sum*7;
    //输出，因为有cnt个1，所以乘4，距离为sum，所以乘7
    return 0;
}

```

---

## 作者：_xdd_ (赞：1)

操作一的异或 $1$ 只改变第一位，如果第一位是 $1$ 则进行操作一，这样就可以把第一位变成 $0$。所以只需要看怎样能**先**遍历到所有 $1$，这个遍历的花费取决于两个 $1$ 之间的最大长度，最后加上异或花费（即 $1$ 的个数 $ \times 4$）就可以了，可以做到 $\mathcal{O}(n)$ 的复杂度。

注意这组数据：`1100011`，如果只向左或向右遍历都要移动 $6$ 步，但正解应该是先向左移动一步，再向右移动四步（也就是“回头”），为了方便枚举，可以将序列复制一次，这样就做到了“循环”。

---

## 作者：HsNu1ly7_ (赞：0)

## 题意

给你一个字符串 $s$，有两种操作：

1. 每次可以将 $s_1$ 异或 $1$，花费 $4$ 的代价。

2. 将 $s$ 循环左移一位或循环右移一位，花费 $7$ 的代价。

问你最少需要多大的代价将 $s$ 变成全 $0$ 串。

## 思路

由于只有异或才能改变字符串的 $01$ 的数量，所以我们只需枚举每个 $1$ 通过循环左移或循环右移到达 $s_1$ 这个位置时的最小代价即可。

代码如下：


```cpp
#include <bits/stdc++.h>
using namespace std ;
#define int long long

int read(){int x=0,f=1; char cha=getchar(); while(cha<'0'||cha>'9'){if(cha=='-'){f=-1; } cha=getchar(); } while(cha>='0'&&cha<='9'){x=x*10+(cha-'0'); cha=getchar(); } return x*f; }
void write(int x){if (x<0){putchar('-'); x=-x; } int sta[68]={},top=0; do{sta[top++]=x%10; x/=10; }while(x); while(top)putchar(sta[--top]+48); }
string s ;
int tot = 0 ;
int ans = 0x3f3f3f3f ;
signed main (){
	cin >> s ;
	int len = s.length() ;
	for (int i = 0 ; i < len ; i++){
		tot += ( s[i] == '1' ) ;
	}
	s += s ;
	int l = 1 , r = len ;
	for (int i = 0 ; i <= tot ; i++){
		while ( s[l] == '0' ) ++l ;
		while ( s[r] == '0' && i ) ++r ;
		int S = r - len ;
		int t = max ( 0ll , len - l ) ;
		ans = min ( {ans , min ( S , t ) + t + S } ) ;
		++l ;
		++r ;
	}
	write ( tot * 4 + ans * 7 ) ;
	return 0 ;
}
```

---

