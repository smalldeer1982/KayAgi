# Balanced Substring

## 题目描述

You are given a string $ s $ consisting only of characters 0 and 1. A substring $ [l,r] $ of $ s $ is a string $ s_{l}s_{l+1}s_{l+2}...\ s_{r} $ , and its length equals to $ r-l+1 $ . A substring is called balanced if the number of zeroes (0) equals to the number of ones in this substring.

You have to determine the length of the longest balanced substring of $ s $ .

## 说明/提示

In the first example you can choose the substring $ [3,6] $ . It is balanced, and its length is $ 4 $ . Choosing the substring $ [2,5] $ is also possible.

In the second example it's impossible to find a non-empty balanced substring.

## 样例 #1

### 输入

```
8
11010111
```

### 输出

```
4
```

## 样例 #2

### 输入

```
3
111
```

### 输出

```
0
```

# 题解

## 作者：zhengrunzhe (赞：8)

为什么要map啊，还带个log

前缀和大小必定在[-n,n]之间

桶开成数组，+n就好了

把0权值转为-1

题意就变成了求最长和为0的区间长度

做个前缀和$sum$

$sum[r]-sum[l-1]=0$就是$sum[r]=sum[l-1]$


$first[i]$表示前缀和为i的第一次出现的位置

$for \  i$扫过去看桶的$sum[i]$更新答案，把$sum[i-1]$丢到桶里

时间复杂度:$O(n)$

```cpp
#include<cstdio>
int max(int a,int b){return a>b?a:b;}
const int N=1e5+10;
int n,sum[N],first[N+N],ans;
char s[N];
int main()
{
	scanf("%d",&n);
	scanf("%s",s+1);
	for (int i=1;i<=n;i++)sum[i]=sum[i-1]+(s[i]=='1'?1:-1);
	for (int i=1;i<=n;i++)
	{
		if (first[sum[i]+n])ans=max(ans,i-first[sum[i]+n]+1);
		if (!first[sum[i-1]+n])first[sum[i-1]+n]=i;
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：曼恩薄荷 (赞：4)

	看到前面也有一篇使用stl中map的题解
	但是思路与我略有不同，我个人也觉得自己的做法较为简洁
	所以就发了一篇题解，希望管理员通过。
    

------------

	进入正题，首先我们可以将0看作-1，将1依旧记为1，这样处理出前缀和数组s。
    显然：如果s[i]于零，则从1到i的这一段中0和1的数量相等。
    那么如果s[i]不为零，即意味着前i个数中1与0的数量差为s[i]。
    那么只要找到最小的一个j，使s[j]=s[i]。
    对于区间[j,i]，1和0的数量便相等。
    我便想到用map来记录最早出现的s[i]的标号。
    下面上程序：
    ```cpp
	#include<bits/stdc++.h>
	using namespace std;
	int s[100005],n,ans;
	map<int,int>Map;
	int main()
	{
 	   scanf("%d",&n);
  	   for(int i=1;i<=n;i++)
 	   {
      	  int t;
      	  scanf("%1d",&t);//每次读入一个数字，免去字符串的复杂处理
     	  if(t == 0)
     	       s[i] = s[i-1] - 1;
          if(t == 1)
            s[i] = s[i-1] + 1;//统计前缀和
          if(!s[i])
            ans = max(ans,i);//如果从1到i已经数量相等，可以直接更新答案
          if(!Map[s[i]])
            Map[s[i]] = i;//如果s[i]为第一次出现，则记录其下标
          else
            ans = max(i-Map[s[i]],ans);//调用map求得最靠前的s[j]=s[i]更新答案
        } 
        printf("%d",ans);
        return 0;
    }
