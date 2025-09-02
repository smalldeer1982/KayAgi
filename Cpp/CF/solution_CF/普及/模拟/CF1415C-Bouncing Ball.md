# Bouncing Ball

## 题目描述

You're creating a game level for some mobile game. The level should contain some number of cells aligned in a row from left to right and numbered with consecutive integers starting from $ 1 $ , and in each cell you can either put a platform or leave it empty.

In order to pass a level, a player must throw a ball from the left so that it first lands on a platform in the cell $ p $ , then bounces off it, then bounces off a platform in the cell $ (p + k) $ , then a platform in the cell $ (p + 2k) $ , and so on every $ k $ -th platform until it goes farther than the last cell. If any of these cells has no platform, you can't pass the level with these $ p $ and $ k $ .

You already have some level pattern $ a_1 $ , $ a_2 $ , $ a_3 $ , ..., $ a_n $ , where $ a_i = 0 $ means there is no platform in the cell $ i $ , and $ a_i = 1 $ means there is one. You want to modify it so that the level can be passed with given $ p $ and $ k $ . In $ x $ seconds you can add a platform in some empty cell. In $ y $ seconds you can remove the first cell completely, reducing the number of cells by one, and renumerating the other cells keeping their order. You can't do any other operation. You can not reduce the number of cells to less than $ p $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1415C/db37e109bcbb2fc66573faa03cd327ce59fe9d9d.png)Illustration for the third example test case. Crosses mark deleted cells. Blue platform is the newly added.What is the minimum number of seconds you need to make this level passable with given $ p $ and $ k $ ?

## 说明/提示

In the first test case it's best to just remove the first cell, after that all required platforms are in their places: 0101010101. The stroked out digit is removed, the bold ones are where platforms should be located. The time required is $ y = 2 $ .

In the second test case it's best to add a platform to both cells $ 4 $ and $ 5 $ : 00000 $ \to $ 00011. The time required is $ x \cdot 2 = 4 $ .

In the third test case it's best to to remove the first cell twice and then add a platform to the cell which was initially $ 10 $ -th: 10110011000 $ \to $ 10110011010. The time required is $ y \cdot 2 + x = 10 $ .

## 样例 #1

### 输入

```
3
10 3 2
0101010101
2 2
5 4 1
00000
2 10
11 2 3
10110011000
4 3```

### 输出

```
2
4
10```

# 题解

## 作者：wawatime1 (赞：2)

## 题目分析
我们可以通过动态规划来解决这个问题。核心思路是考虑在不同位置进行操作（删除第一个元素或添加平台）后，使得从位置 $p$ 开始，每隔 $k$ 个位置都有平台的最小花费。

- 设 $dp_i$ 表示处理到第 $i$ 个位置时，满足跳跃条件的最小花费。

### 状态转移方程推导：

- 不删除第一个元素：如果当前位置 $i$ 不需要作为跳跃路径上的平台，即 $(i - p)\bmod k$ 不等于 $0$，那么  $dp_i$ 就等于 $dp_{i - 1}$，因为不需要额外操作。如果当前位置 $i$ 需要作为跳跃路径上的平台 $(i - p) \bmod k$ 等于 $0$ 且当前位置没有平台 $a_i = 0$，则  $dp_i = dp_{i - 1} + x$，表示添加一个平台的花费；如果当前位置有平台 $a_i = 1$，则 $ dp_i = dp_{i - 1}$，不需要额外花费。

- 删除第一个元素：无论当前位置情况如何，都可以选择删除第一个元素，此时 $dp_i = dp_{i - 1} + y$。所以最终 $dp_i$ 取上述两种情况的最小值。

边界条件：

- 当 $i < p$ 时，$dp_i$ 设为一个极大值，因为不能减少到少于 $p$ 个位置。$dp_{p - 1} = 0$，表示从位置 $p$ 开始时，还未进行任何操作，花费为 $0$。

#### 最终答案：
处理完所有位置后，$dp_{n}$ 就是能合法跳出序列的最小修改花费。

---

## 作者：Schwarzkopf_Henkal (赞：1)

这题没有什么不好想的地方。

对于每一个合法位置，我们都能求出这个位置的花费，也就是让球将这个点作为第一个点开始跳并且完成所需要的花费。具体过程是，我们要求出弹跳过程中所碰到的所有方块中为空的个数，还有这个位置之前的多余方块的个数。暴力求的话复杂度是 $\mathcal{O}(n^2)$ 的。

