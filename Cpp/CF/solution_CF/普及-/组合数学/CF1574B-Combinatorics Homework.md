# Combinatorics Homework

## 题目描述

You are given four integer values $ a $ , $ b $ , $ c $ and $ m $ .

Check if there exists a string that contains:

- $ a $ letters 'A';
- $ b $ letters 'B';
- $ c $ letters 'C';
- no other letters;
- exactly $ m $ pairs of adjacent equal letters (exactly $ m $ such positions $ i $ that the $ i $ -th letter is equal to the $ (i+1) $ -th one).

## 说明/提示

In the first testcase strings "ABCAB" or "BCABA" satisfy the requirements. There exist other possible strings.

In the second testcase there's no way to put adjacent equal letters if there's no letter that appears at least twice.

In the third testcase string "CABBCC" satisfies the requirements. There exist other possible strings.

## 样例 #1

### 输入

```
3
2 2 1 0
1 1 1 1
1 2 3 2```

### 输出

```
YES
NO
YES```

# 题解

## 作者：猫猬兽 (赞：4)

### CF手速场B题，思维题
## 题意
给出 $a,b,c,m$,表示 $a$ 个 $A$，$b$ 个 $B$，$c$ 个 $C$ 组成的字符串，问是否存在一个串使得相邻两字符相同的对数为 $m$ 对。
## 思路
考虑直接构造较难，我们求出给定 $a,b,c$,求出符合条件的上界和下界，再判断。
### 上界
显然相同字符放一起最优，此时上界为 $a+b+c-3$。
### 下界
先求出最多的字符，假设为 $A$，然后 $ABABAB...ACACAC..AAA$ 这样构造，此时下界为 $max(0,a-b-c-1)$。


## 代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
long long t,a,b,c,m,i;
int main()
{
    scanf("%lld",&t);
    for(i=1;i<=t;i=i+1)
    {
    	scanf("%lld%lld%lld%lld",&a,&b,&c,&m);
    	if(a<b)swap(a,b);
    	if(b<c)swap(b,c);
    	if(a<b)swap(a,b);
    	if(m<=a+b+c-3&&m>=a-b-c-1)printf("YES\n");
    	else printf("NO\n");
	}
    return 0;
}

```
完结撒花

---

## 作者：一E孤行 (赞：1)

我们考虑这样构造字符串：

`aaabbbccc` 和 `abcabcabc` 很显然，对于相邻两个字符相等不相等的贡献，第一个最大，第二个最小。

那么，我们先对输入的 $a,b,c$ 排序，使得 $c\leq b \leq a$，那么，最多的贡献是 $a+b+c-3$，最小的贡献是 $a-b-c-1$ （最小值很好理解，最大值是这样的： $a$ 个数最多有 $a-1$ 个相同的，所以同理扩展到 $b,c$）。

此时，如果 $m$ 在最大值和最小值的区间内，则一定可以构造成功。


```cpp
#include<cstdio>
#include<algorithm>
#include<queue>
#include<iostream>
#include<cstring>
#include<ctime>
#include<cmath>
using namespace std;
bool cmp(int x,int y) {
    return x>y;
}
int a[20],m;
int main() { 
    int c1=clock();
#ifdef LOCAL
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
#endif
    //=========================================
     int T;
     scanf("%d",&T);
     while(T--) {
        //  int  a,b,c,m;
        //  int x,y,z;
        //  scanf("%d%d%d%d",&a,&b,&c,&m);
        //  x=a,y=b,z=c;
        //  int sum=a+b+c;
        //  a=max(x,max(y,z));
        //  c=min(x,min(y,z));
        //  b=sum-a-c;
         scanf("%d%d%d%d",&a[1],&a[2],&a[3],&m);
         sort(a+1,a+4,cmp);
         if(m<=a[1]+a[2]+a[3]-3 && a[1]-a[2]-a[3]-1 <= m) puts("YES");
         else puts("NO");
     }
    //=========================================
    cerr<<"Tmie Used:"<<clock()-c1<<"ms"<<endl;
    return 0;
}

