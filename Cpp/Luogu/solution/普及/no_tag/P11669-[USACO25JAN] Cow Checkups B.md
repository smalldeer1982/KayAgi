# [USACO25JAN] Cow Checkups B

## 题目描述

**注意：我们建议使用 Python 以外的其他语言以获得本题目的全部分数。**

Farmer John 的 $N$（$1 \leq N \leq 7500$）头奶牛站成一行，奶牛 $1$ 在队伍的最前面，奶牛 $N$ 在队伍的最后面。FJ 的奶牛也有许多不同的品种。他用从 $1$ 到 $N$ 的整数来表示每一品种。队伍从前到后第 $i$ 头奶牛的品种是 $a_i$（$1 \leq a_i \leq N$）。

FJ 正在带他的奶牛们去当地的奶牛医院进行体检。然而，奶牛兽医非常挑剔，仅愿意当队伍中第 $i$ 头奶牛为品种 $b_i$（$1 \leq b_i \leq N$）时对其进行体检。

FJ 很懒惰，不想完全重新排列他的奶牛。他将执行以下操作恰好一次。

选择两个整数 $l$ 和 $r$，使得 $1 \leq l \le r \leq N$。反转队伍中第 $l$ 头奶牛到第 $r$ 头奶牛之间的奶牛的顺序。
FJ 想要衡量这种方法有多少效果。对于每一个 $c=0 \ldots N$，请帮助 FJ 求出使得恰好 $c$ 头奶牛被检查的不同操作 $(l,r)$ 的数量。两种操作 $(l_1,r_1)$ 和 $(l_2,r_2)$ 不同，当且仅当 $l_1 \neq l_2$ 或者 $r_1 \neq r_2$。

## 说明/提示

### 样例解释


#### 样例 #1：

如果 FJ 选择 $(l=1,r=1)$，$(l=2,r=2)$ 或 $(l=3,r=3)$，则没有奶牛将会被检查。注意这些操作并没有改变奶牛的位置。
以下操作会导致一头奶牛被检查。

- $(l=1,r=2)$：FJ 反转第一头和第二头奶牛的顺序，因此新队伍中每头奶牛的品种将为 $[3,1,2]$。第一头奶牛将会被检查。
- $(l=2,r=3)$：FJ 反转第二头和第三头奶牛的顺序，因此新队伍中每头奶牛的品种将为 $[1,2,3]$。第二头奶牛将会被检查。
- $(l=1,r=3)$：FJ 反转第一头，第二头和第三头奶牛的顺序，因此新队伍中每头奶牛的品种将为 $[2,3,1]$。第三头奶牛将会被检查。

#### 样例 #2

三种导致 $3$ 头奶牛被检查的可能操作为 $(l=1,r=1)$，$(l=2,r=2)$ 和 $(l=3,r=3)$。

#### 样例 #3

两种导致 $4$ 头奶牛被检查的可能操作为 $(l=4,r=5)$ 和 $(l=5,r=7)$。

### 子任务
- 测试点 4-6: $N\le 100$
- 测试点 7-13: 无特殊限制

## 样例 #1

### 输入

```
3
1 3 2
3 2 1```

### 输出

```
3
3
0
0```

## 样例 #2

### 输入

```
3
1 2 3
1 2 3```

### 输出

```
0
3
0
3```

## 样例 #3

### 输入

```
7
1 3 2 2 1 3 2
3 2 2 1 2 3 1```

### 输出

```
0
6
14
6
2
0
0
0```

# 题解

## 作者：yedalong (赞：11)