但是我们发现，我们在求某一个位置的路径上空方块个数的时候其实已经把后面所有下标膜 $k$ 同余的位置上的值都求出来了，这部分是不需要重复求的，总复杂度 $\mathcal{O}(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,p,K,c[100005],mk[100005],x,y,ans,res[100005];
char str[100005];
int main(){
    scanf("%d",&T);
    while(T--){
        ans=1e9;
        memset(mk,0,sizeof(mk));
        memset(res,0,sizeof(res));
        scanf("%d%d%d%s%d%d",&n,&p,&K,str+1,&x,&y);
        for(int i=1;i<=n;i++)
            c[i]=str[i]-'0';
        for(int i=p;i<=n;i++){
            if(!mk[i]){
                int j=0;
                while(K*(j+1)+i<=n)
                    j++;
                while(j>=0){
                    mk[K*j+i]=1;
                    if(c[K*j+i]==0)
                        res[K*j+i]++;
                    if(j)
                        res[K*(j-1)+i]=res[K*j+i];
                    j--;
                }
            }
            ans=min(ans,(i-p)*y+res[i]*x);
        }
        printf("%d\n",ans);
    }
}
```

---

## 作者：TEoS (赞：1)

本文同步发表在[我的blog](https://www.cnblogs.com/TEoS/p/14084101.html)


------------


**题意分析**

给出一个由 $0,1$ 组成的序列，要从第 $p$ 个位置开始，每次跳 $k$ 个单位，要求跳出序列，只有当所有经过的位置都为 $1$ 才合法。你可以花费 $x$ 将这个序列的第一个元素删除，也可以花费 $y$ 将其中一个位置改为 $1$ ，求能合法跳出序列的最小修改花费。

**思路分析**

发现当第一个位置确定后，后面的所有跳到的位置都可以确定，考虑枚举删去的元素数量，即起始位置。

显然前 $p-1$ 个元素都是无用的，可以不管它们，然后设为从第 $1$ 个位置开始。

假设删去前 $i$ 个元素，那么很容易可以得出需要跳的次数：$\left \lceil \frac{(n-i)}{k} \right \rceil$ 。然后需要知道被跳到的地方有多少个位置为 $0$ ，这个可以把整个序列按照对 $k$ 的模数进行分类，然后对于每一类预处理出为 $1$ 的个数，处理的时候再统计当前位置之前的 $1$ 的个数，就可以得出后面的 $0$ 的个数。最后加上删去 $i$ 个元素的花费即可。

```c++
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<cmath> 
using namespace std;
const int N=1e5+100;
int T,n,p,k,x,y,ans;
int cnt[N],ncnt[N];
string s;
void clear()
{
	memset(cnt,0,sizeof(cnt));//整个序列中 1 的个数
	memset(ncnt,0,sizeof(ncnt));//当前位置之前的 1 的个数
	ans=1e9;
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		clear();
		scanf("%d%d%d",&n,&p,&k);cin>>s;scanf("%d%d",&x,&y);
		for(int i=p-1;i<n;i++)
			cnt[(i-p+1)%k]+=s[i]-'0';//预处理 1 的个数
		for(int i=p-1;i<n;i++)
			ans=min(ans,((int)ceil((double)(n-i)/k)-cnt[(i-p+1)%k]+ncnt[(i-p+1)%k])*x+(i-p+1)*y),ncnt[(i-p+1)%k]+=s[i]-'0';
		printf("%d\n",ans);
	}
	return 0;
}
```



---

## 作者：xh39 (赞：0)

有一个01串,你可以执行以下操作:将一个$0$改变为$1$,代价为$x$;将01串的第一个元素删除,代价为$y$。现在必须让下标为$p+k\times i (i为任意符合条件的数)$的**任意**元素**都**为$1$。求代价的最小值。

直接将最开始$(p-1)$个元素直接删除,然后$p=1$。正确性略。

然后dp。设删除$i$次的方案为$f[i]$,状态转移方程为:

$f[i]=\{暴力枚举,具体见代码。 (i<=k)$

$\kern{30pt} \{f[i-k]\kern{68pt}(i>k且s[i-k]=1) $

$\kern{30pt} \{f[i-k]-x\kern{50pt}(i>k且s[i-k]=0) $

当$s[i-k]=0$时,说明可以少改一个,即少用代价$x$。

答案为$f[i]+i\times y$的最大值。因为删一个数用代价$y$。

代码

```cpp
#include<iostream>
using namespace std;
string s;
int f[1000005];
void Main(){
	int n,p,k,add,del,i,j,sum=0,Min=2147483647;
	cin>>n>>p>>k>>s>>add>>del;
	n-=p-1;
	s.erase(0,p-1);
	for(i=0;i<k;i++){
		sum=0;
		for(j=i;j<n;j+=k){ //不断枚举p,p+k,p+2k,p+3k,...
			if(s[j]=='0'){ //需要修改。
				sum+=add;
			}
		}
		f[i]=sum;
	}
	for(i=k;i<n;i++){
		f[i]=f[i-k];
		if(s[i-k]=='0'){
			f[i]-=add;
		}
	}
	for(i=0;i<n;i++){
		Min=min(Min,f[i]+del*i);
	}
	cout<<Min<<endl;
}
int main(){
	int t,i;
	cin>>t;
	for(i=0;i<t;i++){
		Main();
	}
	return 0;
}
```

---

## 作者：比利♂海灵顿 (赞：0)

# CF1415C Bouncing Ball

设删掉 $l$ 块，等价于让球从 $p + l$ 开始弹，为了方便编程和思考，接下来将以这种模型分析本题。

因为 $k$ 是固定的，所以只要 $l$ 确定了，最后的花费就确定了，所以每组数据只有 $n - p + 1$ 种方案 ($0 \leq l \leq n - p$)，只要枚举每种方案的花费即可。

首先打出暴力，枚举删除块数 $l$，然后模拟弹跳，需要加平台就加平台，从每一种方案的花费中选出最小花费。单组数据时间复杂度 $O(\frac{n^2}k)$。

然后思考优化，发现枚举 $l$ 和 $l + k$时，除了对于删 $l$ 时第一个讨论的落点以外，其它落点都时重复计算的，而且对于每一个 $l$ 都是这样，周期固定为 $k$。

不妨新建一个数组 `f[l]`，存储每一个满足 $0 \leq l < k$ 的方案增加平台的总花费。预处理复杂度 $O(\frac{nk}k)$，即 $O(n)$。

预处理后开始枚举每一个 $l$，先看看已经删掉的 $l + p - k$ 是否要加一个平台，即是否原来没有平台，如果本来没有，那么在 `f[l % k]` 中一定计算了给 $l + p - k$ 加平台的花费，由于当前方案这个块被删除了，所以不能再计算给 $l - p + k$ 加平台的花费了，要减掉。

不要忘记特判 $l < k$ 的情况，由于一开始不删点也不会落到 $l + p - k$ 上，所以 `f[l % k]` 本来就没有计算 $l + p - k$ 是否加平台的花费，所以不进行上一段提出的对 `f[l % k]` 的修正。

有了预处理后的枚举过程被优化到了 $O(n - p)$，所以单组数据总复杂度为 $O(n)$，总复杂度 $O(sum_n)$，符合要求。

## 代码

```cpp
int n, p, k, t, ans, b, c, tmp, f[100005];
char S[100005];
bool a[100005];
void Clr() {  //初始化变量和数组
  n = RD();   //读入优化已省略
  p = RD();
  k = RD();
  gets(S);
  b = RD();
  c = RD();
  for (register int i(0); i < n; ++i) {
    a[i + 1] = S[i] - '0';  //将字串转化为 bool 数组, 存某一位上是否有平台
  }
  memset(f, 0, sizeof(f));
  ans = 0x7f3f3f3f;
  return;
}
int main() {
  t = RD();
  for (register int T(1); T <= t; ++T) {
    Clr();
    for (register int i(0); i < k; ++i) {  //枚举符合 0 <= l < k 的 l
      for (register int j(p + i); j <= n; j += k) {  //模拟弹跳
        if (!a[j]) {                                 //无平台
          f[i] += b;                                 //加平台
        }
      }
    }
    for (register int i(0); i <= n - p; ++i) {  //枚举每个方案中的 l
      tmp = c * i;                              //删除 i 块需要的花费
      if (i >= k) {
        if (!a[i + p - k]) {  // f[i % k]中计算了给 i + p - k 加平台的花费
          f[i % k] -= b;  //不用给已经删掉的块加平台
        }
      }
      tmp += f[i % k];  //删除 i 块的花费 + 加平台的花费 = 总花费
      ans = min(ans, tmp);  //更新最优方案
    }
    printf("%d\n", ans);
  }
  return 0;
}
```

---