```

---

## 作者：wheneveright (赞：1)

## 题意

给出 $T$ 个 $a, b, c, m$，表示有 $a$ 个 `A`、$b$ 个 `B`、$c$ 个 `C`，问是否存在一个由这些字符组成的排列使得相邻两个数相同的个数为 $m$ 个。

## 解析

这题我居然花了半个多小时。

下面假设 $a, b, c$ 有序。

首先可以想到如果 $m = 0$ 时的判断条件：$c - 1 \le a + b$，就是把 $c$ 个 `C` 中插入 `A` 或者 `B`。

然后想到相邻两个相同可以捆绑成同一个，也就是相对应的字符数量减一。

那么肯定是减去最大的数最优，然后就是贪心的想法，先把最大的减掉使得 $b = c$ 如果 $m \not = 0$ 那就再把这两个同时减去，如果 $a = b = c$ 且 $m \not = 0$ 的话，那就三个数字一起减，过程中满足三个数字有序。

## 代码

写的有点繁琐，不过思路是清晰的。

```cpp
# include <bits/stdc++.h>
using namespace std;
 
int T;
int a, b, c, m;
 
int main () {
	cin >> T;
	while (T--) {
		cin >> a >> b >> c >> m;
		if (a > b) swap (a, b);
		if (b > c) swap (b, c);
		if (a > b) swap (a, b);
		int t = min (c - b, m);
		c -= t; m -= t; // 这里是找到最大的数和 m 尽可能减
		if (m) {
			// 如果不行的话就把 b c 一起减
			t = min ((b - a), m / 2);
			b -= t; c -= t; m -= t * 2;
			if (m) {
				if (a != b) { b--; m--; }
				else {
					t = min (a, m / 3);
					a -= t; b -= t; c -= t; m -= t * 3;
					if (m) m--, a--;
					if (m) m--, b--;
				}
				// 还不行就三个一起减
			}
		}
		// 因为输入都是大于等于 1 的，存在 0 就说明无解
		puts (a + b >= c - 1 && a && b && c ? "YES" : "NO");
	}
	return 0;
}
```

---

## 作者：yangzd (赞：0)

## 题目大意:

给定 $a , b , c$ 分别为字母 $A , B , C$ 的数量，$m$ 为前后字母相等的字母对的个数。问是否能够构造出满足 $m$ 的字符串，字母必须全部用完。

## 分析:

这题是思维题，因为这题要我们判断，是否有正好m对，我们先算出 $cnt 1$ 最多可以组成多少对，再算出 $cnt 2$ 最少可以组成多少对，当 $m$ 介于两者之间时，一定存在正好 $m$ 对的情况，否则一定不存在

而由于三种字符最多可以组成的对数各为 $a - 1,b - 1 , c - 1$ 对，所以 $ cnt 1 = a + b + c - 3$。

最少的情况我们这么考虑，假设 $A$ 的数量最多，而本来 $A$ 可以组成 $a - 1$ 对，而当我们在每两个 $A$ 间都插入一个 $B$ 或一个 $C$ 后，对子数就变为最少，变为 $a - 1 - b - c$ 对，当然这个答案可能是负的，但是当答案是负的的情况表示可以一个对子都没有，那么这种情况我们把 $cnt 2$ 置为 $0$ ，表示有 $0$ 个对子就好了。当然，这只是 $A$ 最多的情况，当 $B$ 最多或者 $C$ 最多的情况同理，只要判断一下谁最多就好了。

## 代码:

```cpp
#include<bits/stdc++.h>
using namespace std;

signed main()
{
	ios::sync_with_stdio(0);
	
    int t;
    
    cin >> t;
    
    while (t--)
	{
        int a[3],m;
        
        cin >> a[0] >> a[1] >> a[2] >> m;
        
        sort(a,a+3);
        
        int sum=a[0]+a[1]+a[2];
        int ma,mi;

        mi=sum-(a[0]+a[1])*2-1;
        mi=max(mi,0);
        ma=sum-3;
        
        if(m>=mi && m<=ma)
            cout << "YES" << endl;
            
        else
        	cout << "NO" << endl;
    }
    
    return 0;
}
```

---

## 作者：Xhesika_Frost (赞：0)

考虑对于给定的 $a,b,c$ 最多能得到多少个对和最少多少个对

如果要得到最多的，那么就应该排成 $aaabbbccc$ 这样让相同的字母相邻，
这样可以得到共 $a+b+c-1$ 个

那么最少呢，可以想到应该排列成 $abcabcbcbc$这样交替排列的

那么对于 $a,b,c$ 我们假设 $a>b>c$ 的话，就最少可以得到 $a-b-c-1$ 个对

这样我们只要检查 $m$ 是否在这个范围就可以了

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int a[5];
int m;
int t; 
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d%d%d",&a[1],&a[2],&a[3],&m);
		sort(a+1,a+4);
		if(m<=a[1]+a[2]+a[3]-3&&a[3]-a[2]-a[1]-1<=m){
			printf("YES\n");
		}else{
			printf("NO\n");
		}
	}
	return 0;
} 
```

---

