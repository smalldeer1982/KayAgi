# Strange Test

## 题目描述

Igor is in 11th grade. Tomorrow he will have to write an informatics test by the strictest teacher in the school, Pavel Denisovich.

Igor knows how the test will be conducted: first of all, the teacher will give each student two positive integers $ a $ and $ b $ ( $ a < b $ ). After that, the student can apply any of the following operations any number of times:

- $ a := a + 1 $ (increase $ a $ by $ 1 $ ),
- $ b := b + 1 $ (increase $ b $ by $ 1 $ ),
- $ a := a \ | \ b $ (replace $ a $ with the [bitwise OR](https://en.wikipedia.org/wiki/Bitwise_operation#OR) of $ a $ and $ b $ ).

To get full marks on the test, the student has to tell the teacher the minimum required number of operations to make $ a $ and $ b $ equal.

Igor already knows which numbers the teacher will give him. Help him figure out what is the minimum number of operations needed to make $ a $ equal to $ b $ .

## 说明/提示

In the first test case, it is optimal to apply the third operation.

In the second test case, it is optimal to apply the first operation three times.

In the third test case, it is optimal to apply the second operation and then the third operation.

## 样例 #1

### 输入

```
5
1 3
5 8
2 5
3 19
56678 164422```

### 输出

```
1
3
2
1
23329```

# 题解

## 作者：XL4453 (赞：9)

### 解题思路：

由于按位或的操作只能由 $a$ 完成，所以当 $a>b$ 时，只能将 $b$ 不停地加到 $a$ 为止。

否则将 $a$ 或 $b$ 一直增加到相等或着 $a$ 按位或后相等，由于数值范围很小，直接暴力枚举就行了。

---
第二段的证明想了好久，差点没整出来。

当 $a>b$ 的时候，由于 $a|b\ge a$，而且没有让 $a$ 变小的方法，所以只能让 $b$ 增加，那么不取或而直接将 $b$ 增加是最好的选择。

问题就在于 $a<b$ 的时候。先排除在取或后再增加 $a$，由于 $a|b\ge b$，此时如果再将 $a$ 增加毫无意义。

所以只有在取或后增加 $b$ 的可能性，可以分每一个二进制位考虑，这里将操作二抽象为增加任意一个数 $x$，同时消耗 $x$ 的代价。由于首要要求是相等而非代价最小，当 $a$ 的某一位为 $0$，同时 $b$ 的相应为 $0$ 时，取或后依然相等，不需要花任何代价，同理有 $1$ 和 $1$，$0$ 和 $1$。

唯一需要讨论的是 $a$ 为 $1$ 而 $b$ 为 $0$，此时取完或还是不变的，需要消耗一定的代价使得 $b$ 增大到和 $a$ 相等，具体消耗的代价视二进制位的位置和后面的数而定。

此时~~不容易~~发现，如果在取或后增加，在考虑玩之后位的所有这种同样的情况之后发现这样的代价直接是这个二进制位的本身的权值，但是如果不先取或直接增加的话，后面的位置上如果存在  $a$ 为 $0$，而 $b$ 为 $1$ 的情况的话就能相应地减少代价。

结合抽象化的操作可知这样的操作并不会影响到其它的任何位，也就是独立的。

---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int a,b,T,x,y,ans,cnt;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&a,&b);
		if(a>=b){
			printf("%d",a-b);
			continue;
		}
		ans=2147483647;
		cnt=0;
		x=a;y=b;
		while((x|y)!=y){
			x++;
			cnt++;
		}
		if(x!=y)cnt++;
		ans=min(ans,cnt);
		
		cnt=0;
		x=a;y=b;
		while((x|y)!=y){
			y++;
			cnt++;
		}
		if(x!=y)cnt++;
		ans=min(ans,cnt);
		
		printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：Na2PtCl6 (赞：2)

### 分析
想让 $a$ 与 $b$ 相等，我们可以把 $a$ 加上一定的值，令其为 $a'$ ，再给 $b$ 加上一个与之相适应的值，使得 $a'|b=b$。

对于把 $a$ 加到多少，我们暴力就行。

把 $b$ 加到多少，就要在二进制下按位分析按位分析。比如样例中的最后一组数据

```
a:   1101 1101 0110 0110
b:10 1000 0010 0100 0110
```
我们从低到高枚举每一位。

对于 $a_i=1$ 的情况，如果 $b_i=0$，就要给 $b$ 加上一个数，但显然直接把 $b_i$ 变成 $1$ 很可能不是最优的。因为对于 $a_j=0$ 的
情况， $b_j$ 的值是任意的，所以如果 $b_j=1$ 就可以在 $b$ 更高位需要从 $0$ 变 $1$时，把 $b_j$ 变为 $0$ 。 

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
char f=1,a2[32],b2[32];
int t,a,b,cnta,cntb,res,ta,tb;

int calc(int ta){
	int ans,suf;	
	suf=ans=cntb=cnta=0;
	while(ta>0){
		a2[++cnta]=ta&1;
		ta>>=1;
	}
	for(int i=1;i<=cnta;i++){
		if(a2[i]==0)
			suf+=b2[i]<<(i-1);
		if(b2[i]==0&&a2[i]==1){
			ans+=(1<<(i-1))-suf;
			suf=0;
		}
		
	}
	memset(a2,0,sizeof(a2));
	return ans+1;
}

int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d %d",&a,&b);
		res=b-a;
		tb=b;
		while(tb>0){		
			b2[++cntb]=tb&1;
			tb>>=1;
		}
		for(int i=a;i<=b;i++){
			res=min(res,i-a+calc(i));
			f=0;
		}
		printf("%d\n",res);
		memset(b2,0,sizeof(b2));
	}
	return 0;
	
}
```

---

## 作者：OIerZhang (赞：0)

# [CF1632C Strange Test](https://www.luogu.com.cn/problem/CF1632C)

## 思路

首先，我们来分析一下这道题适合用什么复杂度。由于 $\sum b \le 10^6$，而 $a$ 和 $b$ 最多用 $10^6$ 次加一操作就能相等，所以本题可以用 $O(n)$ ~~暴力大法~~解决。

但是怎么暴力呢？我们再分析一下按位或的特点。例如有两个数分别为 $(1110010)_2$ 和 $(1000000010)_2$，它们按位或的结果是 $(1001110010)_2$。可见，只要按位或后某一位有至少一个数对应的位为 $1$，这一位就不可能为 $0$。换句话说，$a \lor b \ge a (a \ge b)$。这意味着，“先按位或再加”一定不比“先加再按位或”更优。

综上，我们只需要枚举“先加 $a$ 再按位或”和“先加 $b$ 再按位或”两种情况即可。

## 核心代码

```cpp
ta = a, tb = b;
while ((ta | tb) != tb) // 小坑：“!=” 比 “|” 优先
    ta++, cnta++;
if (ta != tb) cnta++;
ta = a, tb = b;
while ((ta | tb) != tb)
    tb++, cntb++;
if (ta != tb) cntb++;
cout << min(cnta, cntb) << endl;
```

---