```

---

## 作者：qwq114514 (赞：1)

## CF873B Balanced Substring 题解 ##
### 0x00 开始之前 ###
理解题意：  
给出一个整数 $ n $ 和一个长度为 $ n $ 的 $ 01 $ 串，求一个最长的为“平衡串”的子串 **（注意是字串不是子序列）**。     
平衡串的定义：平衡串是一个 $ 01 $ 串，里面 $ 0 $ 的个数与 $ 1 $ 的个数相等。    
判断个数相等暴力是 $ O(n) $ 的。   
枚举区间的两端又是 $ O(n^2) $ 的。   
合起来就是 $ O(n^3) $ 的。   
TLE可是再正常不过了。
### 0x01 前缀和速度优化 ###
这样，有了区间两端之后，经过**前缀和**优化后的暴力变成了 $ O(n^2) $ ，还是有所优化的。  
但是要想明白如何将区间和转化成判断平衡串。   
我们只要把 $ 01 $ 串变成 $ -1 $ 和 $ 1 $ 的串（ $ 0 $ 变为 $ -1 $ ），然后如果区间双端的前缀和相等就说明这个区间是“平衡串”。
### 0x02 时间复杂度优化 * 2 ###
- 假如我们的字符串全为 $ -1 $ ，前缀和数组将会最小，第 $ n $ 项为 $ -n $ 。    
- 假如我们的字符串全为 $ 1 $ ，前缀和数组将会最打，第 $ n $ 项为 $ n $ 。   

我们既然要判断**最长**串，就应该让前缀和中两个相等元素距离最长，而元素在 $ -n $ 到 $ n $ 之间。   
先枚举 $ 0 $ 到 $ n $ 算出对于每一个前缀和的起始点和结束点，再枚举 $ -n $ 到 $ n $ 求最大长度。   
时间复杂度是 $ O(n) $ 的。
### 0x03 代码实现 ###
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[114514],f[114514*2],l[114514*2];
string s;
int main(){
    memset(f,0x3f,sizeof(f));//注意设为0的话开始下标为0的点再待会判断的时候不会被算入（这样了之后判断的就是0x3f3f3f）
    memset(l,0x3f,sizeof(l));
    int n;
    cin>>n>>&s[1];
    //解释：a前缀和数组下表为i，l和f数组下表为前缀和的值
    for(int i=1;i<=n;i++){
        a[i]=((s[i]=='0')?(-1):(1));//将01串改变为-1和1的字符串
        a[i]+=a[i-1];//前缀和
    }
    for(int i=0;i<=n;i++){
        if(f[a[i]+n]==0x3f3f3f3f)f[a[i]+n]=i;//如果枚举到现在还没有枚举到那就设置起始点
        //下标+n因为a[i]的值是在-n到n之间，下标必须非负
        l[a[i]+n]=i;//结束点的设置：i越来越大，不需要max函数设置结束点
    }
    int maxl=0;
    for(int i=0;i<=n*2;i++)maxl=max(maxl,l[i]-f[i]);
    cout<<maxl;
    return 0;
}//结束啦！
```

---

## 作者：AC_Automation (赞：1)

题意：给出一个$n$长度的01串，其中含有相同0，1个数的子串被称为“平衡串”，问最长的平衡串的长度。

我们可以先将0改变成-1，这样的话，新串中和为0的子串即为原串中“平衡串”。

考虑枚举某一个端点，并判断是否存在可行的另一个端点。在这道题中，我们枚举右端点。