双指针好题。
## Solution
初次见到这道题，我的第一想法就是枚举左右端点，用一个数组 $ans$ 记录答案，加上判断后就很成功的超时了，代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a[7505],b[7505],ans[7505],cnt;
int main(){
    cin>>n;
    for(int i = 1;i<=n;i++) cin>>a[i];
    for(int i = 1;i<=n;i++) cin>>b[i];
    for(int i = 1;i<=n;i++) if(a[i]==b[i]) cnt++;
    for(int l = 1;l<=n;l++){
        for(int r = l;r<=n;r++){
            int tmp=cnt;
            for(int i = l;i<=r;i++){
                if(a[i]==b[i]) tmp--;
                if(a[i]==b[r-(i-l)]) tmp++;
            }
            ans[tmp]++;
        }
    }
    for(int i = 0;i<=n;i++) cout<<ans[i]<<'\n';
}
```
[评测结果](https://www.luogu.com.cn/record/201285274)  
接下来我们考虑优化。  
我们可以考虑省掉判断的时间，具体怎么省呢？我们可以选定一个中间点，让 $l$ 和 $r$ 在中间点两边向外移动，这样在枚举 $l$ 和 $r$ 的同时也就可以判断，用一个 $tmp$ 变量存当前的被检查奶牛数，就省下判断的时间了！  
当左端点为 $l$，右端点为 $r$ 时的判断：
$$tmp=\left\{
\begin{array}{rcl}
tmp-1    &   &      {a_l=b_l\land a_l\neq b_r}\\
tmp-1    &   &      {a_r=b_r\land a_r\neq b_l}\\
tmp+1     &   &      {a_l\neq b_l\land a_l=b_r}\\
tmp+1     &   &      {a_r\neq b_r\land a_r=b_l}\\
\end{array}\right.$$  
这一部分算是比较好理解的。  
最后就能解决此题。  
## AC code
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a[7505],b[7505],ans[7505],cnt,l,r;
int main(){
    cin>>n;
    for(int i = 1;i<=n;i++) cin>>a[i];
    for(int i = 1;i<=n;i++) cin>>b[i];
    for(int i = 1;i<=n;i++) if(a[i]==b[i]) cnt++;
    for(int i = 1;i<=n;i++){
        int tmp=cnt;
        l=i,r=i;
        while(l>=1&&r<=n){
            if(a[l]==b[l]&&a[l]!=b[r]) tmp--;
            if(a[r]==b[r]&&a[r]!=b[l]) tmp--;
            if(a[l]!=b[l]&&a[l]==b[r]) tmp++;
            if(a[r]!=b[r]&&a[r]==b[l]) tmp++;
            ans[tmp]++;
            l--,r++;
        }
        if(i==n) continue;
        l=i,r=i+1;
        tmp=cnt;
        while(l>=1&&r<=n){//这里进行两次的区别是：一次是枚举长度为奇数的区间，一次是枚举长度为偶数的区间
            if(a[l]==b[l]&&a[l]!=b[r]) tmp--;
            if(a[r]==b[r]&&a[r]!=b[l]) tmp--;
            if(a[l]!=b[l]&&a[l]==b[r]) tmp++;
            if(a[r]!=b[r]&&a[r]==b[l]) tmp++;
            ans[tmp]++;
            l--,r++;
        }
    }
    for(int i = 0;i<=n;i++) cout<<ans[i]<<'\n';
}
```
最后也是跑得飞快，[评测记录](https://www.luogu.com.cn/record/201301908)。

---

## 作者：chenxi2009 (赞：8)

**本文含有二创成分。**

> 荡魂山处石人泪，定仙游走魔向北。

你是蛊修世界中的一名蛊师。不久之前你在十大古派的比拼中获胜，成为了狐仙福地的主人。然而你在福地中触发了“逆”组织的布置，断绝了与福地外部的联系，只有炼出定仙游蛊才能逃出生天。

你所得知的蛊方中主材有两种：胆识蛊和太古的荣耀之光。你的手上有 $n$ 只胆识蛊，根据产生胆识蛊的石人魂魄有着不同的类型，从左向右第 $i$ 只胆识蛊的类型为 $a_i$，而蛊方中记录的第 $i$ 个位置上摆放的是类型为 $b_i$ 的胆识蛊，炼蛊的成功率和所需的荣耀之光的量取决于你有多少个胆识蛊摆放正确。

你可以调整胆识蛊的摆放顺序，但是由于时间紧迫，你只能做一次如下操作：
> 选择两个正整数 $1\le l\le r\le n$，把 $a_{l\cdots r}$ 左右翻转。

你的炼道境界普通，所以在炼蛊之前需要完全熟悉这份蛊方。你需要知道每一个数量 $i(i\in[0,n])$，有多少种操作方式可以使得有 $i$ 个位置摆放着正确的胆识蛊？
## 思路
胆识蛊数量不足一万，可以考虑 $O(n^2)$ 的算法。

这个时候就需要我们发现一个性质：对于对称中心相同的操作，是可以在从中心向两边扩展的过程中依次全部求出的。也就是说，如果用 $f_{l,r}$ 表示操作 $(l,r)$ 后的正确蛊数，那么形式化地，$f_{l,r}$ 由 $f_{l+1,r-1}$ 的值和 $a_l$、$a_r$、$b_l$、$b_r$ 的关系决定。

具体而言，可以列出式子：$f_{l,r}=f_{l+1,r-1}-[a_l=b_l]-[a_r=b_r]+[a_l=b_r]+[a_r=b_l](r-l\ge2)$。

动态规划还是太吃操作了，我们可以枚举每一个对称中心，用上面这个式子得到所有的方案，时间复杂度 $O(n^2)$。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[8000],b[8000],ans[8000],l,r,all,cnt;
inline void expand(){//将 (l,r) 扩展到 (l-1,r+1)，cnt 记录了正确的位置数 
    l --,r ++;
    cnt = cnt + (a[l] == b[r]) + (a[r] == b[l]) - (a[l] == b[l]) - (a[r] == b[r]);
    ans[cnt] ++;
}
int main(){
    scanf("%d",&n);
    for(int i = 1;i <= n;i ++) scanf("%d",&a[i]);
    for(int i = 1;i <= n;i ++) scanf("%d",&b[i]);

    for(int i = 1;i <= n;i ++) if(a[i] == b[i]) all ++;//先统计不翻转的情况下正确位置的个数
    for(int i = 1;i <= n;i ++){//枚举以位置 i 为中心的反转方案
        cnt = all,l = i + 1,r = i - 1;//这样设定初始值可以让第一次扩展后 l=r，下面同理
        while(l - 1 > 0 && r + 1 <= n) expand();
    }
    for(int i = 1;i < n;i ++){//枚举以位置 i+0.5 为中心的反转方案
        cnt = all,l = i + 1,r = i;
        while(l - 1 > 0 && r + 1 <= n) expand();
    }

    for(int i = 0;i <= n;i ++) printf("%d\n",ans[i]);
    return 0;
}
```

---

## 作者：cjh20090318 (赞：6)

## 题意

给定两个 $N$ 个数的数列 $a,b$。

设 $d$ 表示将 $a$ 的 $[l,r]$ 区间翻转后的数列，$f(l,r) = \sum\limits_{i=1}^N[d_i = b_i]$。

求对于每个 $c \in [0,N] \cap \mathbb{N}$，有多少对不同的 $(l,r)\ (1 \le l \le r \le N)$ 满足 $f(l,r) = c$。

## 分析

$1 \le N \le 7500$ 提示时间复杂度可能是 $O(N^2)$，也就是说要找到一种对于每个区间求相等数量为 $O(1)$ 的做法。

对于一个当前已知答案区间 $[l,r]$，可以迅速推广到区间 $[l-1,r+1]$。因为他们的对称轴是相同的，所以新区间内 $[l,r]$ 的关系不会变，计算答案只需要考虑 $l-1$ 和 $r+1$ 对应的关系即可。

时间复杂度 $O(N^2)$。

## 代码

```cpp
//the code is from chenjh
#include<cstdio>
using namespace std;
int n;
int a[7505],b[7505];
int ans[7505];
int main(){
	scanf("%d",&n);
	int org=0,sum=0;
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++) scanf("%d",&b[i]),org+=a[i]==b[i];//初始有多少个已经对应相等。
	for(int i=1;i<=n;i++){
		sum=org;
		for(int l=i,r=i+1;l>0&&r<=n;--l,++r)
			++ans[sum+=(a[l]==b[r])+(a[r]==b[l])-(a[l]==b[l])-(a[r]==b[r])];//对称轴在 i 和 i+1 之间，加上两端新出现的答案，减去原来的答案。
		sum=org;
		for(int l=i,r=i;l>0&&r<=n;--l,++r)
			++ans[sum+=(a[l]==b[r])+(a[r]==b[l])-(a[l]==b[l])-(a[r]==b[r])];//对称轴为 i，同上。
	}
	for(int i=0;i<=n;i++) printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：w150432 (赞：1)

### 题意： 
题目给我们两个长度为  $n$ 的数组，如果  $a_i = b_i$ 我们就叫他们是匹配的。然后我们需要计算出有多少种区间 $l \sim r$ 让恰好 $c$ 头奶牛匹配，$0 \leq c \leq n$ ，按顺序输出每种 $c$ 的值。

### 暴力：
我们先想一下暴力，那就是每次反转区间 $l \sim r$， 区间的数量是 $ \large\frac{N(N + 1)}{2}$， $N$ 最大为 $7500$，所以最坏大概是 $2 \times 10^7$ 个，然后还需要从头至尾遍历区间，区间最坏的长度为 $N$ 也就是 $7500$， 显然不可能在一秒内完成。

### 优化：
我们再想想如何优化，先做出前缀和记录，前缀和的第     $i$ 个元素表示 $1 \sim i$ 区间中牛原来的顺序，和体检顺序匹配的数量。这样我们就可以快速计算区间 $l \sim r$ 不转换的匹配数量

然后，我们创建一个数组 $f$，初始化的时候所有值都是 $0$，$ \large f_{l,r}$ 表示在反转区间 $l \sim r$ 后，$l \sim r$ 区间能够被检查的奶牛的数量。经过一阵摸索发现了他的推导式 $ \large f_{l,r} = \large f_{l + 1, r - 1}$ 加上 $a_{l + 1}$ 和 $b_{r - 1}$ 是否匹配，加上$a_{r - 1}$ 和 $b_{l + 1}$ 是否匹配。

我们按照长度dp，因为只有长度比 $r - l + 1$ 小的区间先推算出来才能保证现在推算是正确的,值得注意的是当长度为 $2$ 和 $3$ 的时候会出现一些特殊的情况，比如 $ \large f_{1,2}$ 会从 $\large f_{2,1}$ 推算，实际上$ \large f_{2, 1}$ 是不存在的，所以当成 $0$ 处理即可。

但是当我们计算长度为 $3$ 的区间时会出现一些需要提前修改的地方，比如我们要计算 $ \large f_{1,3}$ 它会使用到 $\large f_{2,2}$ ，长度为 $1$ 的区间反转相当于没有反转，它等价于原数组的匹配。所以我们需要在计算 $f$ 数组前提前处理。当 $a_i = b_i$ 时，$ \large f_{i, i}$ 的值就赋为 $1$， 当 $a_i \neq b_i$ 时 $\large f_{i,i}$ 的值为 $0$。

最后，当计算完 $f$ 数组后，我们需要创建一个数组 $ans$ ， $ans_i$ 表示反转后匹配数量是 $i$ 的区间的数量。我们只需要遍历所有改变的区间，把改变区间的匹配数加上不变区间的匹配数量的和算出来，这个 $ans$ 的下标，然后让这个下标的 $ans_i$ 加 $1$ 即可。计算完 $ans$ 数组后就直接遍历输出。 

### AC代码：

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 7500 + 10;

int n, cnt;
int sum[N];
int a[N], b[N];
int ans[N];
int dp[N][N];

int main()
{
    scanf("%d", &n);

    for (int i = 1 ; i <= n ; i ++ ) scanf("%d", &a[i]);
    for (int i = 1 ; i <= n ; i ++ ) scanf("%d", &b[i]);

    for (int i = 1 ; i <= n ; i ++ )
    {
        sum[i] = sum[i - 1];
        if (a[i] == b[i])
        {
            dp[i][i] = 1;
            sum[i] ++;
        }
    }

    for (int len = 2 ; len <= n ; len ++ )
        for (int j = 1 ; j + len - 1 <= n ; j ++ )
            dp[j][j + len - 1] = dp[j + 1][j + len - 2] + (a[j] == b[j + len - 1]) + (a[j + len - 1] == b[j]);

    for (int i = 1 ; i <= n ; i ++ )
        for (int j = i ; j <= n ; j ++ )
            ans[dp[i][j] + sum[i - 1] + sum[n] - sum[j]] ++;

    for (int i = 0 ; i <= n ; i ++ )
        printf("%d\n", ans[i]);

    return 0;
}
```

---

## 作者：chzhh_111 (赞：1)

注意到 $n$ 的范围最大为 $7500$，这就为我们考虑实现 $O(n^2)$ 的算法提供可能性。

首先我们来考虑暴力：

- 第一步，枚举每一个区间的长度；
- 第二步，枚举左端点求出右端点；
- 第三步，我们遍历一整个区间，算出这一个区间可以对答案产生贡献是什么。

可以发现这样子的时间复杂度应该是 $O(n^3)$，是远远达不到通过这道题的限制。但是我们发现在求第三步的时候我们可以利用之前遍历的结果，因此我们可以设立一个 $sum_{i,len}$，用来表示翻转一个以 $i$ 为中心，其中长度为 $len$ 的区间后，整个可以能被成功匹配的个数，而这个数组的转移我们可以由 $sum_{i,len - 2}$ 转移过来（也就是如果长度的奇偶性相同，我们可以将之前枚举的结果向左右扩展得到现在我们要求的东西）。

同时这个数组是可以滚动优化的，可以变成 $sum_{i,0/1}$，表示翻转一个以 $i$ 为中心，其中长度为偶数或者奇数的区间后，整个可以被成功匹配的个数。

答案我们只需要别求 $sum$ 数组边统计就行了。

初始化的话，一开始我们将一整个 $sum$ 数组赋值为 $cnt$，其中 $cnt$ 表示在不进行任何操作下所能成功匹配的个数。

代码部分：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=7501;
int n,a[N],b[N],cnt,sum[N][2],ans[N];
signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++) scanf("%lld",&b[i]),cnt+=(a[i]==b[i]);
	for(int i=1;i<=n;i++) sum[i][0]=sum[i][1]=cnt;
	for(int i=1;i<=n;i++)
	{
		for(int l=1;l<=n-i+1;l++)
		{
			int r=l+i-1,mid=(l+r)/2,tot=i&1;
			sum[mid][tot]+=(a[l]!=b[l]&&a[l]==b[r])+(a[r]!=b[r]&&a[r]==b[l]);
			sum[mid][tot]-=(a[l]!=b[r]&&a[l]==b[l])+(a[r]!=b[l]&&a[r]==b[r]);
			ans[sum[mid][tot]]++;
		}
	}
	for(int i=0;i<=n;i++) printf("%lld\n",ans[i]);
	return 0;
}
```

如果成功 AC 这题，可以尝试一下 [另外一道](https://www.luogu.com.cn/problem/P9325)，我感觉思路还挺像的。

---

## 作者：nbhs23a28 (赞：1)

一道和石子合并一样典型的区间 DP 模板题。先计算原匹配数，至于变化数，我们发现，每一段区间 $[l,r](r-l>1)$ 的状态都可以由 $[l+1,r-1]$ 的状态结合 $a_l,b_l$ 及 $a_r,b_r$ 的关系求得，状态转移方程为
```cpp
f[l][r]=f[l+1][r-1]+(a[l]==b[r])+(a[r]==b[l])-(a[l]==b[l])-(a[r]==b[r])
```
另，注意转移顺序（参考石子合并，初始化后由区间长 $k$ 作第一层循环）。

Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[10010],b[10010],cnt;
long long ans[10010];
short f[7502][7502];
int main()
{cin>>n;
 for(int i=1;i<=n;i++)
 cin>>a[i];
 for(int i=1;i<=n;i++)
 {cin>>b[i];
  if(a[i]==b[i]) cnt++;
 }
 ans[cnt]+=n; //l=r时结果始终与原来相等
 for(int i=1;i<=n;i++)
 f[i][i]=f[i][i-1]=0;
 for(int k=1;k<n;k++)
 {for(int i=1;i<=n-k;i++)
  {f[i][i+k]=f[i+1][i+k-1]-(a[i]==b[i])-(a[i+k]==b[i+k])+(a[i]==b[i+k])+(b[i]==a[i+k]) ;  
   ans[cnt+f[i][i+k]]++;
  }
 }
 for(int i=0;i<=n;i++)
 cout<<ans[i]<<'\n';
}
```

---

## 作者：coding_sealion (赞：1)

### 题目大意

翻转 $a$ 数组的区间 $[l,r]$ ，求与 $b$ 数组中相同的数的个数。

### 解题思路

#### 解法一（预估 $30$ 分代码）：

暴力枚举两个端点 $l,r$ ，但显然会超时。

代码如下


```cpp
long long i,n,a[15005],b[15005],sum,ans,j,k,c[15005];
bool p[15005];
int main(){
	cin>>n;
	for(i=1;i<=n;i++)
		cin>>a[i];//输入a数组
	for(j=1;j<=n;j++){
		cin>>b[j];//输入b数组
	}
	for(i=1;i<=n;i++){
		for(j=i;j<=n;j++){
			sum=0;
			for(k=1;k<=n;k++){
				if(k<i||k>j){
					if(a[k]==b[k])sum++;//如果不在范围内
				}
				else {
					if(a[j-(k-i)]==b[k])sum++;//在范围内
				}
			}
			c[sum]++;//得到的答案++
		}
	}
	for(i=0;i<=n;i++)cout<<c[i]<<endl;//输出
	return 0;
}
```


这种方法不难想到，但分数也不高。

#### 解法二（ AC 代码）：

优化一：计算 $a$ 数组与 $b$ 数组初始时重合的个数，然后枚举区间内即可。

优化二：枚举所有区间的核心，向外扩张。

 AC 代码：


```cpp
//头文件自己写
long long i,n,a[15005],b[15005],sum,ans,j,k,c[15005];
bool p[15005];
int main(){
	cin>>n;
	for(i=1;i<=n;i++)
		cin>>a[i];//输入A数组
	for(j=1;j<=n;j++){
		cin>>b[j];//输入b数组
		if(a[j]==b[j])ans++,p[j]=1;//提前处理，ans记录原先a数组与b数组重叠个数，打标记（后面会用到）
	}
	for(k=1;k<=n;k++){//以k为中心枚举
		i=k;//用i记作k，因为k不能改动
		sum=0;//记录相较于原来答案的变化
		for(j=i;i>0&&j<=n;j++,i--){//区间内，数的个数为奇数
			if(a[j]!=b[i]&&p[i])sum--;//如果下标为i,j的两个数字调换后不一样且 调换前一样（P数组判断）会比原先少一个
			else if(a[j]==b[i]&&!p[i])sum++;//如果下标为i,j的两个数字调换后一样且 调换前不一样（P数组判断）会比原先多一个
			if(a[i]!=b[j]&&p[j])sum--;
			else if(a[i]==b[j]&&!p[j])sum++;//反之同理
			c[ans+sum]++;//得到的答案数++
		}
		sum=0;//i和sum都变了，所以要重新赋初值
		i=k;
		for(j=i+1;i>0&&j<=n;j++,i--){//区间内，数的个数为偶数，for循环里面相同
			if(a[j]!=b[i]&&p[i])sum--;
			else if(a[j]==b[i]&&!p[i])sum++;
			if(a[i]!=b[j]&&p[j])sum--;
			else if(a[i]==b[j]&&!p[j])sum++;
			c[ans+sum]++;//原始加上变化的，得到的答案++
		}
	}
	for(i=0;i<=n;i++)cout<<c[i]<<endl;//从小到大输出答案
	return 0;
}
```

---

## 作者：wanganze (赞：1)

### 题目描述

Farmer John 的 $N$（$1 \leq N \leq 7500$）头奶牛站成一行，奶牛 $1$ 在队伍的最前面，奶牛 $N$ 在队伍的最后面。FJ 的奶牛也有许多不同的品种。他用从 $1$ 到 $N$ 的整数来表示每一品种。队伍从前到后第 $i$ 头奶牛的品种是 $a_i$（$1 \leq a_i \leq N$）。

FJ 正在带他的奶牛们去当地的奶牛医院进行体检。然而，奶牛兽医非常挑剔，仅愿意当队伍中第 $i$ 头奶牛为品种 $b_i$（$1 \leq b_i \leq N$）时对其进行体检。

FJ 很懒惰，不想完全重新排列他的奶牛。他将执行以下操作**恰好一次**。

选择两个整数 $l$ 和 $r$，使得 $1 \leq l \le r \leq N$。反转队伍中第 $l$ 头奶牛到第 $r$ 头奶牛之间的奶牛的顺序。

FJ 想要衡量这种方法有多少效果。对于每一个 $c=0 \ldots N$，请帮助 FJ 求出使得恰好 $c$ 头奶牛被检查的不同操作 $(l,r)$ 的数量。两种操作 $(l_1,r_1)$ 和 $(l_2,r_2)$ 不同，如果 $l_1 \neq l_2$ 或者 $r_1 \neq r_2$。

### 分析

即给定一个序列，经过一次对区间 $\lbrack L,R \rbrack$ 的反转，求结果与目标序列的匹配数。

### 暴力

显然地，我们可以枚举区间，反转后用的`unordered_map` 记录匹配个数。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 7510;
int a[N],b[N];
unordered_map<int,int> mp;
int main()
{
	int n;
	cin>>n;
	for(int i = 1; i <= n; i ++) scanf("%d",&a[i]);
	for(int i = 1; i <= n; i ++) scanf("%d",&b[i]);
	for(int i = 1; i <= n; i ++)
		for(int j = i; j <= n; j ++)
		{
			int res = 0;
			for(int k = i; k <= j; k ++)
				if(a[i + j - k] == b[k]) res ++;
			mp[res] ++;
		}
	for(int i = 0; i <= n; i ++) printf("%d\n",mp[i]);
	return 0;
}
```

然而复杂度是 $O(n^3)$ 的，需要进一步优化。

### 优化
我们注意到计算反转序列的匹配数是代码的复杂度瓶颈(不变部分可以通过预处理得到)。我们发现会有很多次重复判断，因此可以枚举中心轴和轴长来减少重复计算（定义偶数长度区间的轴为中间两项）。

对区间的长度分奇偶讨论，奇数长的枚举中心轴和轴长，偶数的枚举左边的中心和轴长。从轴长小的开始，即可避免对较靠近反转的轴的重复计算，因为这些部分在较短轴、同中心的区间中已经算过。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 7510;
int a[N],b[N],c[N];
unordered_map<int,int> mp;
int main()
{
	int n;
	cin>>n;
	for(int i = 1; i <= n; i ++) scanf("%d",&a[i]);
	for(int i = 1; i <= n; i ++) scanf("%d",&b[i]);
	for(int i = 1; i <= n; i ++) c[i] = c[i - 1] + (a[i] == b[i]);
	for(int i = 1; i <= n; i ++)
	{
		int res = (a[i] == b[i]);
		mp[c[n]] ++;
		for(int j = 2; i - j + 1 >= 1 && i + j - 1 <= n; j ++)
		{
			res += (a[i - j + 1] == b[i + j - 1]) + (a[i + j - 1] == b[i - j + 1]);
			mp[res + c[i - j] + c[n] - c[i + j - 1]] ++;
		}
	}
	for(int i = 1; i <= n; i ++)
	{
		int res = 0;
		for(int j = 1; i - j + 1 >= 1 && i + j <= n; j ++)
		{
			res += (a[i - j + 1] == b[i + j]) + (a[i + j] == b[i - j + 1]);
			mp[res + c[i - j] + c[n] - c[i + j]] ++;
		}
	}
	for(int i = 0; i <= n; i ++) printf("%d\n",mp[i]);
	return 0;
}
```

代码中，`c` 数组用前缀和记录原本的匹配数，`res` 记录区间的匹配数。

复杂度 $O(n^2)$，可以通过本题。

---

## 作者：lcfollower (赞：1)

# 题目大意

给定长度为 $n$ 的序列 $a$，$b$。

你可以选择不同的 $l$，$r$（$1\le l\le r\le n$），使得 $a$ 序列种 $l$ 到 $r$ 下标的元素翻转（即 $a_r$ 变为 $a_l$，$a_{r-1}$ 变为 $a_{l+1}$，以此类推），操作之间互不影响且只能操作一次。

求对于所有整数 $j$（$j\in \{[0 ,n]\}$，操作后 $\sum\limits_{i=1}^n [a_i = b_i] = j$ 的数量。

---

申明一下，对于 $a_i = b_i$，我记作相同（~~主要是我懒~~）。

解题思路
---

首先看到 $n\le 7500$，可以想到出题人想把别的不正确的算法卡过，只过 $\mathcal O(n^2)$ 的算法。

最先想到的大概是枚举 $l$，$r$，然后翻转区间统计答案，时间复杂度为 $\mathcal O(n^3)$，期望得分 $30$ 分，实际得分 $42$ 分。

然后可以用平衡树优化区间翻转，但这玩意好像不能统计这段区间内与 $b_i$ 相等的元素（如果可以评论）？如果不能时间复杂度仍为 $\mathcal O(n^3)$，期望得分 $42$ 分。


---

考虑翻转不改变什么。

如果一个区间 $[l ,r]$ 经过翻转，那么接下来你会怎么样？

当然是在区间的左边和右边各添加一个元素，即 $a_{l - 1}$ 与 $a_{r + 1}$。

见下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/150l54c5.png)

蓝色部分的区间不变，下面在左、右两边各添加一个元素，这里记作一次拓展。

然而红色部分的序列和在左边以及右边各添加一个元素之后**不变**！

所以我们可以记录区间内的相同个数，一次拓展后可以 $\mathcal O(1)$ 记录，当然初始还是要从一个元素的区间开始啊。

这里是奇数长度的区间，偶数长度的区间同理，可以自己去画一画。

---

当你打完代码发现：你样例二没过。

然后检查后发现：统计的是区间内相同个数，还遗漏了**区间外**相同的个数！

这点不难办，前缀和就可以 $\mathcal O(1)$ 算出。

代码
---

```cpp
# include <bits/stdc++.h>

# define int long long
# define up(i ,x ,y) for (int i = x ; i <= y ; i ++)

using namespace std;

inline int read (){int s = 0 ; bool w = 0 ; char c = getchar () ; while (!isdigit (c)) {w |= (c == '-') ,c = getchar () ;} while (isdigit (c)){s = (s << 1) + (s << 3) + (c ^ 48) ; c = getchar ();}return w ? -s : s;}
inline void write (int x){if (x < 0) putchar ('-') ,x = -x; if (x > 9) write (x / 10) ; putchar (x % 10 | 48);}
inline void writeln (int x){write (x) ,putchar ('\n');}

const int N = 7505;
int n ,a[N] ,b[N] ,pre[N] ,ans[N];

signed main (){

  n = read ();

  up (i ,1 ,n) a[i] = read ();
  up (i ,1 ,n) b[i] = read ();
  up (i ,1, n) pre[i] = pre[i - 1] + (a[i] == b[i]);

  /* 奇数长度的 [l ,r]。 */

  up (i ,1 ,n){
    int res = 0;
    up (j ,1 ,min (i ,n - i + 1)){
      int l = i - j + 1 ,r = i + j - 1;
      
      if (l == r) res += (a[l] == b[l]);
      else res += (a[l] == b[r]) + (a[r] == b[l]);//由于是翻转，所以不是 (a[l] == b[l]) + (a[r] == b[r])。

      ans[res /* 区间内 */ + (pre[n] - pre[r] + pre[l - 1])/* 区间外 */] ++;
    }
  }

  /* 偶数长度的 [l ,r]。
     可以把 [i ,i + 1] 之间的空格看作 i 进行一次拓展，所以下面的 r = i + j 而不是 r = i + j - 1，j 的拓展范围也发生改变。
  */
  up (i ,1 ,n - 1){
    int res = 0;
    up (j ,1 ,min (i ,n - i)){
      int l = i - j + 1 ,r = i + j;
      //这里 l，r 不可能相等，i - j + 1 = i + j，解得 j = 0.5，一定不可能。

      res += (a[l] == b[r]) + (a[r] == b[l]);

      ans[res + (pre[n] - pre[r] + pre[l - 1])] ++;
    }
  }

  up (i ,0 ,n) writeln (ans[i]);
  return 0;

}
```

但是这题还有[加强版](https://www.luogu.com.cn/problem/P11670)，不过加强版是求和。

---

## 作者：lkjlkjlkj2012 (赞：0)

### 思路
首先第一眼看到这题，蒟蒻想到的是暴力：枚举反转区间的 $l,r$ ，统计答案。但是这样做是 $O(n^3)$ 的，考虑优化统计答案部分。由于反转区间 $[l,r]$ 相当于对于每个 $1 \le i \le \frac{r-l+1}{2}$ ，交换 $a_{l+i-1}$ ， $a_{r-i+1}$ ，所以考虑枚举 $\frac{r-l+1}{2}$ 也就是区间中点，就可以 $O(1)$ 维护答案啦。
### 代码

```cpp
// Problem: Problem 3. Cow Checkups
// Contest: USACO - USACO 2025 January Contest, Bronze
// URL: https://usaco.org/index.php?page=viewproblem&cpid=1457
// Memory Limit: 256 MB
// Time Limit: 4000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
int n, a[7505], b[7505];
int sum[7505], ans[7505];
int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i];
  for (int i = 1; i <= n; i++) cin >> b[i];
  for (int i = 1; i <= n; i++) sum[i] = sum[i - 1] + (a[i] == b[i]);
  // middle of is m;
  // int cnt = 0;
  for (int m = 1; m <= n; m++)  // m-l m-l+1 ... m-1 m m+1 ... m+l-1 m+l
  {
    int an = sum[n];
    ans[an]++;
    // cout << m << " " << m << endl;
    for (int l = 1; m - l > 0 && m + l <= n; l++) {
      an -= (a[m - l] == b[m - l]) + (a[m + l] == b[m + l]);
      an += (a[m - l] == b[m + l]) + (a[m + l] == b[m - l]);
      ans[an]++;
      // cout << m - l << " " << m + l << endl;
    }
  }
  // middle of is m and m+1
  for (int m = 1; m < n; m++)  // m-l m-l+1 ... m-1 m m+1 m+2 ... m+l m+l+1
  {
    int an = sum[n];
    an -= (a[m] == b[m]) + (a[m + 1] == b[m + 1]);
    an += (a[m] == b[m + 1]) + (a[m + 1] == b[m]);
    ans[an]++;
    // cout << m << " " << m + 1 << endl;
    for (int l = 1; m - l > 0 && m + l + 1 <= n; l++) {
      an -= (a[m - l] == b[m - l]) + (a[m + l + 1] == b[m + l + 1]);
      an += (a[m - l] == b[m + l + 1]) + (a[m + l + 1] == b[m - l]);
      ans[an]++;
      // cout << m - l << " " << m + l + 1 << endl;
    }
  }
  // cout << cnt << endl;
  for (int i = 0; i <= n; i++) cout << ans[i] << endl;
  return 0;
}
```

---

## 作者：LionBlaze (赞：0)

考虑可爱的区间 DP。

我们注意到，如果我们知道 $l\sim r$ 翻转的结果，那么就可以 $\Theta(1)$ 求出 $l - 1 \sim r + 1$ 的结果。

有两种 dp 方法：

1. $f_{l,r}$ 表示翻转 $l \sim r$ 的结果。
2. $f_{m,r}$ 表示翻转 $m-r \sim m+r$ 的结果。

第一种更简单，第二种和思路更符合。而这个蒟蒻赛时没有想到第一种做法，所以讲第二种。

首先，注意到 $m$ 和 $r$ 可能并非整数，比如 $m=114.5$ 且 $r=14.5$ 的时候 $m-r=100$ 且 $m+r=129$，都为整数，是一种合法的翻转方式。

但同时注意到若 $m-r$ 和 $m+r$ 都为整数，则 $(m-r)+(m+r)=2m$ 也是整数，所以 $m$ 要么是整数，要么是一个整数 $+0.5$，$r$ 同理。

故我们分类讨论。

令不翻转的结果是 $s$，则：

$m$ 为整数的基础情形是 $f_{m,0}=s$。

$m$ 不为整数的基础情形是 $f_{m,0.5}=s+\text{翻转后 m-0.5 是否匹配}+\text{翻转后 m+0.5 是否匹配}-\text{翻转前 m-0.5 是否匹配}-\text{翻转前 m+0.5 是否匹配}$

状态转移方程是 $f_{m,i}=f_{m,i-1}+\text{翻转后 m-i 是否匹配}+\text{翻转后 m+i 是否匹配}-\text{翻转前 m-i 是否匹配}-\text{翻转前 m+i 是否匹配}$。

虽然注意到 $m$ 不为整数的时候的基础情形和状态转移方程非常像，可以直接定义 $f_{m,-0.5}=s$，但是这个人太蒻了考场上没想出来。

同时，由于数组并不支持浮点数下标，所以写代码的时候用两个 dp 数组，一个表示整数，一个表示小数，然而两个维度数字都 $-0.5$。

考场代码非常可爱。

```cpp
﻿// 考虑区间 Dynamic Programming.
// 注意到对于同一个中心，我们可以 O(1) 快速扩展
// 总共有 2n-1 个中心，每个最多能扩展 n 次
// 时间复杂度 O(n^2)
//
// 实现细节：中心可能是小数。
// 所以可以两次区间 DP
#include <cstdio>