让我们维护一个前缀和数组$sum[i]$。对于某一个右端点$k$，如果存在一个$j\in[1,k-1]$，使得$sum[j]=sum[k]$，那么$\sum_{i=j+1}^ka_i$就一定等于0。这样的话，就形成了一个平衡串。我们可以用一个桶来记录前缀和数组之前是否存在过某个值，就可以$O(1)$判断一个右端点是否对应一个左端点，即可通过本题。
```
#include<iostream>
using namespace std;
int book[200005];//桶
int main(){
	int n,sum=0,ans=0;
	cin>>n;
	string s;
	cin>>s;
	for(int i=1;i<=n;i++){
		if(s[i-1]=='1')sum++;
		else sum--;//sum记录前缀和
		if(sum==0)ans=max(ans,i); //有可能平衡串出现在最开始的某一个串
		if(book[sum+100000]==0)book[sum+100000]=i;
		else ans=max(ans,i-book[sum+100000]);
        //注意：1.桶内如果已经有了元素，那么不要改变它，因为左端点越靠左越好
        //2.因为前缀和有可能<0，那么我们需要整体移动桶的下标
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：yeshubo_qwq (赞：1)

思路：

将 $0$ 作为 $-1$，将 $1$ 作为 $+1$，做前缀。

如果两个位置 $l,r$ 的前缀的值相等，则 $l+1 \sim r$ 一定是“平衡串”。

用数组记录每一个值第一次出现的位置，后面每出现一次这个值，就求出“平衡串”的长度取最大。

但是，前缀的值可能出现负数，但范围在 $-n \sim n$，所以要在记录时下标要 $+n$。

注意：前缀的值为 $0$ 时，第一次出现的位置就是 $0$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,i,x,ans,a[200005];
char s[100005];
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>s+1;
	for (i=1;i<=n;i++){
		x=x+(s[i]=='0'?-1:1);
		if (x!=0&&a[x+n]==0) a[x+n]=i;
		else ans=max(ans,i-a[x+n]);
	}
	return cout<<ans,0;
}
```


---

## 作者：happybob (赞：0)

考虑将 `0` 权值设为 $-1$，将 `1` 权值设为 $1$。

题目即求一段最长子串使得这一串的权值和为 $0$。

考虑 $p_i$ 为权值，其中 $1 \leq i \leq n$，前缀和为 $s_i = \sum \limits_{j=1}^i p_i$。特别地，$sum_0=0$。

即求 $r-l+1$ 最大的 $(l,r)$ 使得 $sum_r = sum_{l-1}$。

然后枚举每一个 $l$，显然可以 $O(1)$ 算出最靠后的和它相同的 $r$，求最大值即可。

复杂度 $O(n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 5;

int sum[N];
vector<int> v[N];

string s;

int main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cin >> s >> s;
	int n = s.size() - 1;
	for (int i = 0; i <= n; i++)
	{
		sum[i] = (s[i] == '0' ? -1 : 1) + (i == 0 ? 0 : sum[i - 1]);
		v[sum[i] + n].push_back(i);
	}
	int ans = 0;
	for (int i = 0; i <= n; i++)
	{
		if (sum[i] == 0) ans = max(ans, i + 1);
		if (*(--v[sum[i] + n].end()) == i) continue;
		ans = max(ans, *(--v[sum[i] + n].end()) - i);
	}
	printf("%d\n", ans);
	return 0;
}
```


---

## 作者：ynxynx (赞：0)

~~水题~~

这道题目我们用一个前缀和 $sum_i$ 维护前 $n$ 个数的和。

因为第一个为 $0$，我们将 $0$ 变为 $-1$，直接处理 $0$ 就可以了。

$\forall i < j,sum_i = sum_j$ 时，显然集合 $\lbrace a_{i+1},a_{i+2},\cdots ,a_j \rbrace$ 符合题意。

我们可以直接用一个 $f_i$ 表示 $sum_j$ 的值为 $i$ 的第一次出现时 $j$ 的值，每次找到时取其距离 $f_i$ 的距离和答案最大值。

那么就做完了。。。

上代码

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
const int N=1e5+10;
int n,sum[N],f[2*N],ans;
char s[N];
int main(){
	scanf("%d",&n);
	scanf("%s",s+1);
	for (int i=1;i<=n;i++) sum[i]=sum[i-1]+(s[i]=='1'?1:-1);//变零
	for (int i=1;i<=n;i++){
		if (f[sum[i]+n]) ans=max(ans,i-f[sum[i]+n]+1);//加n是为了避免负数
		if (!f[sum[i-1]+n]) f[sum[i-1]+n]=i;//处理前一项，放在后面的原因是防止重复
	}
	printf("%d\n",ans);
	return 0;
}

```

---