using namespace std;

int dp1[7505][3755]; // 其实第二维不需要开这么大，
int dp2[7505][3755]; // 但是不 MLE 就行
int a[7505];
int b[7505];
int cnt[7505];
int exchange(int x, int y)
{
	return int(a[x] == b[y]) + int(a[y] == b[x]) - int(a[x] == b[x]) - int(a[y] == b[y]);
}

int main()
{
	int n;
	scanf("%d", &n);
	int yyy_loves_OI = 0;
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", a + i);
	}
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", b + i);
		yyy_loves_OI += (b[i] == a[i]);
	}
	// ----------Part.1----------
	// 中心为整数时半径可以为 0，此时 l = r
	for (int OoO = 1; OoO <= n; OoO++)
	{
		cnt[dp1[OoO][0] = yyy_loves_OI]++;
		// 枚举半径
		for (int RrR = 1; OoO - RrR >= 1 && OoO + RrR <= n; RrR++)
		{
			// 真的不是压行大师啊呜呜
			cnt[dp1[OoO][RrR] = dp1[OoO][RrR - 1] + exchange(OoO - RrR, OoO + RrR)]++;
		}
	}
	// ----------Part.2----------
	for (int OoO = 1; OoO < n; OoO++)
	{
		cnt[dp2[OoO][0] = yyy_loves_OI + exchange(OoO, OoO + 1)]++;
		for (int RrR = 1; OoO - RrR >= 1 && OoO + RrR + 1 <= n; RrR++)
		{
			// 真的不是压行大师啊呜呜
			cnt[dp2[OoO][RrR] = dp2[OoO][RrR - 1] + exchange(OoO - RrR, OoO + RrR + 1)]++;
		}
	}
	for (int i = 0; i <= n; i++)
	{
		printf("%d\n", cnt[i]);
	}
	return 0;
}
```

---

